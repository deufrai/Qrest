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

MidiController* MidiController::_instance = 0;

MidiController::MidiController()
    : _synchroTimeoutTimer(new QTimer(this)),
      _midiEngine(MidiEngine::getInstance())

{

    // Setup MIDI Clock timeout detector
    _synchroTimeoutTimer->setSingleShot(true);
    _synchroTimeoutTimer->setInterval(Constants::MIDI_SYNC_TIMEOUT_MS);
    connect(_synchroTimeoutTimer, SIGNAL(timeout()), this, SLOT(onSyncTimeout()));

    // setup connections
    QObject::connect(this,
                     SIGNAL(bip()),
                     this,
                     SLOT(onBip()));


    QObject::connect(this,
                     SIGNAL(start()),
                     this,
                     SLOT(onStart()));


    QObject::connect(this,
                     SIGNAL(stop()),
                     this,
                     SLOT(onStop()));

    QObject::connect(this,
                     SIGNAL(stopTimeoutDetector()),
                     this,
                     SLOT(onStopTimeoutDetector()));

    QObject::connect(this,
                     SIGNAL(startTimeoutDetector()),
                     this,
                     SLOT(onStartTimeoutDetector()));



    // startup MIDI engine
    _midiEngine->init();


}

MidiController::~MidiController() {

    _midiEngine->stop();
    _midiEngine->closePort();
    _midiEngine->cleanup();
}

void MidiController::midiQuarter() {

    emit startTimeoutDetector();
    emit bip();
}

void MidiController::midiStart() {

    emit start();
}

void MidiController::midiStop() {

    emit stopTimeoutDetector();
    emit stop();
}

void MidiController::midiSyncStart() {

    _midiEngine->setSlave(true);
}

void MidiController::midiSyncStop() {

    _midiEngine->setSlave(false);
    stopTimeoutDetector();
    Document::getInstance()->setMidiClockRunning(false);

}

void MidiController::onSyncTimeout() {

    Document::getInstance()->setMidiClockRunning(false);
    emit lost_synchro();
}


MidiController* MidiController::getInstance() {

    if ( 0 == _instance ) {

        _instance = new MidiController();
    }

    return _instance;
}

void MidiController::onBip() {

    Document::getInstance()->setTempoSource(Document::TEMPO_SOURCE_MIDI);
    Document::getInstance()->setMidiClockRunning(true);
    TapTempoCalculator::getInstance()->process();

}

void MidiController::onStart() {

    Document::getInstance()->setMidiClockRunning(true);
}

void MidiController::onStop() {

    Document::getInstance()->setMidiClockRunning(false);
}


void MidiController::resetEngine() {

    emit reset();

    closePort();
    _midiEngine->cleanup();

    _midiEngine->init();
    openPort();
}

const std::vector<std::string> MidiController::getDeviceNames() {

    return _midiEngine->getDeviceNames();
}

bool MidiController::openPort( ) {

    std::string portName = Settings::getInstance()->getSettings().value(
                Settings::MIDI_DEVICE,
                Settings::MIDI_DEVICE_DEFAULT
                ).toString().toStdString();

    if ( _midiEngine->openPort(portName) ) {

        _midiEngine->start();
        return true;

    } else {

        return false;
    }

}

void MidiController::closePort() {

    Document::getInstance()->setMidiClockRunning(false);
    _midiEngine->stop();
    _midiEngine->closePort();
}


bool MidiController::resetPort() {

    emit reset();
    closePort();
    return openPort();
}

void MidiController::onStartTimeoutDetector() {

    _synchroTimeoutTimer->start();
}


void MidiController::onStopTimeoutDetector() {

    _synchroTimeoutTimer->stop();
}
