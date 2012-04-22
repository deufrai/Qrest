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
#include "states/learnstate.h"

#ifndef QT_NO_DEBUG
#include <QDebug>
#include "states/taptriggerstate.h"
#endif

MidiController* MidiController::_instance = 0;

MidiController::MidiController()
: _midiEngine(MidiEngine::getInstance()),
  _freeWheelState(new FreeWheelState()),
  _syncState(new SyncState()),
  _learnState(new LearnState()),
  _triggerState(new TapTriggerState()),
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

    #ifndef QT_NO_DEBUG
            qDebug() << "CONTROLLER : resetEngine()";
    #endif

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

#ifndef QT_NO_DEBUG
        qDebug() << "MidiController::openPort - ";
#endif

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

    #ifndef QT_NO_DEBUG
            qDebug() << "MidiController::closePort - ";
    #endif

    _currentState->reset();
    _currentState = _freeWheelState;
    _midiEngine->closePort();
}


bool MidiController::resetPort() {

    #ifndef QT_NO_DEBUG
            qDebug() << "MidiController::resetPort - ";
    #endif

    closePort();
    emit midiReset();
    return openPort();
}

void MidiController::startMidiSync() {

    #ifndef QT_NO_DEBUG
            qDebug() << "MidiController::startMidiSync - ";
    #endif

    _currentState->reset();
    _currentState = _syncState;
}

void MidiController::stopMidiSync() {

    #ifndef QT_NO_DEBUG
            qDebug() << "MidiController::stopMidiSync - ";
    #endif

    _currentState->reset();
    _currentState = _freeWheelState;
}

void MidiController::processMidiEvent(const MidiEvent* event ) {

    emit midiEventRecieved(event);
}

void MidiController::onMidiEventRecieved(const MidiEvent* event) {

    _currentState->processEvent(event);
}

void MidiController::stopLearning() {

    #ifndef QT_NO_DEBUG
            qDebug() << "MidiController::stopLearning - ";
    #endif

    _currentState->reset();
    _currentState = _freeWheelState;
}

void MidiController::startTriggerMode() {

    #ifndef QT_NO_DEBUG
            qDebug() << "MidiController::startTriggerMode - ";
    #endif

    _currentState->reset();
    _currentState = _triggerState;
}

void MidiController::stopTriggerMode() {

    #ifndef QT_NO_DEBUG
            qDebug() << "MidiController::stopTriggerMode - ";
    #endif

    _currentState->reset();
    _currentState = _freeWheelState;
}

void MidiController::startLearning() {

    #ifndef QT_NO_DEBUG
            qDebug() << "MidiController::startLearning - ";
    #endif

    _currentState->reset();
    /*
     * TODO : emitting a reset here is too much.
     * this signal is meant for a bigger event, the reset of the whole MIDI engine
     *
     * But this is all we can do untill we have real
     * State Macgine implementation permitting us to
     * trigger specific events on specific State transitions
     *
     * Can be done with a test on _currentState before assigning it
     * the new state
     */
    emit midiReset();
    _currentState = _learnState;
}

void MidiController::learnStateCapturedEvent(const MidiEvent* event) {

    #ifndef QT_NO_DEBUG
            qDebug() << "MidiController::learnStateCapturedEvent - ";
    #endif

    emit learnedEvent(event);
}
