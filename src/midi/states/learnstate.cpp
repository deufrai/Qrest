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

#include "learnstate.h"
#include "../events/midinoteon.h"
#include "../events/midiprogramchange.h"
#include "../midicontroller.h"

LearnState::LearnState() {}

LearnState::~LearnState() {}

void LearnState::processEvent(const MidiEvent* event) {

    /*
     * We are learning the event that will trigger the TAP function.
     * Once captured, we send it to the GUI via the MidiController
     *
     * We handle 2 different types of events :
     *
     *  - Note ON
     *  - Program Change
     *
     * If we recieve any other type of event, we will send a NULL
     */

    if ( dynamic_cast<const MidiNoteOn*>        (event) != 0 ||
         dynamic_cast<const MidiProgramChange*> (event) != 0 ) {

        MidiController::getInstance()->learnStateCapturedEvent(event);

    } else {

        delete event;
        MidiController::getInstance()->learnStateCapturedEvent(0);
    }
}
