/*
 *  qrest
 *
 *  Copyright (C) 2008-2013 - Frédéric CORNU
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

#ifndef MIDILEARNDIALOG_H
#define MIDILEARNDIALOG_H

#include <QtGui/QDialog>
#include "ui_midilearndialog.h"
#include "../../midi/events/midievent.h"

/**
 * dialog displayed to capture a MIDI event and store
 * is as a trigger for the TAP feature.
 */
class MidiLearnDialog: public QDialog
{
Q_OBJECT

    ////////////////////////////////////////////////////////////////////////////
    //
    // INIT
    //
    ////////////////////////////////////////////////////////////////////////////
public:
    MidiLearnDialog( QWidget *parent = 0 );
    ~MidiLearnDialog();

    ////////////////////////////////////////////////////////////////////////////
    //
    // SLOTS
    //
    ////////////////////////////////////////////////////////////////////////////
public slots:

    /**
     * We recieved a MIDI event
     *
     * @param event : the event
     */
    void onEventLearned( const MidiEvent* event );

    /**
     * Captured event has been accepted as a trigger
     */
    virtual void accept();

    /**
     * dialog is rejected
     */
    virtual void reject();

    ////////////////////////////////////////////////////////////////////////////
    //
    // PRIVATE FUNCTIONS
    //
    ////////////////////////////////////////////////////////////////////////////
private:

    /**
     * Display a MidiEvent
     *
     * @param event : the event to display
     */
    void displayEvent( const MidiEvent* event );
    ////////////////////////////////////////////////////////////////////////////
    //
    // MEMBERS
    //
    ////////////////////////////////////////////////////////////////////////////

    /** our candidate MIDI event */
    const MidiEvent* _candidate;

    /** the UI form */
    Ui::MidiLearnDialogClass ui;
};

#endif // MIDILEARNDIALOG_H
