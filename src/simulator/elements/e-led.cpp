/***************************************************************************
 *   Copyright (C) 2012 by santiago González                               *
 *   santigoro@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/

#include "e-led.h"

eLed::eLed()
    : eDiode()
{
    m_umbral = 2.4;

    m_prevStep   = Simulator::self()->step();
    m_maxCurrent = 0.02;
    m_lastCurrent = 0.0;

    disp_brightness  = 0;
    avg_brightness   = 0;
    lastUpdatePeriod = 0;
}
eLed::~eLed() {}

void eLed::runStep()
{
    if( !m_vChanged ) return;
    //qDebug()<< "eLed::runStep";
    eDiode::runStep();
    updateVI();
}
void eLed::updateVI()
{
    eDiode::updateVI();
    
    const unsigned long long step = Simulator::self()->step();
    int period = step - m_prevStep;    

    //if( period == 0 ) period = 1;

    m_prevStep = step;
    lastUpdatePeriod += period;

    avg_brightness += m_lastCurrent * period / m_maxCurrent;
    m_lastCurrent = m_current;
    //qDebug()<<"current"<< m_current<<m_lastCurrent<<period<< lastUpdatePeriod <<avg_brightness;
    //label->setText( QString("%1 A"). arg(float(int(m_current*1000))/1000) );
}

void eLed::updateBright()
{
    if( !Simulator::self()->isRunning() )
    {
        avg_brightness = 0;
        lastUpdatePeriod = 0;
        m_bright = 20;
        return;
    }
    updateVI();
    
    if ( lastUpdatePeriod != 0. )
    {
        disp_brightness = avg_brightness/lastUpdatePeriod;
        //qDebug() << disp_brightness << avg_brightness << lastUpdatePeriod;
        avg_brightness   = 0;
        lastUpdatePeriod = 0;
    }
    m_bright = uint(disp_brightness*255)+20;
    //qDebug() << m_bright;
}
