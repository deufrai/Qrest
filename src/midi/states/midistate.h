/*  qrest
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

#ifndef MIDISTATE_H_
#define MIDISTATE_H_

#include "../events/midievent.h"

/**
 * Interface for all State ojects that will help represent the various
 * states of the MIDI controller :
 *
 *  - Freewheel : We don't care about recieved MIDI events
 *  - Sync      : We sync application BPM whith recieved MIDI Clock events
 *  - TAP       : We trigger TAPs with MIDI events
 *  - Learn     : We listen for only one event for TAP learn mode
 *
 */
class MidiState {

public:
    virtual ~MidiState();

protected:
    MidiState();

public:
    /**
     * Process MIDI event according to state
     *
     * @param event the MIDI event to process
     */
    virtual void processEvent(const MidiEvent* event) = 0;

    /**
     * reset any state-specific status
     */
    virtual void reset() = 0;
};

#endif /* MIDISTATE_H_ */
