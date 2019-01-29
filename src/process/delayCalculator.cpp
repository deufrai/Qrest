/*
 *  qrest
 *
 *  Copyright (C) 2008-2019 - Frédéric CORNU
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

#include "delayCalculator.h"
#include "../model/document.h"
#include "../model/delay.h"
#include "../constants.h"

////////////////////////////////////////////////////////////////////////////////
//
// INIT
//
////////////////////////////////////////////////////////////////////////////////

DelayCalculator* DelayCalculator::_instance = 0;

DelayCalculator::DelayCalculator() {
}

DelayCalculator::~DelayCalculator() {
}

DelayCalculator* DelayCalculator::getInstance(void) {

    if (0 == _instance) {

        _instance = new DelayCalculator();
    }

    return _instance;
}

void DelayCalculator::destroy(void) {

    delete _instance;
    _instance = 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// PROCESSOR INTERFACE
//
////////////////////////////////////////////////////////////////////////////////
void DelayCalculator::process(void) {

    /*
     * all constants are declared as double, in order not to worry about
     * those dreaded integer divisions.
     */

    // mutliplier from a quarter to a whole note
    static const double QUARTER_TO_WHOLE_MUTLT = 4.0;

    // mutliplier from a quarter to a half note
    static const double QUARTER_TO_HALF_MUTLT = 2.0;

    // mutliplier from a quarter to a quarter note
    static const double QUARTER_TO_QUARTER_MUTLT = 1.0;

    // mutliplier from a quarter to a eighth note
    static const double QUARTER_TO_EIGHTH_MUTLT = 1 / 2.0;

    // mutliplier from a quarter to a sixteenth note
    static const double QUARTER_TO_SIXTEENTH_MUTLT = 1 / 4.0;

    // mutliplier from a quarter to a thirtysecond note
    static const double QUARTER_TO_THIRTYSECOND_MUTLT = 1 / 8.0;

    // get data store
    Document* pDocument = Document::getInstance();

    // get tempo value
    double tempo = pDocument->getTempo();

    // get alteration multiplier
    double alterationMultiplier = pDocument->getMultiplier();

    // do the math
    pDocument->getWholeDelay()->setPeriod(

            getDelayPeriodFromTempoAndMutliplier(tempo, QUARTER_TO_WHOLE_MUTLT
                                                 * alterationMultiplier));

    pDocument->getHalfDelay()->setPeriod(

            getDelayPeriodFromTempoAndMutliplier(tempo, QUARTER_TO_HALF_MUTLT
                                                 * alterationMultiplier));

    pDocument->getQuarterDelay()->setPeriod(

            getDelayPeriodFromTempoAndMutliplier(tempo, QUARTER_TO_QUARTER_MUTLT
                                                 * alterationMultiplier));

    pDocument->getEighthDelay()->setPeriod(

            getDelayPeriodFromTempoAndMutliplier(tempo, QUARTER_TO_EIGHTH_MUTLT
                                                 * alterationMultiplier));

    pDocument->getSixTeenthDelay()->setPeriod(

            getDelayPeriodFromTempoAndMutliplier(tempo, QUARTER_TO_SIXTEENTH_MUTLT
                                                 * alterationMultiplier));

    pDocument->getThirtySecondDelay()->setPeriod(

            getDelayPeriodFromTempoAndMutliplier(tempo, QUARTER_TO_THIRTYSECOND_MUTLT
                                                 * alterationMultiplier));

}

////////////////////////////////////////////////////////////////////////////////
//
// PRIVATE FUNCTIONS
//
////////////////////////////////////////////////////////////////////////////////
double DelayCalculator::getDelayPeriodFromTempoAndMutliplier(const double tempo, const double multiplier) {

    return Constants::SECONDS_PER_MINUTE / tempo * Constants::MILLISEC_PER_SECOND * multiplier;
}

