/*  qrest
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

#include "syncstate.h"
#include "../../model/document.h"
#include "../events/midicontinue.h"
#include "../events/midistart.h"
#include "../events/midistop.h"
#include "../events/midiclock.h"
#include "../../constants.h"
#include "../../process/tapTempoCalculator.h"
#include "../../midi/midicontroller.h"

SyncState::SyncState()
: _midiClockCounter(0),
  _midiClockTimeoutDetector(new QTimer()) {

    /*
     * Initialise time out detector timer :
     *
     *  - single shot
     *  - connected to our own slot
     */
    _midiClockTimeoutDetector->setSingleShot(true);
    _midiClockTimeoutDetector->setInterval(Constants::MIDI_SYNC_TIMEOUT_MS);
    connect(_midiClockTimeoutDetector, SIGNAL(timeout()), this, SLOT(onMidiClockTimeoutDetectorTimeout()));
}

SyncState::~SyncState() { }

void SyncState::reset() {

    _midiClockTimeoutDetector->stop();
    Document::getInstance()->setMidiClockRunning(false);
}

void SyncState::onMidiClockTimeoutDetectorTimeout() {

    MidiController::getInstance()->timeOutDetected();
}

void SyncState::processEvent(const MidiEvent* event) {

    if ( dynamic_cast<const MidiContinue*> (event) != 0 ||
         dynamic_cast<const MidiStart*> (event) != 0 ) {

        /*
         * MidiStart & MidiContinue
         * ========================
         *
         * We handle them the same way, as MidiContinue is just a start from
         * anywhere else than the beginning of the source timeline
         */

        // We tell everyone that we are now following external sync
        
        _midiClockCounter = 0;
        Document::getInstance()->setMidiClockRunning(true);


    } else if ( dynamic_cast<const MidiStop*> (event) != 0 ) {

        /*
         * MidiStop
         * ========
         *
         * We tell everyone that we are no longer following external sync
         * and disable timeout detector
         */
        Document::getInstance()->setMidiClockRunning(false);
        _midiClockTimeoutDetector->stop();


    } else if ( dynamic_cast<const MidiClock*> (event) != 0 ) {

        /*
         * MidiClock
         * ========
         *
         * Midi Clock events are sent 24 times every 4th note.
         * So we count them intill we have 24 and then trigger a tempo calculation
         *
         */      
        if ( ++_midiClockCounter == Constants::MIDI_CLOCK_EVENTS_PER_QUARTER ) {
            
            /*
             * we want the GUI to update correctly, even if we enter slave mode
             * AFTER the Midi Start event has been sent
             */
            Document::getInstance()->setMidiClockRunning(true);
            
            _midiClockCounter = 0;            
            Document::getInstance()->setTempoSource(Document::TEMPO_SOURCE_MIDI_CLOCK);
            TapTempoCalculator::getInstance()->process();
        }

        // reset the MIDI clock timeout detector for another cycle
        _midiClockTimeoutDetector->start();
    }

    // discard event
    delete event;
}
