/*
 * midiprogramchange.h
 *
 *  Created on: 19 avr. 2012
 *      Author: deufrai
 */

#ifndef MIDIPROGRAMCHANGE_H_
#define MIDIPROGRAMCHANGE_H_

#include "midisimpleevent.h"

class MidiProgramChange: public MidiSimpleEvent {
public:
    MidiProgramChange(const unsigned char channel, const unsigned char program);
    virtual ~MidiProgramChange();
};

#endif /* MIDIPROGRAMCHANGE_H_ */
