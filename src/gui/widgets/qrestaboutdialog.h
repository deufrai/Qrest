/*
 *  qrest
 *
 *  Copyright (C) 2008-2009 - Frédéric CORNU
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

#ifndef QRESTABOUTDIALOG_H
#define QRESTABOUTDIALOG_H

#include <QtGui/QDialog>
#include "ui_qrestaboutdialog.h"

/**
 * The "About" Dialog
 */

class QrestAboutDialog : public QDialog
{
    Q_OBJECT

    ////////////////////////////////////////////////////////////////////////////
	//
	// INIT
	//
	////////////////////////////////////////////////////////////////////////////
public:
    QrestAboutDialog(const char* versionString, QWidget *parent = 0);
    ~QrestAboutDialog();

    ////////////////////////////////////////////////////////////////////////////
	//
	// MEMBERS
	//
	////////////////////////////////////////////////////////////////////////////
private:
	/** the GUI from */
    Ui::QrestAboutDialog ui;
};

#endif // QRESTABOUTDIALOG_H
