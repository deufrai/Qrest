/*
 *  qrest
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

#ifndef MIDIDOUBLEEVENT_H_
#define MIDIDOUBLEEVENT_H_

#include "midisimpleevent.h"

class MidiDoubleEvent: public MidiSimpleEvent {
public:
    MidiDoubleEvent(const unsigned char channel, const unsigned char value1, const unsigned char value2);
    virtual ~MidiDoubleEvent();

    inline unsigned char getValue2() const {

        return _value2;
    }

private:
    unsigned char _value2;
};

#endif /* MIDIDOUBLEEVENT_H_ */
