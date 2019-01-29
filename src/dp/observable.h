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

#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <vector>

class Observer;

using std::vector;

/**
 * Observable design pattern abstract Class.
 */

class Observable {

protected:

    ////////////////////////////////////////////////////////////////////////////
    //
    // INIT
    //
    ////////////////////////////////////////////////////////////////////////////
    Observable();
    virtual ~Observable();

public:

    ////////////////////////////////////////////////////////////////////////////
    //
    // INTERFACE
    //
    ////////////////////////////////////////////////////////////////////////////
    /**
     * Register a new observer.
     *
     * Add observer to observers list
     *
     * \param observer the observer to add
     */
    void registerObserver(Observer* observer);

    /**
     * Remove a registered observer.
     *
     * Remove observer from observers list
     *
     * \param observer the observer to remove
     */
    void removeObserver(Observer* observer);

protected:

    ////////////////////////////////////////////////////////////////////////////
    //
    // FUNCTIONS
    //
    ////////////////////////////////////////////////////////////////////////////
    /**
     * Notify all observers to update.
     *
     * Notify all registered observers to update their view.
     */
    void notifyObservers() const;

private:

    ////////////////////////////////////////////////////////////////////////////
    //
    // MEMBERS
    //
    ////////////////////////////////////////////////////////////////////////////
    /** collection of all observers */
    vector<Observer*> _observers;
};

#endif /*OBSERVABLE_H_*/
