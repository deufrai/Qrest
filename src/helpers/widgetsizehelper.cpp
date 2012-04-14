/*
 *  qrest
 *
 *  Copyright (C) 2008-2011 - Frédéric CORNU
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <QWidget>
#include <QObjectList>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QGroupBox>
#include <QCheckBox>

#include "widgetsizehelper.h"
#include "../constants.h"

WidgetSizeHelper::WidgetSizeHelper()
{

}

void WidgetSizeHelper::setDefaultFontSize(QWidget* pWidget) {

    // we get children of pWidget

    QObjectList children = pWidget->children();

    // for each child
    for ( int i = 0; i < children.length(); i++ ) {

        /*
         * we change its font size if it is of one of those types
         *
         *  - QLabel
         *  - QLineEdit
         *  - QRadioButton
         *  - QGroupBox
         *  - QCheckBox
         */
        QWidget* pChild = static_cast<QWidget*> ( children.at(i) );

        if (  qobject_cast<QLabel*>(pChild) != NULL ||
              qobject_cast<QLineEdit*>(pChild) != NULL ||
              qobject_cast<QRadioButton*>(pChild) != NULL ||
              qobject_cast<QGroupBox*>(pChild) != NULL  ||
              qobject_cast<QCheckBox*>(pChild) != NULL )
        {
            QFont lFont = pChild->font();
            lFont.setPointSize(Constants::MAC_FONT_SIZE);
            pChild->setFont(lFont);
        }

        // and scan it if it has children
        if ( 0 != pChild->children().length() ) {

            setDefaultFontSize( pChild );
        }
    }
}
