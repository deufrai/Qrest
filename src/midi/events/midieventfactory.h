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
#include "midinoteon.h"
#include "midiprogramchange.h"
#include <QStringList>

/**
 * Factory for MIDI events
 */
class MidiEventFactory {
private:
    MidiEventFactory();
    virtual ~MidiEventFactory();

public:

    /**
     * Create a MidiEvent from raw data.
     *
     * Will return NULL if event's type is not of :
     *
     * - Note ON
     * - Program change
     * - Midi Clock
     * - Midi Start
     * - Midi Stop
     * - Midi Continue
     *
     * @param data raw data provided by the MIDI engine
     *
     * @return a pointer to MidiEvent
     */
    static MidiEvent* createEvent(const std::vector<unsigned char>* data);

    /**
     * Create a MidiEvent from a string representation that was sed to store app settings.
     *
     * Will return NULL if string doesn't represent one of these type of events :
     *
     * - Note ON
     * - Program change
     *
     * @param list : the string representation
     *
     * @return a pointer to MidiEvent
     */
    static const MidiEvent* createEvent(const QStringList& list);

};

#endif /* MIDIEVENTFACTORY_H_ */
