/*
 *  qrest
 *
 *  Copyright (C) 2008-2016 - Frédéric CORNU
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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "ui_settingsdialog.h"

/**
 * Support class for the Settings dialog box
 */
class SettingsDialog: public QDialog {
Q_OBJECT

    ////////////////////////////////////////////////////////////////////////////
    //
    // INIT
    //
    ////////////////////////////////////////////////////////////////////////////
public:
    SettingsDialog( QWidget *parent = 0 );
    ~SettingsDialog();

    ////////////////////////////////////////////////////////////////////////////
    //
    // ACCESS
    //
    ////////////////////////////////////////////////////////////////////////////
    /**
     * get the 'remember window position' switch value
     *
     * @return true or false, duh
     */
    inline bool getRememberWindowPosition() const {
        return _rememberWidnowPosition;
    }

    /**
     * get the 'MIDI input port name' field value
     *
     * @return the value
     */
    inline const QString& getInputPortName() const {
        return _inputPortName;
    }

    /**
     * Get the 'device name' combobox chosen value
     *
     * @return the value
     */
    inline const QString& getDeviceName() const {
        return _deviceName;
    }

    inline const QString getChosenLanguage() const {

        return ui.cmbLocales->itemData( ui.cmbLocales->currentIndex() ).toString();
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    // SLOTS
    //
    ////////////////////////////////////////////////////////////////////////////
private slots:
    /** Qt slot that gets called when OK button is ckicked */
    virtual void accept();

    /**
     * Language comboBox selection has changed
     *
     * @param index : the 0-numbererd index of the currently
     *                selected comboBox item
     *
     **/
    void onLocalesChanged( int index );
    /**
     * Display dialog to check and / or set the TAP trigger MIDI event
     */
    void on_triggerButton_clicked();

    ////////////////////////////////////////////////////////////////////////////
    //
    // MEMBERS
    //
    ////////////////////////////////////////////////////////////////////////////
private:
    /** the UI object */
    Ui::SettingsDialogClass ui;

    /** main section */
    QListWidgetItem* _mainSection;

    /** midi section */
    QListWidgetItem* _midiSection;

    /** remember window position switch value */
    bool _rememberWidnowPosition;

    /** value of 'input port name' field */
    QString _inputPortName;

    /** value of deviceName combobox current chosen value */
    QString _deviceName;

    /** A label used to warn user that an app restart is needed */
    QLabel* _restartWarningLabel;

};

#endif // SETTINGSDIALOG_H
