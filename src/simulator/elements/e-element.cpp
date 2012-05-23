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

#include "e-element.h"


eElement::eElement() : cero_doub( 1e-12 ), high_imp( 1e12 )
{
    m_vChanged = false;
    Simulator::self()->addToElementList( this );
}
eElement::~eElement()
{
    Simulator::self()->remFromElementList( this );
}

void eElement::setVChanged()
{
    m_vChanged = true;
}

ePin* eElement::getEpin( int pin )
{
    return m_ePin[pin];
}

