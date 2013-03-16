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

#include "delayCalculatorTestCase.h"

#include "../../src/model/document.h"
#include "../../src/model/delay.h"
#include "../../src/process/delayCalculator.h"

void DelayCalculatorTestCase::initTestCase() {

    // Set initial tempo value du 60 BPM.
    Document::getInstance()->setTempo(60);
}

void DelayCalculatorTestCase::testPlainValues() {

    // expected values
    const double EXPECTED_WHOLE_PERIOD = 4000.0;
    const double EXPECTED_HALF_PERIOD = 2000.0;
    const double EXPECTED_QUARTER_PERIOD = 1000.0;
    const double EXPECTED_EIGHTH_PERIOD = 500.0;
    const double EXPECTED_SIXTEENTH_PERIOD = 250.0;
    const double EXPECTED_THIRTYSECOND_PERIOD = 125.0;

    const double EXPECTED_WHOLE_FREQUENCY = 1 / 4.0;
    const double EXPECTED_HALF_FREQUENCY = 1 / 2.0;
    const double EXPECTED_QUARTER_FREQUENCY = 1;
    const double EXPECTED_EIGHTH_FREQUENCY = 2;
    const double EXPECTED_SIXTEENTH_FREQUENCY = 4;
    const double EXPECTED_THIRTYSECOND_FREQUENCY = 8;

    Document* pDocument = Document::getInstance();

    pDocument->setMultiplier(Document::MULTIPLIER_PLAIN);

    DelayCalculator::getInstance()->process();

    QCOMPARE(pDocument->getWholeDelay()->getPeriod(), EXPECTED_WHOLE_PERIOD);
    QCOMPARE(pDocument->getHalfDelay()->getPeriod(), EXPECTED_HALF_PERIOD);
    QCOMPARE(pDocument->getQuarterDelay()->getPeriod(), EXPECTED_QUARTER_PERIOD);
    QCOMPARE(pDocument->getEighthDelay()->getPeriod(), EXPECTED_EIGHTH_PERIOD);
    QCOMPARE(pDocument->getSixTeenthDelay()->getPeriod(), EXPECTED_SIXTEENTH_PERIOD);
    QCOMPARE(pDocument->getThirtySecondDelay()->getPeriod(), EXPECTED_THIRTYSECOND_PERIOD);

    QCOMPARE(pDocument->getWholeDelay()->getFrequency(), EXPECTED_WHOLE_FREQUENCY);
    QCOMPARE(pDocument->getHalfDelay()->getFrequency(), EXPECTED_HALF_FREQUENCY);
    QCOMPARE(pDocument->getQuarterDelay()->getFrequency(), EXPECTED_QUARTER_FREQUENCY);
    QCOMPARE(pDocument->getEighthDelay()->getFrequency(), EXPECTED_EIGHTH_FREQUENCY);
    QCOMPARE(pDocument->getSixTeenthDelay()->getFrequency(), EXPECTED_SIXTEENTH_FREQUENCY);
    QCOMPARE(pDocument->getThirtySecondDelay()->getFrequency(), EXPECTED_THIRTYSECOND_FREQUENCY);
}

void DelayCalculatorTestCase::testDottedValues() {

    // expected values
    const double EXPECTED_WHOLE_PERIOD = 4000.0 * 1.5;
    const double EXPECTED_HALF_PERIOD = 2000.0 * 1.5;
    const double EXPECTED_QUARTER_PERIOD = 1000.0 * 1.5;
    const double EXPECTED_EIGHTH_PERIOD = 500.0 * 1.5;
    const double EXPECTED_SIXTEENTH_PERIOD = 250.0 * 1.5;
    const double EXPECTED_THIRTYSECOND_PERIOD = 125.0 * 1.5;

    const double EXPECTED_WHOLE_FREQUENCY = 1 / 4.0 * 2 / 3.0;
    const double EXPECTED_HALF_FREQUENCY = 1 / 2.0 * 2 / 3.0;
    const double EXPECTED_QUARTER_FREQUENCY = 1 * 2 / 3.0;
    const double EXPECTED_EIGHTH_FREQUENCY = 2 * 2 / 3.0;
    const double EXPECTED_SIXTEENTH_FREQUENCY = 4 * 2 / 3.0;
    const double EXPECTED_THIRTYSECOND_FREQUENCY = 8 * 2 / 3.0;

    Document* pDocument = Document::getInstance();

    pDocument->setMultiplier(Document::MULTIPLIER_DOTTED);

    DelayCalculator::getInstance()->process();

    QCOMPARE(pDocument->getWholeDelay()->getPeriod(), EXPECTED_WHOLE_PERIOD);
    QCOMPARE(pDocument->getHalfDelay()->getPeriod(), EXPECTED_HALF_PERIOD);
    QCOMPARE(pDocument->getQuarterDelay()->getPeriod(), EXPECTED_QUARTER_PERIOD);
    QCOMPARE(pDocument->getEighthDelay()->getPeriod(), EXPECTED_EIGHTH_PERIOD);
    QCOMPARE(pDocument->getSixTeenthDelay()->getPeriod(), EXPECTED_SIXTEENTH_PERIOD);
    QCOMPARE(pDocument->getThirtySecondDelay()->getPeriod(), EXPECTED_THIRTYSECOND_PERIOD);

    QCOMPARE(pDocument->getWholeDelay()->getFrequency(), EXPECTED_WHOLE_FREQUENCY);
    QCOMPARE(pDocument->getHalfDelay()->getFrequency(), EXPECTED_HALF_FREQUENCY);
    QCOMPARE(pDocument->getQuarterDelay()->getFrequency(), EXPECTED_QUARTER_FREQUENCY);
    QCOMPARE(pDocument->getEighthDelay()->getFrequency(), EXPECTED_EIGHTH_FREQUENCY);
    QCOMPARE(pDocument->getSixTeenthDelay()->getFrequency(), EXPECTED_SIXTEENTH_FREQUENCY);
    QCOMPARE(pDocument->getThirtySecondDelay()->getFrequency(), EXPECTED_THIRTYSECOND_FREQUENCY);
}

void DelayCalculatorTestCase::testTripletValues() {

    // expected values
    const double EXPECTED_WHOLE_PERIOD = 4000.0 * 2 / 3.0;
    const double EXPECTED_HALF_PERIOD = 2000.0 * 2 / 3.0;
    const double EXPECTED_QUARTER_PERIOD = 1000.0 * 2 / 3.0;
    const double EXPECTED_EIGHTH_PERIOD = 500.0 * 2 / 3.0;
    const double EXPECTED_SIXTEENTH_PERIOD = 250.0 * 2 / 3.0;
    const double EXPECTED_THIRTYSECOND_PERIOD = 125.0 * 2 / 3.0;

    const double EXPECTED_WHOLE_FREQUENCY = 1 / 4.0 * 1.5;
    const double EXPECTED_HALF_FREQUENCY = 1 / 2.0 * 1.5;
    const double EXPECTED_QUARTER_FREQUENCY = 1 * 1.5;
    const double EXPECTED_EIGHTH_FREQUENCY = 2 * 1.5;
    const double EXPECTED_SIXTEENTH_FREQUENCY = 4 * 1.5;
    const double EXPECTED_THIRTYSECOND_FREQUENCY = 8 * 1.5;

    Document* pDocument = Document::getInstance();

    pDocument->setMultiplier(Document::MULTIPLIER_TRIPLET);

    DelayCalculator::getInstance()->process();

    QCOMPARE(pDocument->getWholeDelay()->getPeriod(), EXPECTED_WHOLE_PERIOD);
    QCOMPARE(pDocument->getHalfDelay()->getPeriod(), EXPECTED_HALF_PERIOD);
    QCOMPARE(pDocument->getQuarterDelay()->getPeriod(), EXPECTED_QUARTER_PERIOD);
    QCOMPARE(pDocument->getEighthDelay()->getPeriod(), EXPECTED_EIGHTH_PERIOD);
    QCOMPARE(pDocument->getSixTeenthDelay()->getPeriod(), EXPECTED_SIXTEENTH_PERIOD);
    QCOMPARE(pDocument->getThirtySecondDelay()->getPeriod(), EXPECTED_THIRTYSECOND_PERIOD);

    QCOMPARE(pDocument->getWholeDelay()->getFrequency(), EXPECTED_WHOLE_FREQUENCY);
    QCOMPARE(pDocument->getHalfDelay()->getFrequency(), EXPECTED_HALF_FREQUENCY);
    QCOMPARE(pDocument->getQuarterDelay()->getFrequency(), EXPECTED_QUARTER_FREQUENCY);
    QCOMPARE(pDocument->getEighthDelay()->getFrequency(), EXPECTED_EIGHTH_FREQUENCY);
    QCOMPARE(pDocument->getSixTeenthDelay()->getFrequency(), EXPECTED_SIXTEENTH_FREQUENCY);
    QCOMPARE(pDocument->getThirtySecondDelay()->getFrequency(), EXPECTED_THIRTYSECOND_FREQUENCY);

}
