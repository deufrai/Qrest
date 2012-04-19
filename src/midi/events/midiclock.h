/*
 * midiClock.h
 *
 *  Created on: 19 avr. 2012
 *      Author: deufrai
 */

#ifndef MIDICLOCK_H_
#define MIDICLOCK_H_

#include "midievent.h"

class MidiClock: public MidiEvent {
public:
    MidiClock();
    virtual ~MidiClock();
};

#endif /* MIDICLOCK_H_ */
