/*
 *  qrest
 *
 *  Copyright (C) 2008-2013 - Frédéric CORNU
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

#ifndef CONSTANTS_H_
#define CONSTANTS_H_
#include <QString>

/**
 * Stores application-wide constants.
 */
class Constants {

private:
    Constants();
    virtual ~Constants();

public:

    /////////////////////////////////////////////////////////////////////
    //
    // Helper Functions
    //
    ////////////////////////////////////////////////////////////////////*
    static void initLocaleNames();

    /////////////////////////////////////////////////////////////////////
    //
    // Data
    //
    ////////////////////////////////////////////////////////////////////*


    /**
     * how many seconds in a minute ?
     */
    static const double SECONDS_PER_MINUTE = 60.0;

    /**
     * how many milliseconds in a second ?
     */
    static const double MILLISEC_PER_SECOND = 1000.0;

    /**
     * String describing version
     */
    static const char* VERSION_STRING;

    /**
     * targetted steadiness ration for taps to be considered steady
     */
    static const double STEADINESS_TARGET_RATIO = 0.90;

    /**
     * progressPie widget default value
     */
    static const double PROGRESSPIE_DEFAULT_VALUE = 0.0;

    /**
     * value for a full progresspie
     */
    static const double PROGRESSPIE_FULL = 1.0;

    /**
     * temp messages are shown for 2 seconds
     */
    static const int STATUSBAR_TEMP_TIMEOUT = 2000;

    /** Default tempo for app startup */
    static const double TEMPO_DEFAULT = 60.0;

    /** Minimum allowed tempo as input. */
    static const double TEMPO_MIN = 1.0;

    /** Maximum allowed tempo as input. */
    static const double TEMPO_MAX = 999.0;

    /** Size (in points) of widget fonts for mac */
    static const int MAC_FONT_SIZE = 13;

    /** How many MIDI CLock events in a quarter note ? */
    static const int MIDI_CLOCK_EVENTS_PER_QUARTER = 24;

    /**
     * How many milliseconds without recieving a midi clock event
     * before considering that synchro is lost ?
     *
     * 170 ms is roughly the time ellapsed between two MidiClock events at 15 BPM
     * which is sloooooooow enough
     **/
    static const int MIDI_SYNC_TIMEOUT_MS = 170;

    /**
     * default name of our MIDI engine
     */
    static const char* MIDI_ENGINE_NAME;

    /** flag used to represent a MidiNoteOn when serialized to QStringList */
    static const QString MIDI_TYPE_NOTE;

    /** flag used to represent a MidiProgramChange when serialized to QStringList */
    static const QString MIDI_TYPE_PC;
};

#endif /* CONSTANTS_H_ */
