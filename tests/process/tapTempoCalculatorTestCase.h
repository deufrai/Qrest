/*
 *  qrest
 *
 *  Copyright (C) 2008-2009 - Frédéric CORNU
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

#ifndef TAPTEMPOCALCULATORTESTCASE_H_
#define TAPTEMPOCALCULATORTESTCASE_H_

#include <QtTest/QtTest>

/*
 * Unit tests against TapTempoCalculator.
 */
class TapTempoCalculatorTestCase : public QObject {

	Q_OBJECT

public:
	TapTempoCalculatorTestCase();
	virtual ~TapTempoCalculatorTestCase();

private slots:
	/*
	 * test fixture : simulates 4 taps at 60 BPM.
	 */
	void initTestCase();

	/*
	 * actual tests.
	 */
	void testTapTempoAt60BPM();
	void testSteadiness();
};

#endif /* TAPTEMPOCALCULATORTESTCASE_H_ */
