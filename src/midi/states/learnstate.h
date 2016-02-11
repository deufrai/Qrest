/*  qrest
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

#ifndef LEARNSTATE_H_
#define LEARNSTATE_H_

#include <QObject>
#include "midistate.h"

/**
 * The learning state in which we switch when user is requested to trigger
 * the event that will itself trigger the TAP function.
 */
class LearnState: public MidiState {

public:
    LearnState();
    virtual ~LearnState();

    virtual void reset() {
    } // don't think we would need to do anything in here

    virtual void processEvent( const MidiEvent* event );
};

#endif /* LEARNSTATE_H_ */
