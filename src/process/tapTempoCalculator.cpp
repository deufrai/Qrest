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

#include <QtGlobal>
#include <algorithm>
#include "tapTempoCalculator.h"
#include "../model/document.h"
#include "../constants.h"
#include "../time/timeStamper.h"

////////////////////////////////////////////////////////////////////////////////
//
// INIT / SINGLETON
//
////////////////////////////////////////////////////////////////////////////////
TapTempoCalculator* TapTempoCalculator::_instance = 0;

TapTempoCalculator::~TapTempoCalculator() {

}

TapTempoCalculator::TapTempoCalculator() :
    _pTimeStamper(new TimeStamper()) {

    /** init deltas collection with default data */
    initDeltas();
}

TapTempoCalculator* TapTempoCalculator::getInstance() {

    if (0 == _instance) {

        _instance = new TapTempoCalculator();
    }

    return _instance;
}

////////////////////////////////////////////////////////////////////////////////
//
// INTERFACE
//
////////////////////////////////////////////////////////////////////////////////
void TapTempoCalculator::process() {

    // the last timestamp will be 0 on first call of this function
    static int lastStamp = 0;

    // get pointer to document
    Document* pDocument = Document::getInstance();

    // get current timestamp
    int currentStamp = _pTimeStamper->getStamp();

    // store delta between current timestamp and last one
    _deltas.push_back(currentStamp - lastStamp);
    _deltas.pop_front();

    // are deltas steady ?
    getSteadiness();

    // set tempo according to average
    double averageDelta = getAverageDelta();
    pDocument->setTempo(qRound(Constants::SECONDS_PER_MINUTE
            * Constants::MILLISEC_PER_SECOND / averageDelta));

    // store current stamp for next call
    lastStamp = currentStamp;
}

////////////////////////////////////////////////////////////////////////////////
//
// PRIVATE FUNCTIONS
//
////////////////////////////////////////////////////////////////////////////////
void TapTempoCalculator::initDeltas() {

    for (int i = 0; i < DELTAS_COUNT; i++) {

        _deltas.push_back(0);
    }
}

double TapTempoCalculator::getAverageDelta() const {

    list<int>::const_iterator it = _deltas.begin();
    long sum = 0;

    while (it != _deltas.end()) {

        sum += *it;
        it++;
    }

    return static_cast<double> (sum) / DELTAS_COUNT;
}

void TapTempoCalculator::getSteadiness() const {

    /*
     * we get the minimum delta, the maximum and return true if they're
     * enclosed withing a range expressed as a ratio. STEADY_RATIO
     */
    Document* pDocument = Document::getInstance();

    list<int>::const_iterator begin = _deltas.begin();
    list<int>::const_iterator end = _deltas.end();

    list<int>::const_iterator min = min_element(begin, end);
    list<int>::const_iterator max = max_element(begin, end);

    double steadiness = (static_cast<double> (*min) / *max);

    pDocument->setSteadiness(steadiness);
    pDocument->setSteady(steadiness > Constants::STEADINESS_TARGET_RATIO);
}
