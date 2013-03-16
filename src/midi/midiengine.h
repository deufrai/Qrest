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

#ifndef MIDIENGINE_H_
#define MIDIENGINE_H_

#include <vector>
#include <string>

/**
 * Main interface for MIDI operations implemented as a Singleton.
 *
 * Will hide lowLevel MIDI operations
 *
 */
class MidiEngine {

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
    // INTERFACE
    //
    ////////////////////////////////////////////////////////////////////////////
public:
    /**
     * Initialize and start the MIDI engine
     */
    virtual void init() = 0;

    /**
     * Stop & cleanup the current MIDI engine
     */
    virtual void cleanup() = 0;

    /**
     * Open a MIDI input port connected to a physical MIDI device
     *
     * \param deviceName : the name of the device to connect to
     *
     * if a blank name is given (param default value), then we
     * open a virtual port (Linux & Mac only)
     *
     * \return a boolean reflecting the success of the operation
     */
    virtual bool openPort( const std::string& deviceName ) = 0;

    /**
     * Close the open MIDI input port
     *
     */
    virtual void closePort() = 0;

    /**
     * return a list of available MIDI devices' names
     *
     * \return a list of names
     */
    virtual const std::vector<std::string> getDeviceNames() = 0;
};

#endif /* MIDIENGINE_H_ */
