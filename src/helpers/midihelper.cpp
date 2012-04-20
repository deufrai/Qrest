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

#include "midihelper.h"
#include <sstream>

std::vector<std::string> MidiHelper::names;

MidiHelper::MidiHelper() { }

MidiHelper::~MidiHelper() { }

void MidiHelper::initNames() {

    names.push_back("C");
    names.push_back("C#");
    names.push_back("D");
    names.push_back("D#");
    names.push_back("E");
    names.push_back("F");
    names.push_back("F#");
    names.push_back("G");
    names.push_back("G#");
    names.push_back("A");
    names.push_back("A#");
    names.push_back("B");
}


std::string MidiHelper::getNoteNameFromNotNumber( const unsigned char noteNumber ) {

    // initialize support vector on first call
    if ( names.size() != NOTES_IN_OCTAVE )
        initNames();

    if ( 127 < noteNumber )
        return "NaN";

    std::stringstream stream;

    stream << names.at( noteNumber % NOTES_IN_OCTAVE )
            << (int) (noteNumber / NOTES_IN_OCTAVE) -1; // octave numbering begin at -1

    return stream.str();
}
