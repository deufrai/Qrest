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

#ifndef MIDIMROADCASTER_H_
#define MIDIMROADCASTER_H_

#include <QObject>
#include <QTimer>
#include "../constants.h"
#include "midiengine.h"

/**
 * This class will be our central point for all MIDI operations.
 * Relaying information between the MIDI engine & all other objects in the app
 *
 * Another key point in this class is de-coupling the MidiEngine thread from the GUI thread
 *
 * Since the events fired from the MidiEngine thread will affect what is displayed
 * on the GUI, we must use Qt signals to avoid GUI modifications from outside
 * the main application"s event loop.
 *
 * So this class's Qt signals are connected to slots of this same class.
 **/
class MidiController : public QObject {

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
     * Simply emits a Qt signal (bip()) when MIDI engine detects a quarter note has
     * ellapsed while recieving MIDI Clock.
     */
    void midiQuarter();

    /**
     * Simply emits a Qt signal (start()) when MIDI engine detects that MIDI clock
     * has started
     */
    void midiStart();

    /**
     * Simply emits a Qt signal (stop()) when MIDI engine detects that MIDI clock
     * has stopped
     */
    void midiStop();

    /**
     * MIDI Clock Synchro has been requested
     */
    void midiSyncStart();

    /**
     * MIDI Clock Synchro has been canceled
     */
    void midiSyncStop();

    /**
     * Get a list of available MIDI devices' names
     *
     * \return a list of device names
     */
    const std::vector<std::string> getDeviceNames();

    /**
     * Open a MIDI input port
     *
     * \return a boolean reflecting the success of the operation
     */
    bool openPort( );

    /**
     * close the MIDI input port
     */
    void closePort();

    /**
     * close open port & reopen
     */
    bool resetPort();

    /**
     * Reset the midi engine
     */
    void resetEngine();
    ////////////////////////////////////////////////////////////////////////////
    //
    // SIGNALS
    //
    ////////////////////////////////////////////////////////////////////////////
signals:
    void bip();
    void start();
    void stop();
    void lost_synchro();
    void reset();

    ////////////////////////////////////////////////////////////////////////////
    //
    // SLOTS
    //
    ////////////////////////////////////////////////////////////////////////////
public slots:
    /**
     * Ask the TapTempoCalculator to take the current time into account
     */
    void onBip();

    /**
     * Tell Document that MIDI Clock just started
     */
    void onStart();

    /**
     * Tell Document that MIDI Clock just stopped
     */
    void onStop();

private slots:
    /**
     * Tell everyone MIDI Sync has been lots
     */
    void onSyncTimeout();

    ////////////////////////////////////////////////////////////////////////////
    //
    // MEMBERS
    //
    ////////////////////////////////////////////////////////////////////////////
protected:
    /**
     * Timer used stop listening to MIDI clock events when no events are recieved
     * after a certain time
     *
     * see : Constants::MIDI_SYNC_TIMEOUT_MS
     */
    QTimer* _synchroTimeoutTimer;

    /**
     * Pointer to the unique MIDI engine
     */
    MidiEngine* _midiEngine;
};

#endif /* MIDIMROADCASTER_H_ */
