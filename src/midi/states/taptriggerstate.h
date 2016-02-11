/*  qrest
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

#ifndef TAPTRIGGERSTATE_H_
#define TAPTRIGGERSTATE_H_

#include "midistate.h"
#include "../events/midievent.h"

/**
 * the state in which we are listening for incomming MIDI events
 * and trigger a TAP if current event matches a user-defined reference event
 */
class TapTriggerState: public MidiState {

public:
    TapTriggerState();
    virtual ~TapTriggerState();

    virtual void reset() {
    } // Don't think we'll do much in here

    virtual void processEvent( const MidiEvent* event );
};

#endif /* TAPTRIGGERSTATE_H_ */
