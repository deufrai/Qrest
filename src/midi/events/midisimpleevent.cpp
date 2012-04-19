/*
 * midisimpleevent.cpp
 *
 *  Created on: 19 avr. 2012
 *      Author: deufrai
 */

#include "midisimpleevent.h"

MidiSimpleEvent::MidiSimpleEvent(const unsigned char channel, const unsigned char value1)
: _channel(channel),
  _value1(value1) {

}

MidiSimpleEvent::~MidiSimpleEvent() {

}

