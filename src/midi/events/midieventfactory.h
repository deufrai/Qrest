/*  qrest
 *
 *  Copyright (C) 2008-2012 - Frédéric CORNU
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

#ifndef MIDIEVENTFACTORY_H_
#define MIDIEVENTFACTORY_H_

#include "midievent.h"
#include <vector>

class MidiEventFactory {
private:
    MidiEventFactory();
    virtual ~MidiEventFactory();

public:
    static MidiEvent* createEvent(const std::vector<unsigned char> data);
};

#endif /* MIDIEVENTFACTORY_H_ */
