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

#include "midibroadcaster.h"
#include "../process/tapTempoCalculator.h"
#include "../model/document.h"

MidiBroadcaster* MidiBroadcaster::_instance = 0;

MidiBroadcaster::MidiBroadcaster()
: _synchroTimeoutTimer(new QTimer(this)) {

	_synchroTimeoutTimer->setSingleShot(true);

	connect(_synchroTimeoutTimer, SIGNAL(timeout()), this, SLOT(onSyncTimeout()));
}

MidiBroadcaster::~MidiBroadcaster() {

}

void MidiBroadcaster::onMidiQuarter() {

	_synchroTimeoutTimer->start(Constants::MIDI_SYNC_TIMEOUT_MS);
	emit bip();
}

void MidiBroadcaster::onMidiStart() {

	emit start();
}

void MidiBroadcaster::onMidiStop() {

	_synchroTimeoutTimer->stop();
	emit stop();
}

void MidiBroadcaster::onSyncTimeout() {

	emit stop();
}


MidiBroadcaster* MidiBroadcaster::getInstance() {

	if ( 0 == _instance ) {

		_instance = new MidiBroadcaster();
	}

	return _instance;
}

void MidiBroadcaster::onBip() {

	Document::getInstance()->setTempoSource(Document::TEMPO_SOURCE_MIDI);
	Document::getInstance()->setMidiClockRunning(true);
	TapTempoCalculator::getInstance()->process();

}

void MidiBroadcaster::onStart() {

	Document::getInstance()->setMidiClockRunning(true);
}

void MidiBroadcaster::onStop() {

	Document::getInstance()->setMidiClockRunning(false);
}



