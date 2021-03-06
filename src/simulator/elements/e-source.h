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

#ifndef ESOURCE_H
#define ESOURCE_H

#include <QObject>

#include "e-element.h"
#include "e-node.h"
//#include "e-pin.h"

class eSource : public eElement
{
    public:
        eSource( ePin* epin=0l );
        ~eSource();

        void initialize();
        void stamp();

        double voltHight() { return m_voltHigh; }
        void  setVoltHigh( double v );

        double voltLow() { return m_voltLow; }
        void  setVoltLow( double v );

        bool  out()       { return m_out; }
        void  setOut( bool hight );

        double imp()       { return m_imp; }
        void  setImp( double imp );

       // void setEpin( ePin* epin );

    protected:
        double m_voltHigh;
        double m_voltLow;
        double m_imp;
        double m_admit;

        bool  m_out;

        eNode* m_scrEnode;
};
#endif
