/*
 * midipogramchange.cpp
 *
 *  Created on: 19 avr. 2012
 *      Author: deufrai
 */

#include "midiprogramchange.h"

MidiProgramChange::MidiProgramChange(const unsigned char channel, const unsigned char program)
: MidiSimpleEvent(channel, program) {


}

MidiProgramChange::~MidiProgramChange() {

}

