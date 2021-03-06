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

#ifndef LEDBASE_H
#define LEDBASE_H

#include "e-led.h"

class LedBase : public Component, public eLed
{
    Q_OBJECT
    Q_PROPERTY( float Umbral     READ umbral     WRITE setUmbral     DESIGNABLE true USER true )
    Q_PROPERTY( float MaxCurrent READ maxCurrent WRITE setMaxCurrent DESIGNABLE true USER true )

    public:
        LedBase( QObject* parent, QString type, QString id );
        ~LedBase();

        //void saveState();
        void updateStep();

        float umbral()                  { return eLed::umbral(); }
        void  setUmbral( float umbral ) { eLed::setUmbral( umbral );}

        float maxCurrent()                   { return eLed::maxCurrent(); }
        void  setMaxCurrent( float current ) { eLed::setMaxCurrent( current ); }

        virtual void paint( QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget );

    public slots:
        void remove();

    protected:
        //double m_prevpVolt;
        //double m_prevnVolt;
        virtual void drawBackground( QPainter *p )=0;
        virtual void drawForeground( QPainter *p )=0;
};

#endif
