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
     * @return tectual representation
     */
    static std::string getNoteNameFromNotNumber( const unsigned char noteNumber );

    /**
     * Initialize names
     */
    static void initNames();
};

#endif /* MIDIHELPER_H_ */
