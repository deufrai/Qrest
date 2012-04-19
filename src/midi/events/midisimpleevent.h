/*
 * midisimpleevent.h
 *
 *  Created on: 19 avr. 2012
 *      Author: deufrai
 */

#ifndef MIDISIMPLEEVENT_H_
#define MIDISIMPLEEVENT_H_

#include "midievent.h"

class MidiSimpleEvent: public MidiEvent {

protected:
    MidiSimpleEvent(const unsigned char channel, const unsigned char value1);
    virtual ~MidiSimpleEvent();

public:
    inline unsigned char getChannel () const {

        return _channel;
    }

    inline unsigned char getValue1 () const {

        return _value1;
    }

private:
    unsigned char _channel;
    unsigned char _value1;
};

#endif /* MIDISIMPLEEVENT_H_ */
