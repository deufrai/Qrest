/*
 * midistart.h
 *
 *  Created on: 19 avr. 2012
 *      Author: deufrai
 */

#ifndef MIDISTART_H_
#define MIDISTART_H_

#include "midievent.h"

class MidiStart: public MidiEvent {
public:
    MidiStart();
    virtual ~MidiStart();
};

#endif /* MIDISTART_H_ */
