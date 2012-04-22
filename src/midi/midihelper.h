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

#ifndef MIDIHELPER_H_
#define MIDIHELPER_H_
#include <string>
#include <vector>
#include "../midi/events/midinoteon.h"
#include "../midi/events/midiprogramchange.h"
#include <QStringList>

/**
 * Helper class for MIDI operations
 */
class MidiHelper {

private:
    MidiHelper();
    virtual ~MidiHelper();

    /**
     * The names of all the notes in an octave
     */
    static std::vector<std::string> names;

    /**
     * There are 12 notes in an octave
     */
    static const unsigned int NOTES_IN_OCTAVE = 12;

public:
    /**
     * Return a textual representation of a MIDI note in German notation + octave number.
     *
     * Example noteNumber = 60 --> returns C4
     *
     * @param noteNumber MIDI note number
     *
     * @return textual representation
     */
    static std::string getNoteNameFromNoteNumber( const unsigned char noteNumber );

    /**
     * Initialize names
     */
    static void initNames();

    /**
     * return a string representation of a MidiNoteOn
     *
     * internal data separated by DELIM
     *
     * @param note : the MidiNoteOn
     *
     * @return a string representation of that note
     */
    static const QStringList noteToStringList(const MidiNoteOn* note);

    /**
     * return a string representation of a MidiProgramChange
     *
     * internal data separated by DELIM
     *
     * @param program : the MidiProgramChange
     *
     * @return a string representation of that MidiProgramChange
     */
    static const QStringList programToStringList(const MidiProgramChange* program);

    /**
     * Check if a MIDI event matches with a refence event
     *
     * We consider a match if both have the same :
     *
     * - type
     * - channel
     * - value1
     *
     * @param event     : the event to be tetsed
     * @param ref       : the reference event
     * @return          : true if match
     */
    static bool midiEventMatchesReference(const MidiEvent* event, const MidiEvent* ref);

};

#endif /* MIDIHELPER_H_ */
