/*
 *  zest
 *
 *  Copyright (C) 2008 - Frédéric CORNU
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

#ifndef DELAY_H_
#define DELAY_H_

#include "../constants.h"

/**
 * Represents a delay for which we want to display two values
 * <ul>
 * <li> The period in milliseconds </li>
 * <li> The frequency of an LFO beating at that period </li>
 * </ul>
 */
class Delay
{
public:

    // INIT
	Delay();
	virtual ~Delay();

	// ACCESS
    /**
     * Set the period.
     * Frequency gets set as well to 1 / period * 1000
     *
     * \param period the period to be set
     */
    inline void setPeriod(const double period) {

    	_period = period;
    	_frequency = 1 / _period * Constants::MILLISEC_PER_SECOND;
    }

    /**
     * Get the period.
     * \return the period
     */
    inline const double getPeriod() const { return _period; }

    /**
     * Get the frenquency.
     * \return the frenquency
     */
    inline const double getFrenquency() const { return _frequency; }

private:

    // MEMBERS

    /** the period of this delay */
    double _period;

    /** the frequency corresponding to the period of this delay */
    double _frequency;

};

#endif /*DELAY_H_*/
