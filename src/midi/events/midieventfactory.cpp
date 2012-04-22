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

#include "midieventfactory.h"
#include "midinoteon.h"
#include <iostream>
#include "midiprogramchange.h"
#include "midistart.h"
#include "midicontinue.h"
#include "midistop.h"
#include "midiclock.h"
#include "../midihelper.h"
#include <QStringList>
#include "../../constants.h"

MidiEventFactory::MidiEventFactory() {
}

MidiEventFactory::~MidiEventFactory() {
}

MidiEvent* MidiEventFactory::createEvent(
        const std::vector<unsigned char>* data) {

    /*
     * Note and program change share the same fist byte structure :
     *
     * the type of event is coded on the 4 msb
     * the channel is coded on the 4 lsb
     *
     * The fact that they use channel information makes them part of what is called
     * the voice messages Category
     */
    static const unsigned char TYPE_NOTE_ON = 0x90;
    static const unsigned char TYPE_PROGRAM_CHANGE = 0xC0;

    /*
     * all events whose byte #0 value is greater that 0xEF dont have channel information
     * their type is coded in the whole first byte
     */
    static const unsigned char TYPE_CLOCK_START = 0xFA;
    static const unsigned char TYPE_CLOCK_CONTINUE = 0xFB;
    static const unsigned char TYPE_CLOCK_STOP = 0xFC;
    static const unsigned char TYPE_CLOCK_CLOCK = 0xF8;

    /*
     * status will be used for MIDI clock events
     *
     * type, channel, value1 & value2 will be used for all voice messages
     */
    unsigned char status = data->at(0);

    MidiEvent* event = 0;

    if (status < 0xF0) {

        unsigned char type = 0;
        unsigned char channel = 0;
        unsigned char value1 = 0;
        unsigned char value2 = 0;

        // we get the 4 msb into type
        type = status & 0xF0;

        // we get the 4 lsb into channel, with numbering starting at 0
        channel = (status & 0xF) + 1;

        if (data->size() > 1)
            value1 = data->at(1);

        if (data->size() > 2)
            value2 = data->at(2);

        switch (type) {

            case TYPE_NOTE_ON:
                event = new MidiNoteOn(channel, value1, value2);
                break;

            case TYPE_PROGRAM_CHANGE:
                event = new MidiProgramChange(channel, value1);
                break;

            default:
                break;
        }

    } else {

        switch (status) {

            case TYPE_CLOCK_START:
                event = new MidiStart();
                break;

            case TYPE_CLOCK_CONTINUE:
                event = new MidiContinue();
                break;

            case TYPE_CLOCK_STOP:
                event = new MidiStop();
                break;

            case TYPE_CLOCK_CLOCK:
                event = new MidiClock();
                break;

            default:
                break;
        }
    }

    return event;

}

const MidiEvent* MidiEventFactory::createEvent(const QStringList& list) {


    /*
     * Implemented only for MdiNoteOn, MidiControlChange & MidiProgramChange
     */

    MidiEvent* event = 0;

    /*
     * If we have 4 values, we're dealing wit notes
     * If we have 3 values, we're dealing with program change
     */
    QString type = list.at(0);

    switch (list.size()) {

        case 4:

            if ( type == Constants::MIDI_TYPE_NOTE ) {

                event = new MidiNoteOn(

                        list.at(1).toUInt(),
                        list.at(2).toUInt(),
                        list.at(3).toUInt());

            }

            break;

        case 3:

            if ( type == Constants::MIDI_TYPE_PC ) {

                event = new MidiProgramChange(

                        list.at(1).toUInt(),
                        list.at(2).toUInt());
            }

            break;

        default:
            break;
    }

    return event;

}
