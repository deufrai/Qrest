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

#ifndef TAPTEMPOTESTTHREAD_H_
#define TAPTEMPOTESTTHREAD_H_

#include <QThread>

/*
 * Helper for TapTempoCalculatorTestCase.
 *
 * simulates a human user clicking 4 times on the UI TAP button at 60 BPM.
 */
class TapTempoTestThread : public QThread {

public:
	TapTempoTestThread();
	virtual ~TapTempoTestThread();

	void run();
};

#endif /* TAPTEMPOTESTTHREAD_H_ */
