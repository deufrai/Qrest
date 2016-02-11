/*
 *  qrest
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

#ifndef DELAYCALCULATOR_H_
#define DELAYCALCULATOR_H_

#include "processor.h"

/**
 * Processor that calculates delay values according to app data stored
 * tempo value.
 */
class DelayCalculator: public Processor {

private:

    ////////////////////////////////////////////////////////////////////////////
    //
    // INIT
    //
    ////////////////////////////////////////////////////////////////////////////
    DelayCalculator();
    virtual ~DelayCalculator();

    ////////////////////////////////////////////////////////////////////////////
    //
    // SINGLETON IMPLEMENTATION
    //
    ////////////////////////////////////////////////////////////////////////////
    /**
     * The only instance.
     */
    static DelayCalculator* _instance;

public:
    /**
     * init and get the only instance.
     *
     * \return the instance
     */
    static DelayCalculator* getInstance();

    /**
     * destroy the only instance.
     */
    static void destroy( void );

    ////////////////////////////////////////////////////////////////////////////
    //
    // PROCESSOR INTERFACE
    //
    ////////////////////////////////////////////////////////////////////////////
    /**
     * Get tempo from app data store and calculate delays
     */
    virtual void process( void );

private:

    ////////////////////////////////////////////////////////////////////////////
    //
    // FUNCTIONS
    //
    ////////////////////////////////////////////////////////////////////////////
    double getDelayPeriodFromTempoAndMutliplier( const double tempo, const double mutliplier );
};

#endif /* DELAYCALCULATOR_H_ */
