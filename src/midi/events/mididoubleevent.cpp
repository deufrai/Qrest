/*
 * mididoubleevent.cpp
 *
 *  Created on: 19 avr. 2012
 *      Author: deufrai
 */

#include "mididoubleevent.h"

MidiDoubleEvent::MidiDoubleEvent(const unsigned char channel, const unsigned char value1, const unsigned char value2)
: MidiSimpleEvent (channel, value1),
  _value2(value2) {

}

MidiDoubleEvent::~MidiDoubleEvent() {

}

