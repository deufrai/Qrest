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

#include <iostream>

#include "rtmidiengine.h"
#include "../model/document.h"
#include "../constants.h"

RtMidiEngine::RtMidiEngine() {

}

RtMidiEngine::~RtMidiEngine() {


}

void RtMidiEngine::init() {

	// Create the engine
    _midiIn = new RtMidiIn(Constants::MIDI_ENGINE_NAME);

	// We don't want to ignore timing-related MIDI events
	_midiIn->ignoreTypes(true, false, true);

}

void RtMidiEngine::openPort( const int portNumber ) {

	if ( _midiIn ) {

		try {

            _midiIn->openPort(portNumber, Constants::MIDI_PORT_NAME);

		} catch (RtError &error) {

			error.printMessage();
		}
	}
}

void RtMidiEngine::openVirtualPort() {

	if ( _midiIn ) {

		try {

            _midiIn->openVirtualPort(Constants::MIDI_PORT_NAME);

		} catch (RtError &error) {

			error.printMessage();
		}
	}
}

void RtMidiEngine::closePort() {

		if ( _midiIn ) {

		try {

			_midiIn->closePort();

		} catch (RtError &error) {

			error.printMessage();
		}
	}
}


void RtMidiEngine::listPhysicalDevices() {

	unsigned int nPorts = _midiIn->getPortCount();

	std::cerr << nPorts << " MIDI input sources available :" << std::endl;

	for (unsigned int i = 0; i < nPorts; i++) {

		try {

			std::cerr << "  * Input Port #" << i + 1 << ": "
					<< _midiIn->getPortName(i) << std::endl;

		} catch (RtError &error) {

			error.printMessage();
		}
	}
}

int RtMidiEngine::readEvent() {

	// some specs about the value of message first byte, for interresting events
	static const int MIDI_START = 0xFA;
	static const int MIDI_CONTINUE = 0xFB;
	static const int MIDI_STOP = 0xFC;
	static const int MIDI_CLOCK = 0xF8;

	// read next message in queue
	_midiIn->getMessage(&_message);

	/*
	 * we sleep for 1ms because getMessage calls are non-blocking
	 * and we don't want to hog the CPU with the handling of empty messages
	 */
	msleep(1);

	// if the queue was empty, so is the current message
	if (_message.size() > 0) {

		// We read the firt byte & check the type of event it describes
		switch ((int) _message[0]) {

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

void RtMidiEngine::cleanup() {

	if (_midiIn) {

		delete _midiIn;
		_midiIn = 0;
	}

}

