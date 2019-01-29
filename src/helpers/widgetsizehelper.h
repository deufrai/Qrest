/*
 *  qrest
 *
 *  Copyright (C) 2008-2019 - Frédéric CORNU
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


#ifndef WIDGETSIZEHELPER_H
#define WIDGETSIZEHELPER_H

class QWidget;

/**
  * Helper class (ifdefed on Mac) to set bigger font sizes
  */
class WidgetSizeHelper
{
public:
    WidgetSizeHelper();

    /**
     * recusrive scan of the whole parent -> child hierarchy of the widget param
     * and sets bigger font size for widgets that have text to show
     *
     * \param pWidget : the widget to scan
     *
     */
    static void setDefaultFontSize(QWidget* pWidget);
};

#endif // WIDGETSIZEHELPER_H

