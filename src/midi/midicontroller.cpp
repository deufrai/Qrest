/*
 *  qrest
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

#ifndef QT_NO_DEBUG
#include <QDebug>
#endif

#include "midicontroller.h"
#include "../process/tapTempoCalculator.h"
#include "../model/document.h"
#include "../settings/settings.h"
#include "states/freewheelstate.h"
#include "states/syncstate.h"
#include "states/learnstate.h"
#include "states/taptriggerstate.h"
#include "rtmidiengine.h"

MidiController* MidiController::_instance = 0;

MidiController::MidiController()
        : _midiEngine( RtMidiEngine::getInstance() ),
                _freeWheelState( new FreeWheelState() ),
                _syncState( new SyncState() ),
                _learnState( new LearnState() ),
                _triggerState( new TapTriggerState() ),
                _currentState( _freeWheelState )

{
    // connect our MIDI egnine <--> GUI decoupling signal / slots
    connect( this, SIGNAL(sigMidiEventRecieved(const MidiEvent*)), this, SLOT(onMidiEventRecieved(const MidiEvent*)) );

    // startup MIDI engine
    _midiEngine->init();
}

MidiController::~MidiController() {

    _midiEngine->closePort();
    _midiEngine->cleanup();
}

MidiController* MidiController::getInstance() {

    if( 0 == _instance ) {

        _instance = new MidiController();
    }

    return _instance;
}

bool MidiController::resetEngine() {

#ifndef QT_NO_DEBUG
    qDebug() << "MidiController::resetEngine - ";
#endif

    closePort();
    _midiEngine->cleanup();
    _midiEngine->init();
    return openPort();
}

const std::vector<std::string> MidiController::getDeviceNames() {

    return _midiEngine->getDeviceNames();
}

bool MidiController::openPort() {

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

    return _midiEngine->openPort( portName );
}

void MidiController::closePort() {

#ifndef QT_NO_DEBUG
    qDebug() << "MidiController::closePort - ";
#endif

    freeWheel();
    _midiEngine->closePort();
}

bool MidiController::resetPort() {

#ifndef QT_NO_DEBUG
    qDebug() << "MidiController::resetPort - ";
#endif

    closePort();
    return openPort();
}

void MidiController::triggerMode() {

#ifndef QT_NO_DEBUG
    qDebug() << "MidiController::triggerMode - ";
#endif

    _currentState->reset();

    emit sigTrigger();

    _currentState = _triggerState;
}

void MidiController::learnMode() {

#ifndef QT_NO_DEBUG
    qDebug() << "MidiController::learnMode - ";
#endif

    _currentState->reset();

    emit sigLearn();

    _currentState = _learnState;
}

void MidiController::syncMode() {

#ifndef QT_NO_DEBUG
    qDebug() << "MidiController::syncMode - ";
#endif

    _currentState->reset();

    emit sigSync();

    _currentState = _syncState;
}

void MidiController::freeWheel() {

#ifndef QT_NO_DEBUG
    qDebug() << "MidiController::freeWheel - ";
#endif

    _currentState->reset();

    emit sigFreewheel();

    _currentState = _freeWheelState;
}

void MidiController::timeOutDetected() {

#ifndef QT_NO_DEBUG
    qDebug() << "MidiController::timeOutDetected - ";
#endif

    freeWheel();
    emit sigTimeout();
}

void MidiController::processMidiEvent( const MidiEvent* event ) {

    emit sigMidiEventRecieved( event );
}

void MidiController::onMidiEventRecieved( const MidiEvent* event ) {

    _currentState->processEvent( event );
}

void MidiController::learnStateCapturedEvent( const MidiEvent* event ) {

    emit sigLearnedEvent( event );
}
