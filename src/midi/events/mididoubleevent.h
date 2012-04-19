/*
 * mididoubleevent.h
 *
 *  Created on: 19 avr. 2012
 *      Author: deufrai
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
