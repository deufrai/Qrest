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

#include "tapTempoCalculatorTestCase.h"
#include "../helpers/tapTempoTestThread.h"
#include "../../src/model/document.h"

TapTempoCalculatorTestCase::TapTempoCalculatorTestCase() {
}

TapTempoCalculatorTestCase::~TapTempoCalculatorTestCase() {
}

void TapTempoCalculatorTestCase::initTestCase() {

    TapTempoTestThread* pThread = new TapTempoTestThread();

    pThread->start( QThread::TimeCriticalPriority );
    pThread->wait();
}

void TapTempoCalculatorTestCase::testTapTempoAt60BPM() {

    QCOMPARE( Document::getInstance()->getTempo(), 60.0 );
}

void TapTempoCalculatorTestCase::testSteadiness() {

    QVERIFY( Document::getInstance()->isSteady() );
}
