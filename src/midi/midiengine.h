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

#ifndef MIDIENGINE_H_
#define MIDIENGINE_H_

#include <QThread>
#include <vector>

/**
 * Main interface for MIDI operations implemented as a Singleton
 *
 * Will hide platform sepcific implementation.
 *
 * Will run in a thread that will keep listening for these MIDI evnents :
 *
 *   - MIDI clock
 *   - Transport stop
 *   - Transport resume
 *
 * and post these infos to the MidiBroadcaster in charge of emitting Qt signals
 */
class MidiEngine: public QThread {

protected:
    ////////////////////////////////////////////////////////////////////////////
    //
    // INIT
    //
    ////////////////////////////////////////////////////////////////////////////
    MidiEngine();
    virtual ~MidiEngine();


    ////////////////////////////////////////////////////////////////////////////
    //
    // SINGLETON
    //
    ////////////////////////////////////////////////////////////////////////////
private:
    static MidiEngine* _instance;

public:
    /**
     * Instanciate the Singleton
     *
     * \return the unique instance
     */
    static MidiEngine* getInstance();


    ////////////////////////////////////////////////////////////////////////////
    //
    // INTERFACE
    //
    ////////////////////////////////////////////////////////////////////////////
    /**
     * Stop the thrad execution
     */
    void stop();

    /**
     * Initialize and start the MIDI engine
     */
    virtual void init() = 0;

    /**
     * Read next MIDI event
     */
    virtual int readEvent() = 0;

    /**
     * Stop & cleanup the current MIDI engine
     */
    virtual void cleanup() = 0;

    /**
     * Open a MIDI input port connected to a physical MIDI device
     *
     * \param portName : the name of the device to connect to
     *
     * if a blank name is given (param default value), then we
     * open a virtual port (Linux & Mac only)
     *
     * \return a boolean reflecting the success of the operation
     */
    virtual bool openPort( const std::string portName ) = 0;

    /**
     * Close the open MIDI input port
     *
     */
    virtual void closePort() = 0;

    /**
     * Should we start ot stop synchronizing to MIDI Clock ?
     *
     * \param slave -- yes to sync
     */
    inline void setSlave(const bool slave) {

        _midiClockSlave = slave;
    }

    /*
     * return a list of available MIDI devices' names
     *
     * \return a list of names
     */
    virtual const std::vector<std::string> getDeviceNames() = 0;

private:
    ////////////////////////////////////////////////////////////////////////////
    //
    // PRIVATE FUNCTIONS
    //
    ////////////////////////////////////////////////////////////////////////////
    /**
     * QThread implementation
     */
    void run();


    ////////////////////////////////////////////////////////////////////////////
    //
    // MEMBERS
    //
    ////////////////////////////////////////////////////////////////////////////
private:
    /** count how many MIDI clock events have been recieved */
    int _nTickCounter;

    /** Should we keep looping ? */
    bool _mustRun;

    /** are we listening to MIDI Clock */
    bool _midiClockSlave;

protected:

    /**
     * The handled MIDI events
     */
    enum eventTypes {

        EVENT_UNHANDLED,
        EVENT_CLOCK,
        EVENT_START,
        EVENT_STOP
    };
};

#endif /* MIDIENGINE_H_ */
