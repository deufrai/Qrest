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

#include "midicontroller.h"
#include "../process/tapTempoCalculator.h"
#include "../model/document.h"
#include "../settings/settings.h"
#include "states/freewheelstate.h"
#include "states/syncstate.h"

MidiController* MidiController::_instance = 0;

MidiController::MidiController()
: _midiEngine(MidiEngine::getInstance()),
  _freeWheelState(new FreeWheelState()),
  _syncState(new SyncState()),
  _currentState(_freeWheelState)


{
    // connect our MIDI egnine <--> GUI decoupling signal / slots
    connect(this, SIGNAL(midiEventRecieved(const MidiEvent*)), this, SLOT(onMidiEventRecieved(const MidiEvent*)));

    // startup MIDI engine
    _midiEngine->init();
}

MidiController::~MidiController() {

    _midiEngine->closePort();
    _midiEngine->cleanup();
}


MidiController* MidiController::getInstance() {

    if ( 0 == _instance ) {

        _instance = new MidiController();
    }

    return _instance;
}


void MidiController::resetEngine() {

    closePort();
    _midiEngine->cleanup();

    emit midiReset();

    _midiEngine->init();
    openPort();
}

const std::vector<std::string> MidiController::getDeviceNames() {

    return _midiEngine->getDeviceNames();
}

bool MidiController::openPort( ) {

#ifdef Q_WS_WIN
    /**
     * On windows, we use physical MIDI ports. So a device name needs to
     * be present in saved settings.
     */
    std::string portName = Settings::getInstance()->getSettings().value(
                Settings::MIDI_DEVICE,
                Settings::MIDI_DEVICE_DEFAULT
                ).toString().toStdString();

#else

    /**
     * On Mac & Linux, virtual MIDI ports are used. So the openPort function
     * needs to recieve a blank portName string
     */
    std::string portName = "";
#endif

    return _midiEngine->openPort(portName);
}

void MidiController::closePort() {

    _currentState->reset();
    _currentState = _freeWheelState;
    _midiEngine->closePort();
}


bool MidiController::resetPort() {

    closePort();
    emit midiReset();
    return openPort();
}

void MidiController::startMidiSync() {

    _currentState = _syncState;
}

void MidiController::stopMidiSync() {

    _currentState = _freeWheelState;
}

void MidiController::processMidiEvent(const MidiEvent* event ) {

    emit midiEventRecieved(event);
}

void MidiController::onMidiEventRecieved(const MidiEvent* event) {

    _currentState->processEvent(event);
}
