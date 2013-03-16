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

#ifndef TAPTEMPOCALCULATOR_H_
#define TAPTEMPOCALCULATOR_H_

#include <list>

#include "processor.h"

class TimeStamper;

using std::list;

/**
 * Calculate tempo from an average of several collected time intervals beetween
 * quarter notes.
 *
 * Implemented as a singleton.
 */
class TapTempoCalculator: public Processor {

    ////////////////////////////////////////////////////////////////////////////
    //
    // CONSTANTS
    //
    ////////////////////////////////////////////////////////////////////////////
private:
    /** We use 3 collected deltas to guess tempo */
    static const int DELTAS_COUNT = 3;

    ////////////////////////////////////////////////////////////////////////////
    //
    // INIT
    //
    ////////////////////////////////////////////////////////////////////////////
private:
    TapTempoCalculator();
    virtual ~TapTempoCalculator();

    ////////////////////////////////////////////////////////////////////////////
    //
    // SINGLETON
    //
    ////////////////////////////////////////////////////////////////////////////
private:
    /** The single instance */
    static TapTempoCalculator* _instance;

public:
    /**
     * ceate and get the only instance.
     *
     * \return the instance.
     */
    static TapTempoCalculator* getInstance();

    ////////////////////////////////////////////////////////////////////////////
    //
    // INTERFACE
    //
    ////////////////////////////////////////////////////////////////////////////
public:
    /**
     * Collects timestamp and calculates tempo from previsouly gathered ones
     */
    virtual void process();

    ////////////////////////////////////////////////////////////////////////////
    //
    // PRIVATE FUNCTIONS
    //
    ////////////////////////////////////////////////////////////////////////////
private:
    /**
     * init the list of deltas
     */
    void initDeltas();

    /**
     * get the average delta from all deltas in list
     *
     * \return the average of all deltas in list
     */
    double getAverageDelta() const;

    /**
     * are deltas within a narrow range ?
     *
     * \return a boolean describing steadiness
     */
    void getSteadiness() const;

    ////////////////////////////////////////////////////////////////////////////
    //
    // MEMBERS
    //
    ////////////////////////////////////////////////////////////////////////////
private:
    /** provides timestamps on demand */
    TimeStamper* _pTimeStamper;

    /** stores deltas between collected timestamps */
    list<int> _deltas;
};

#endif /* TAPTEMPOCALCULATOR_H_ */
