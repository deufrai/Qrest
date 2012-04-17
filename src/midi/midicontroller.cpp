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

MidiController* MidiController::_instance = 0;

MidiController::MidiController()
: _synchroTimeoutTimer(new QTimer(this)),
  _midiEngine(MidiEngine::getInstance())

{

	_synchroTimeoutTimer->setSingleShot(true);

	connect(_synchroTimeoutTimer, SIGNAL(timeout()), this, SLOT(onSyncTimeout()));
}

MidiController::~MidiController() {

}

void MidiController::midiQuarter() {

	_synchroTimeoutTimer->start(Constants::MIDI_SYNC_TIMEOUT_MS);
	emit bip();
}

void MidiController::midiStart() {

	emit start();
}

void MidiController::midiStop() {

	_synchroTimeoutTimer->stop();
	emit stop();
}

void MidiController::midiSyncStart() {

	_midiEngine->init();
	_midiEngine->openVirtualPort();
	_midiEngine->start();
}

void MidiController::midiSyncStop() {

	_synchroTimeoutTimer->stop();
	_midiEngine->stop();
	_midiEngine->closePort();
	_midiEngine->cleanup();
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


