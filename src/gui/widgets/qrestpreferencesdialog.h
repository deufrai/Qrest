/*
 *  qrest
 *
 *  Copyright (C) 2008-2012 - Frédéric CORNU
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

#ifndef QRESTPREFERENCESDIALOG_H
#define QRESTPREFERENCESDIALOG_H

#include <QDialog>
#include "ui_qrestpreferencesdialog.h"

/**
 * Main preferences dialog box.
 */
class QrestPreferencesDialog: public QDialog {
Q_OBJECT

    ////////////////////////////////////////////////////////////////////////////
    //
    // INIT
    //
    ////////////////////////////////////////////////////////////////////////////
public:
    QrestPreferencesDialog(QWidget *parent = 0);
    ~QrestPreferencesDialog();

    ////////////////////////////////////////////////////////////////////////////
    //
    // MEMBERS
    //
    ////////////////////////////////////////////////////////////////////////////
private:
    Ui::QrestPreferencesDialogClass ui;

    ////////////////////////////////////////////////////////////////////////////
    //
    // SLOTS
    //
    ////////////////////////////////////////////////////////////////////////////
private slots:
    /**
     * this slot is called when the 'OK' button is clicked
     */
    virtual void accept();
};

#endif // QRESTPREFERENCESDIALOG_H
