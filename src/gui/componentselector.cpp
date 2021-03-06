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

#include "componentselector.h"
#include "itemlibrary.h"

ComponentSelector::ComponentSelector( QWidget *parent )
	: QTreeWidget( parent )
{
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::DragOnly);
    setAlternatingRowColors(true);
    setIndentation(12);
    setRootIsDecorated(true);
    setCursor(Qt::OpenHandCursor);
    headerItem()->setHidden( true );
    setIconSize( QSize( 32, 26));
	
//    QWhatsThis::add( this, QString::fromUtf8( gettext("Add components to the circuit diagram by dragging them into the circuit.<br><br>To add more than one component of the same type, doubleclick on a component, and click repeatedly in the circuit to place the component. Right click to stop placement.<br><br>Some components (such as subcircuits) can be removed by right clicking on the item and selecting \"Remove\"." ) ) );

    QString appPath = QCoreApplication::applicationDirPath();
    loadXml( appPath+"/data/arduino.xml", "Boards", "Arduino");

    foreach( LibraryItem* libItem, itemLibrary()->items() )
    {
        QString category = libItem->category();
        if( category != "")
        {
            QString icon = ":/";
            icon.append(libItem->iconfile());
            addItem( libItem->name(), category, icon, libItem->type() );
        }
    }

    loadXml( appPath+"/data/avrs.xml", "AVR", "AVR");
    
    connect( this, SIGNAL(itemPressed(QTreeWidgetItem*, int)),
             this, SLOT  (slotItemClicked(QTreeWidgetItem *, int)) );
}
ComponentSelector::~ComponentSelector() { }

void ComponentSelector::loadXml( const QString &mculist, const QString &category, const QString &type )
{
    QFile file(mculist);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
          QMessageBox::warning(0, tr("Application"), tr("Cannot read file %1:\n%2.").arg(mculist).arg(file.errorString()));
          return;
    }
    QDomDocument domDoc;
    if (!domDoc.setContent(&file))
    {
         QMessageBox::warning(0, tr("Application"), tr("Cannot set file %1\nto DomDocument").arg(mculist));
         file.close();
         return;
    }
    file.close();

    QDomElement root = domDoc.documentElement();
    QDomNode    node = root.firstChild();
    QDomElement element;

    while( !node.isNull() )
    {
        element = node.toElement();

        if( element.tagName()=="mcu" )
        {
            QString icon = "";
    
            if( element.hasAttribute("icon") )
            {
                icon = QCoreApplication::applicationDirPath();
                icon.append("/data/images/");
                icon.append(element.attribute("icon"));
            }
            addItem( element.attribute( "name" ), category, icon, type );
        }
        node = node.nextSibling();
    }
}

void ComponentSelector::addItem( const QString &caption, const QString &_category, const QString &icon, const QString &type )
{
    QTreeWidgetItem *item =  new QTreeWidgetItem(0);
    item->setText( 0, caption );
    item->setFlags( QFlag(32) );
    item->setIcon( 0, QIcon(icon) );
    item->setData( 0, Qt::UserRole, type );

    QTreeWidgetItem *titulo = 0l;

    if ( !m_categories.contains(_category, Qt::CaseSensitive) )
    {
        m_categories.append(_category);
        titulo = new QTreeWidgetItem(0);
        titulo->setFlags( QFlag(32) );
        QFont font = titulo->font(0);
        font.setPointSize(12);
        font.setWeight(75);
        titulo->setFont( 0, font );
        titulo->setText( 0, _category );
        titulo->setTextColor( 0, QColor(255, 230, 200) );
        titulo->setBackground( 0, QBrush(QColor(75, 75, 130)) );
        titulo->setChildIndicatorPolicy( QTreeWidgetItem::ShowIndicator );
        addTopLevelItem( titulo );
        titulo->setExpanded(true);
    }
    else
    {
        QList<QTreeWidgetItem*> list = findItems(_category, Qt::MatchExactly );

        if ( list.length() > 0 ) titulo = list.first();
        else
        {
            for( int i=0; i<topLevelItemCount(); i++ )
            {
                QTreeWidgetItem *it = topLevelItem(i);

                for( int j=0; j < it->childCount(); j++ )
                {
                    if( it->child(j)->text(0) == _category)
                       titulo = it->child(j);
                }
            }
        }
    }
    m_categories.append(caption);

    titulo->addChild( item );
}

void ComponentSelector::mouseReleaseEvent(QMouseEvent *)
{
    setCursor( Qt::OpenHandCursor );
}


void ComponentSelector::slotItemClicked( QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    if (!item) return;

    QMimeData *mimeData = new QMimeData;
    QString type = item->data(0, Qt::UserRole).toString();
    mimeData->setText( item->text(0) );
    mimeData->setHtml( type );              // esto hay que revisarlo

    if( type=="" ) return;

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);

    drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
}

