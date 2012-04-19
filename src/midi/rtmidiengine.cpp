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
#include "../settings/settings.h"
#include "events/midieventfactory.h"

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

bool RtMidiEngine::openPort( const std::string deviceName) {

    if ( _midiIn ) {

        std::string portName = Settings::getInstance()->getSettings().value(
                    Settings::MIDI_PORT_NAME,
                    Settings::MIDI_PORT_NAME_DEFAUT).toString().toStdString();

        /*
         * if deviceName is empty, we are opening a virtual port (Linux & Mac)
         */
        if ( deviceName.empty() ) {

            try {

                _midiIn->openVirtualPort(portName);
                return true;

            } catch (RtError& error) {

                error.printMessage();
                return false;
            }
        }

        /*
         * if deviceName is not empty, we are opening a physical port (windows)
         *
         * We get the list of all detected devices and search for
         * deviceName in that list.
         *
         * if found
         *
         *  - Open a physical port to it and return true
         *
         * else
         *
         * - return false
         */
        std::vector<std::string> devices = getDeviceNames();

        for (unsigned int i=0; i<devices.size(); i++) {

            if ( 0 == devices.at(i).compare(deviceName) ) {

                try {

                    _midiIn->openPort(i, portName);
                    return true;

                } catch (RtError &error) {

                    error.printMessage();
                }
            }
        }
    }

    // in here, either the MIDI engine is NULL or our device cannot be found
    return false;
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


const std::vector<std::string> RtMidiEngine::getDeviceNames() {

    unsigned int nPorts = _midiIn->getPortCount();

    std::vector<std::string> devices;

    for (unsigned int i = 0; i < nPorts; i++) {

        try {

            devices.push_back(_midiIn->getPortName(i));

        } catch (RtError &error) {

            error.printMessage();
        }
    }

    std::vector<std::string>::const_iterator it = devices.begin();

    while ( it != devices.end() ) {

        std::cerr << *it++ << std::endl;
    }

    return devices;
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

        //TODO : test to be removed
        delete MidiEventFactory::createEvent(_message);

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

