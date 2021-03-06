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

#ifndef MCUCOMPONENT_H
#define MCUCOMPONENT_H

#include <QtGui>

#include "component.h"
#include "baseprocessor.h"

class McuComponentPin;

class McuComponent : public Component
{
	Q_OBJECT
    Q_PROPERTY( QString  program  READ program WRITE setProgram DESIGNABLE true USER true )
    //Q_PROPERTY( int      Freq     READ freq    WRITE setFreq    DESIGNABLE true USER true )

	public:
        QRectF boundingRect() const { return m_area; }

        McuComponent( QObject* parent, QString type, QString id );
        ~McuComponent();

        QString program()   const      { return  m_symbolFile; }
        void setProgram( QString /*pro*/ ) {/* m_symbolFile = pro;*/ }

        //int  freq()                    { return m_freq; }
        //void setFreq( int freq )       { m_freq = freq; }

        virtual void paint( QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget );
	
    public slots:
        virtual void terminate();
        virtual void remove();
        virtual void reset();
        void slotLoad();
        void slotReload();

	protected:
        void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

        virtual void addPin( QString id, QString type, QString label, int pos, int xpos, int ypos, int angle )=0;
        virtual void attachPins()=0;
        virtual void initPackage();
        //virtual bool attachDevice();

        BaseProcessor* m_processor;

        int   m_numpins;
        //int   m_freq;

        QString m_device;       // Name of device
        QString m_dataFile;     // pics.xml or whatever file containig mcu defs
        QString m_symbolFile;   // firmware file loaded
        QString m_lastFirmDir;  // Last firmware folder used
        
        QList<McuComponentPin*> m_pinList;
};
#endif

