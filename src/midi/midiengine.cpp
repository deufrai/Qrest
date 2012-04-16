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

#include "midiengine.h"
#include "alsamidiengine.h"
#include "../constants.h"
#include "midibroadcaster.h"
#include "../model/document.h"

MidiEngine* MidiEngine::_instance = 0;

MidiEngine::MidiEngine()
: nTickCounter( 0 ) {

}

MidiEngine::~MidiEngine() {

}

MidiEngine* MidiEngine::getInstance() {

	if ( 0 == _instance ) {

#ifdef linux
		_instance = new AlsaMidiEngine();
#endif

	}

	return _instance;
}

void MidiEngine::run() {

	/*
	 * We start the endless loop and translate MIDI events into calls to the
	 * MidiBroadcaster, which in turn translates them to Qt signals, mainly
	 * handled by the application data store : Document
	 */

	if ( Document::getInstance()->isMidiAvailable() ) {

		while (true) {

			switch ( readEvent() ) {

			case EVENT_CLOCK:

				/*
				 * MIDI clock events are triggered 24 times in a quarter note.
				 * So every 24 MIDI clock events, we trigger a 'quarter' message
				 */

				if ( ++nTickCounter == Constants::MIDI_CLOCK_EVENTS_PER_QUARTER ) {

					nTickCounter = 0;
					MidiBroadcaster::getInstance()->onMidiQuarter();
				}

				break;

			case EVENT_START:

				MidiBroadcaster::getInstance()->onMidiStart();
				break;

			case EVENT_STOP:

				MidiBroadcaster::getInstance()->onMidiStop();
				break;
			}
		}
	}
}
