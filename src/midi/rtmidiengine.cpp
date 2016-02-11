/*
 *  qrest
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

#include <iostream>
#include <sstream>

#include "rtmidiengine.h"
#include "../model/document.h"
#include "../constants.h"
#include "../settings/settings.h"
#include "events/midieventfactory.h"
#include "midicontroller.h"

RtMidiEngine* RtMidiEngine::_instance = 0;

RtMidiEngine* RtMidiEngine::getInstance() {

    if( _instance == 0 ) {

        _instance = new RtMidiEngine();
    }

    return _instance;
}

RtMidiEngine::RtMidiEngine()
        : _midiIn( 0 ) {

}

RtMidiEngine::~RtMidiEngine() {

}

void RtMidiEngine::init() {

    // Create the engine
    _midiIn = new RtMidiIn( Constants::MIDI_ENGINE_NAME );

    // We don't want to ignore timing-related MIDI events
    _midiIn->ignoreTypes( true, false, true );
}

std::string RtMidiEngine::createPortName() {

    std::string portName = Settings::getInstance()->getSettings().value(
            Settings::MIDI_PORT_NAME,
            Settings::MIDI_PORT_NAME_DEFAUT ).toString().toStdString();

    /*
     * QREST-27 : Automatic MIDI port rename when several Qrest instance are running
     *
     * - We scan ports already opened by qrest
     *   they will show up like that:
     *
     * On Linux : <engine_name>:<0>
     * On Mac   : <real_port_name>
     * On Win   : we don't care, it just works
     *
     *   So we have 2 distinct cases to handle :
     *
     * On Linux :
     *   we count the number of already running Qrest instances by checking against the engine name
     *
     * On Mac :
     *   we count the number of already running Qrest instances by checking prefered port name
     */

    RtMidiOut midiOut( Constants::MIDI_ENGINE_NAME );

    unsigned int portCount = midiOut.getPortCount();
    unsigned int instanceCount = 0;

    for( unsigned int i = 0; i < portCount; i++ ) {

        std::string currentName = midiOut.getPortName( i );

#ifndef Q_WS_MAC
        if( currentName.find( Constants::MIDI_ENGINE_NAME ) < currentName.npos ) {
#else
            if ( currentName.find(portName) < currentName.npos ) {
#endif

            instanceCount++;
        }
    }

    if( instanceCount > 0 ) {

        std::stringstream stream;

        stream << portName << instanceCount + 1;

        portName = stream.str();
    }

    return portName;
}

bool RtMidiEngine::openPort( const std::string& deviceName ) {

    if( _midiIn ) {

        /*
         * if deviceName is empty, we are opening a virtual port (Linux & Mac)
         */
        if( deviceName.empty() ) {

            try {

                _midiIn->setCallback( &mycallback );
                _midiIn->openVirtualPort( createPortName() );
                return true;

            } catch( RtError& error ) {

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

        for( unsigned int i = 0; i < devices.size(); i++ ) {

            if( 0 == devices.at( i ).compare( deviceName ) ) {

                try {

                    _midiIn->setCallback( &mycallback );
                    _midiIn->openPort( i, createPortName() );
                    return true;

                } catch( RtError &error ) {

                    error.printMessage();
                }
            }
        }
    }

    // in here, either the MIDI engine is NULL or our device cannot be found
    return false;
}

void RtMidiEngine::closePort() {

    if( _midiIn ) {

        try {

            _midiIn->closePort();

        } catch( RtError &error ) {

            error.printMessage();
        }
    }
}

const std::vector<std::string> RtMidiEngine::getDeviceNames() {

    unsigned int nPorts = _midiIn->getPortCount();

    std::vector<std::string> devices;

    for( unsigned int i = 0; i < nPorts; i++ ) {

        try {

            devices.push_back( _midiIn->getPortName( i ) );

        } catch( RtError &error ) {

            error.printMessage();
        }
    }

    std::vector<std::string>::const_iterator it = devices.begin();

    while( it != devices.end() ) {

        std::cerr << *it++ << std::endl;
    }

    return devices;
}

void RtMidiEngine::mycallback( double deltatime, std::vector<unsigned char> *message, void *userData ) {

    /*
     * We don't like warnings, even when we are not responsible.
     * this simply does nothing but we don't want to get used to see warnings
     */
    (void) ( userData );
    (void) ( deltatime );

    MidiController::getInstance()->processMidiEvent( MidiEventFactory::createEvent( message ) );
}

void RtMidiEngine::cleanup() {

    delete _midiIn;
    _midiIn = 0;
}

