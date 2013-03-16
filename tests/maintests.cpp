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

#include <QCoreApplication>
#include <QList>
#include "process/delayCalculatorTestCase.h"
#include "process/tapTempoCalculatorTestCase.h"

/*
 * Launching every testcase
 */
int main(int argc, char** argv) {

    QCoreApplication app(argc, argv);

    /*
     * List of all tests to be ran.
     */
    QList<QObject*> tests;

    /*
     * populate a list of all testscases we want to run.
     */
    tests << new DelayCalculatorTestCase();
    tests << new TapTempoCalculatorTestCase();

    bool someTestsFailed = false;
    int status = 0;

    /*
     * Run all tests and remember if at leasst one of them failed.
     */
    foreach (QObject* test, tests)
        {

            status = QTest::qExec(test, argc, argv);

            if (!someTestsFailed && 0 != status) {

                someTestsFailed = true;
            }
        }

    /*
     * We return 0 if no failure occured, otherwise : 1.
     */
    return someTestsFailed ? 1 : 0;
}
