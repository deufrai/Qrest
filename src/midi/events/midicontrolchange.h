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

#ifndef MIDICONTROLCHANGE_H_
#define MIDICONTROLCHANGE_H_

#include "mididoubleevent.h"

class MidiControlChange: public MidiDoubleEvent {
public:
    MidiControlChange(const unsigned char channel, const unsigned char value1, const unsigned char value2);
    virtual ~MidiControlChange();
};

#endif /* MIDICONTROLCHANGE_H_ */
