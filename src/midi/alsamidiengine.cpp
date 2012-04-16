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

#include "alsamidiengine.h"
#include "../model/document.h"

AlsaMidiEngine::AlsaMidiEngine()

: MidiEngine() {


}

AlsaMidiEngine::~AlsaMidiEngine() {

}

void AlsaMidiEngine::init() {

	// Open connection to system sequencer
    bool okSoFar = snd_seq_open(&_seqHandle, "default", SND_SEQ_OPEN_INPUT, 0) == 0;


    // Set ALSA client name
    if (okSoFar)
    	okSoFar = snd_seq_set_client_name(_seqHandle, "qrest") == 0;

    // open an input port to the sequencer
    if (okSoFar) {
    	 _port = snd_seq_create_simple_port(_seqHandle, "Midi Clock IN",
                          SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE,
                          SND_SEQ_PORT_TYPE_APPLICATION);

    	 Document::getInstance()->setMidiAvailable(_port >= 0);
    }
}

int AlsaMidiEngine::readEvent() {

	/*
	 * actual MIDI event read is done here
	 *
	 * Since we're running in a distinct thread, we can use ALSA's default blocking read
	 */
	snd_seq_event_t *ev = 0;
	snd_seq_event_input(_seqHandle, &ev);

	/*
	 * report cpatured event
	 */
	switch ( ev->type ) {

	case SND_SEQ_EVENT_CLOCK:

		return EVENT_CLOCK;
		break;

	case SND_SEQ_EVENT_CONTINUE:
	case SND_SEQ_EVENT_START:

		return EVENT_START;
		break;

	case SND_SEQ_EVENT_STOP:

		return EVENT_STOP;
		break;

	default:
		break;
	}

	return EVENT_UNHANDLED;
}
