/*  qrest
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

#include "taptriggerstate.h"
#include "../../model/document.h"
#include "../midihelper.h"
#include "../../process/tapTempoCalculator.h"

TapTriggerState::TapTriggerState() {
}

TapTriggerState::~TapTriggerState() {
}

void TapTriggerState::processEvent( const MidiEvent* event ) {

    if( MidiHelper::midiEventMatchesReference( event, Document::getInstance()->getTriggerEvent() ) ) {

        Document::getInstance()->setTempoSource( Document::TEMPO_SOURCE_TAP );
        TapTempoCalculator::getInstance()->process();
    }

    delete event;
}

