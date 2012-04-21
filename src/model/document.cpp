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

#include "document.h"
#include "../process/delayCalculator.h"

////////////////////////////////////////////////////////////////////////////////
//
// INIT
//
////////////////////////////////////////////////////////////////////////////////

Document* Document::_instance = 0;

Document::Document() :
    _tempo(Constants::TEMPO_DEFAULT),
    _steady(true),
    _steadiness(FULL_STEADINESS),
    _tempoSource(TEMPO_SOURCE_KEYBOARD),
    _multiplier(MULTIPLIER_PLAIN),
    _midiClockRunning(false),
    _midiClockTimeout(false) {

    // init vector of Delay objects
    initDelays();

}

Document::~Document() {

    // destroy delays
    destroyDelays();

    // destroy DelayCalculator
    DelayCalculator::destroy();
}

Document* Document::getInstance() {

    if (0 == _instance) {

        _instance = new Document();
    }

    return _instance;
}

void Document::destroy() {

    if (_instance) {

        delete _instance;
        _instance = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// MEMBER FUNCTIONS
//
////////////////////////////////////////////////////////////////////////////////

void Document::setTempo(const double tempo) {

    if ((Constants::TEMPO_MIN <= tempo && tempo <= Constants::TEMPO_MAX)) {

        _tempo = tempo;
        updateDelays();
    }

    notifyObservers();
}

////////////////////////////////////////////////////////////////////////////////
//
// PRIVATE FUNCTIONS
//
////////////////////////////////////////////////////////////////////////////////
void Document::initDelays(void) {

    for (int i = 0; i < DELAYS_COUNT; i++) {

        _delays.push_back(new Delay());
    }
}

void Document::destroyDelays(void) {

    for (int i = 0; i < DELAYS_COUNT; i++) {

        delete _delays[i];
        _delays[i] = 0;
    }

    _delays.clear();

}

void Document::updateDelays(void) {

    DelayCalculator::getInstance()->process();
}
