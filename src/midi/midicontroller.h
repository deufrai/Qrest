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

#ifndef MIDIMROADCASTER_H_
#define MIDIMROADCASTER_H_

#include <QObject>
#include "../constants.h"
#include "midiengine.h"
#include "states/midistate.h"

/**
 * This class will be our central point for all MIDI operations.
 * Relaying information between the MIDI engine & all other objects in the app
 *
 * It also serve the purpose of de-coupling the MIDI engine's internal thead (RtMidi implementation)
 * from the GUI. So changes on the GUI can be made ins response to MIDI event hadling in the different
 * states of the controller.
 *
 * De-coupling is done with Qt Signals & Slots
 **/
class MidiController: public QObject {

Q_OBJECT

    ////////////////////////////////////////////////////////////////////////////
    //
    // INIT
    //
    ////////////////////////////////////////////////////////////////////////////
private:
    MidiController();
    virtual ~MidiController();

    /** The single instance */
    static MidiController* _instance;

    ////////////////////////////////////////////////////////////////////////////
    //
    // INTERFACE
    //
    ////////////////////////////////////////////////////////////////////////////
public:

    /** Instanciate and/or return the single instance */
    static MidiController* getInstance();

    /**
     * Get a list of available MIDI devices' names
     *
     * \return a list of device names
     */
    const std::vector<std::string> getDeviceNames();

    /**
     * close open port & reopen
     */
    bool resetPort();

    /**
     * Reset the midi engine
     *
     * @return true id reset was successfull
     */
    bool resetEngine();

    /**
     * Process a new MIDI event.
     *
     * In fact, we pass it to our current State
     *
     * @param event the MIDI event to process
     */
    void processMidiEvent( const MidiEvent* event );

    /**
     * Enter trigger mode
     */
    void triggerMode();

    /**
     * Enter learn mode
     */
    void learnMode();

    /**
     * Enter sync mode
     */
    void syncMode();

    /**
     * Enter freeWheel mode
     */
    void freeWheel();

    /**
     * A MIDI event has been learned. we pass it to GUI
     * and switch back to freewhell state
     *
     * @param event the event
     */
    void learnStateCapturedEvent( const MidiEvent* event );

    /**
     * A MIDI Clock timeout has been detected by the syncState
     *
     * We switch batch to freewheel and alert everyone
     */
    void timeOutDetected();

    /**
     * Open a MIDI input port
     *
     * \return a boolean reflecting the success of the operation
     */
    bool openPort();

    /**
     * Check is midi controller is in Sync state
     *
     * \return true if controller's state is Sync
     */
    inline bool isSyncState() { return _currentState == _syncState; }

    ////////////////////////////////////////////////////////////////////////////
    //
    // PRIVATE FUNCTIONS
    //
    ////////////////////////////////////////////////////////////////////////////
private:
    /**
     * close the MIDI input port
     */
    void closePort();

    ////////////////////////////////////////////////////////////////////////////
    //
    // SIGNALS
    //
    ////////////////////////////////////////////////////////////////////////////
signals:
    /**
     * Emitted when a new MIDI event has been recieved from the MIDI engine callback
     *
     */
    void sigMidiEventRecieved( const MidiEvent* );

    /**
     * Emitted when a MIDI event has been learned.
     * Will be caught by the MIDI learning GUI
     *
     */
    void sigLearnedEvent( const MidiEvent* );

    /**
     * Emitted when a MIDI Clock timeout has been detected
     */
    void sigTimeout();

    /**
     * Emitted when entering freewheel mode
     */
    void sigFreewheel();

    /**
     * Emitted when entering trigger mode
     */
    void sigTrigger();

    /**
     * Emitted when entrering learn mode
     */
    void sigLearn();

    /**
     * Emitted when entering sync mode
     */
    void sigSync();

private slots:
    /**
     * Pass the event to our current state
     */
    void onMidiEventRecieved( const MidiEvent* event );

    ////////////////////////////////////////////////////////////////////////////
    //
    // MEMBERS
    //
    ////////////////////////////////////////////////////////////////////////////
protected:
    /**
     * Pointer to the unique MIDI engine
     */
    MidiEngine* _midiEngine;

    /** The FreeWheelState */
    MidiState* _freeWheelState;

    /** The SyncState */
    MidiState* _syncState;

    /** The LearnState */
    MidiState* _learnState;

    /** The TapTriggerState */
    MidiState* _triggerState;

    /** The current state */
    MidiState* _currentState;

};

#endif /* MIDIMROADCASTER_H_ */
