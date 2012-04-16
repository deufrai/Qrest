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

#include "rtmidiengine.h"
#include "../model/document.h"
#include <iostream>


RtMidiEngine::RtMidiEngine() {

}

RtMidiEngine::~RtMidiEngine() {

	if ( _midiIn ) {

		_midiIn->closePort();
		delete _midiIn;
		_midiIn  = 0;
	}
}


void RtMidiEngine::init() {

	// Create the engine
	_midiIn = new RtMidiIn("qrest");

	/*
	 * Discovering available ports
	 */
	unsigned int nPorts = _midiIn->getPortCount();

	std::cout << "\nThere are " << nPorts << " MIDI input sources available.\n";

	std::string portName;

	for (unsigned int i = 0; i < nPorts; i++) {

		try {

			portName = _midiIn->getPortName(i);

		} catch (RtError &error) {

			error.printMessage();
		}

		std::cout << "  Input Port #" << i + 1 << ": " << portName << '\n';
	}


	// We don't want to ignore timing-related MIDI events
	_midiIn->ignoreTypes(true, false, true);

	// We open a named port
	_midiIn->openPort(0, "MIDI Clock IN");

	// If all goes wel untill here, MIDI is now available
	Document::getInstance()->setMidiAvailable(true);
}


int RtMidiEngine::readEvent() {

	// some specs about the value of message first byte, for interresting events
	static const int MIDI_START =  		0xFA;
	static const int MIDI_CONTINUE =  	0xFB;
	static const int MIDI_STOP =  		0xFC;
	static const int MIDI_CLOCK =  		0xF8;


	// read next message in queue
	_midiIn->getMessage(& _message);

	/*
	 * we sleep for 1ms because getMessage calls are non-blocking
	 * and we don't want to hog the CPU with the handling of empty messages
	 */
	msleep(1);

	// if the queue was empty, so is the current message
	if ( _message.size() > 0 ) {


		// We read the firt byte & check the type of event it describes
		switch ( (int)_message[0] ) {

		case MIDI_CLOCK:

			return EVENT_CLOCK;
			break;

		case MIDI_START:
		case MIDI_CONTINUE:

			return EVENT_START;
			break;

		case MIDI_STOP:

			return EVENT_STOP;
			break;
		}
	}

	return EVENT_UNHANDLED;
}


