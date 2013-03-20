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

#ifndef MIDISIMPLEEVENT_H_
#define MIDISIMPLEEVENT_H_

#include "midievent.h"

/**
 * Abstract type representing a 2 bytes MIDI event
 */
class MidiSimpleEvent: public MidiEvent {

protected:

    /**
     * The only constructor
     *
     * @param channel   affected MIDI channel
     * @param value1    value of byte #1
     */
    MidiSimpleEvent( const unsigned char channel, const unsigned char value1 );

public:
    virtual ~MidiSimpleEvent();

public:

    /**
     * Get affected MIDI channel
     *
     * @return MIDI channel
     */
    inline unsigned char getChannel() const {

        return _channel;
    }

    /**
     * Get value of byte #1
     *
     * @return value of byte #1
     */
    inline unsigned char getValue1() const {

        return _value1;
    }

private:

    /** affected MIDI channel */
    unsigned char _channel;

    /** value of byte #1 */
    unsigned char _value1;
};

#endif /* MIDISIMPLEEVENT_H_ */
