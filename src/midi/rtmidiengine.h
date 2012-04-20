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

#ifndef RTMIDIENGINE_H_
#define RTMIDIENGINE_H_

#include "midiengine.h"
#include "contrib/RtMidi.h"

#include <vector>

/**
 * MidiEngine implementation using RtMidi
 *
 * RtMidi: realtime MIDI i/o C++ classes
 * Copyright (c) 2003-2011 Gary P. Scavone
 *
 * http://www.music.mcgill.ca/~gary/rtmidi/
 */
class RtMidiEngine: public MidiEngine {

    ////////////////////////////////////////////////////////////////////////////
    //
    // INIT
    //
    ////////////////////////////////////////////////////////////////////////////
public:
    RtMidiEngine();
    virtual ~RtMidiEngine();

    ////////////////////////////////////////////////////////////////////////////
    //
    // INTERFACE
    //
    ////////////////////////////////////////////////////////////////////////////
    void init();
    void cleanup();
    bool openPort( const std::string portName );
    void closePort();

    /**
     * List all physical MIDI devices attached to the system
     */
    const std::vector<std::string> getDeviceNames();

private:

    static void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData );

    ////////////////////////////////////////////////////////////////////////////
    //
    // RtMIDI implementation support members
    //
    ////////////////////////////////////////////////////////////////////////////
    /** The RtMidi engine */
    RtMidiIn* _midiIn;

    /** container of last recieved MIDI message */
    std::vector<unsigned char> _message;

};

#endif /* RTMIDIENGINE_H_ */
