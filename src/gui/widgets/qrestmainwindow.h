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

#ifndef QRESTMAINWINDOW_H
#define QRESTMAINWINDOW_H

#include <QtGui/QMainWindow>
#include "../forms/ui_qrestmainwindow.h"
#include "../../dp/observer.h"
#include "../../midi/midicontroller.h"

class Document;
class ProgressPie;

/**
 * Qrest Really Easy Studio Toolkit main window
 */
class QrestMainWindow: public QMainWindow, Observer {
Q_OBJECT

public:

    ////////////////////////////////////////////////////////////////////////////
    //
    // INIT
    //
    ////////////////////////////////////////////////////////////////////////////
    QrestMainWindow(QWidget *parent = 0);
    ~QrestMainWindow();

    ////////////////////////////////////////////////////////////////////////////
    //
    // INTERFACE
    //
    ////////////////////////////////////////////////////////////////////////////
    /**
     * update view to reflect App data changes
     */
    virtual void updateView();

private slots:

    ////////////////////////////////////////////////////////////////////////////
    //
    // SLOTS
    //
    ////////////////////////////////////////////////////////////////////////////
    /**
     * Slot that gets called when 'return' is presses with tempo edit field
     * focused.
     */
    void on_tempoEdit_returnPressed();

    /**
     * Slot that gets called whenever tempo input field's content has changed
     *
     * \param text the new text
     */
    void on_tempoEdit_textEdited(const QString& text);

    /**
     * Slot that gets called when 'tap' button is pressed
     */
    void on_tapButton_pressed();

    /**
     * Slot that gets called when 'plain' radio button is clicked
     */
    void on_plainRadio_clicked();

    /**
     * Slot that gets called when 'dotted' radio button is clicked
     */
    void on_dottedRadio_clicked();

    /**
     * Slot that gets called when 'triplet' radio button is clicked
     */
    void on_tripletRadio_clicked();

    /**
     * Slot that gets called upon "Quit" action triggering
     */
    void on_actionQuit_triggered();

    /**
     * Slot that gets called upon "Preferences" action triggering
     */
    void on_actionPreferences_triggered();

    /**
     * Slot that gets called upon "About" action triggering
     */
    void on_actionAbout_triggered();

    /**
     * Slot that gets called upon "Help" action triggering.
     *
     * Shows help viewer
     */
    void on_actionHelp_triggered();

    /**
     * Slot that gets called when 'freewheel' radio button is clicked
     */
    void on_freewheelRadio_clicked();

    /**
     * Slot that gets called when 'MIDI sync' radio button is clicked
     */
    void on_syncRadio_clicked();

    /**
     * Slot that gets called when 'MIDI TapTempo' radio button is clicked
     */
    void on_triggerRadio_clicked();

    /**
     * Makes sure help viewer is on front.
     */
    void raiseHelp();

    /**
     * A MIDI Clock timeout has been detected
     */
    void onTimeout();

    /**
     * entered freewheel mode
     */
    void onFreewheel();

    /**
     * entered trigger mode
     */
    void onTrigger();

    /**
     * entered learn mode
     */
    void onLearn();

    /**
     * entered sync mode
     */
    void onSync();

    ////////////////////////////////////////////////////////////////////////////
    //
    // EVENT HANDLERS
    //
    ////////////////////////////////////////////////////////////////////////////

private:
    /**
     * Custom event handler used for tempo edit field and mousewheel events
     *
     * \param target the object tagetted by the event
     * \param event the event to be handled
     *
     * \return true if event should not be handled by other handlers.
     */
    virtual bool eventFilter(QObject *target, QEvent *event);

    /**
     * Handles close event on this window.
     *
     * Destroys help window.
     */
    virtual void closeEvent(QCloseEvent* event);

    ////////////////////////////////////////////////////////////////////////////
    //
    // PRIVATE FUNCTIONS
    //
    ////////////////////////////////////////////////////////////////////////////
    /**
     * Give the focus to tempo input field.
     */
    void setFocusToTempoInput(void) const;

    /**
     * pass tempo input field content value to app data
     */
    void processTempoInput(void) const;

    /**
     * Display a permanent message in status bar
     *
     * \param message the message to display
     */
    void statusPermMessage(const QString& message) const;

    /**
     * Display a temporary message in status bar
     *
     * \param message the message to display
     */
    void statusTempMessage(const QString& message) const;

    /**
     * Clear status bar message zone
     */
    void statusClear(void) const;

    /**
     * Refresh delay times display fields.
     */
    void updateDelayDisplays(void);

    /**
     * Refresh LFO display fields.
     */
    void updateLfoDisplays(void);

    /**
     * We check if we have a configured MIDI trigger.
     *
     * If not, we display a warning message and redirect
     * the user to the trigger setup dialog.
     *
     * @return true if we have a trigger or user sets one up
     *         and falsa if user fails to provide one
     */
    bool checkIfTriggerModePossible();

    /**
     * En/Dis-able tempo input related UI controls
     *
     * @param enabled : well .... you know ...
     */
    void setTempoInputControlsEnable(bool enabled);

    /**
     * Display an error message on midi reset or openport failure
     */
    void errorMidiDevice();

    /**
     * En-Dis/able midi GUI controls
     *
     * @param enable should controls be enabled (true by default)
     */
    void setMidiControlsEnable(bool enable = true);

    ////////////////////////////////////////////////////////////////////////////
    //
    // MEMBERS
    //
    ////////////////////////////////////////////////////////////////////////////
    /** The GUI subclass */
    Ui::QrestMainWindowClass ui;

    /** Application data store */
    Document* _document;

    ProgressPie* _pie;

};

#endif // QRESTMAINWINDOW_H
