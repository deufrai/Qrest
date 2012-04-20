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
#include "midicontrolchange.h"
#include "midiprogramchange.h"
#include "midistart.h"
#include "midicontinue.h"
#include "midistop.h"
#include "midiclock.h"
#include "../../helpers/midihelper.h"

MidiEventFactory::MidiEventFactory() {
}

MidiEventFactory::~MidiEventFactory() {
}

MidiEvent* MidiEventFactory::createEvent(
        const std::vector<unsigned char> data) {

    /*
     * Note, control changes and program change share this structure for byte #0
     *
     * the type of event is code on the 4 msb
     * the channel is coded on the 4 lsb
     *
     * The fact that they use channel information makes them part of what is called
     * the voice messages Category
     */
    static const unsigned char TYPE_NOTE_ON = 0x90;
    static const unsigned char TYPE_CONTROL_CHANGE = 0xB0;
    static const unsigned char TYPE_PROGRAM_CHANGE = 0xC0;

    /*
     * all events whose byte #0 value is greater that 0xEF dont have channel information
     * their type is code in the whole byte #0
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
    unsigned char status = data.at(0);

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

        if (data.size() > 1)
            value1 = data.at(1);

        if (data.size() > 2)
            value2 = data.at(2);

        switch (type) {

            case TYPE_NOTE_ON:
                event = new MidiNoteOn(channel, value1, value2);
                break;

            case TYPE_CONTROL_CHANGE:
                event = new MidiControlChange(channel, value1, value2);
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

    if ( MidiNoteOn* note = dynamic_cast<MidiNoteOn*> (event) ) {

        std::cout << "Note : channel " << (int)note->getChannel()
                << ", Number : " << (int)note->getValue1()
                << ", Name : " << MidiHelper::getNoteNameFromNotNumber(note->getValue1())
                << ", Velocity : " << (int)note->getValue2() << std::endl;

    } else if ( MidiControlChange* cc = dynamic_cast<MidiControlChange*> (event) ) {

        std::cout << "Control Change : channel " << (int)cc->getChannel()
                << ", Number : " << (int)cc->getValue1()
                << ", Value : " << (int)cc->getValue2() << std::endl;

    } else if ( MidiProgramChange* pc = dynamic_cast<MidiProgramChange*> (event) ) {

        std::cout << "Program change : channel " << (int)pc->getChannel()
                << ", Number : " << (int)pc->getValue1() << std::endl;

    } else if ( dynamic_cast<MidiClock*> (event) ) {

        std::cout << "MIDI Clock" << std::endl;

    } else if ( dynamic_cast<MidiStart*> (event) ) {

        std::cout << "MIDI Start" << std::endl;

    } else if ( dynamic_cast<MidiContinue*> (event) ) {

        std::cout << "MIDI Continue" << std::endl;

    } else if ( dynamic_cast<MidiStop*> (event) ) {

        std::cout << "MIDI Stop" << std::endl;

    }

    return event;

}

