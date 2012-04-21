/*
 *  qrest
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

#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include "../dp/observable.h"
#include "delay.h"
#include <vector>

/**
 * Stores all application data.
 *
 * Singelton class that stores all application data.
 * Implements the Observable interface
 */
class Document: public Observable {

private:

    ////////////////////////////////////////////////////////////////////////////
    //
    // INIT
    //
    ////////////////////////////////////////////////////////////////////////////
    Document();
    virtual ~Document();

public:

    ////////////////////////////////////////////////////////////////////////////
    //
    // SINGLETON
    //
    ////////////////////////////////////////////////////////////////////////////
    /**
     * get the singleton instance.
     *
     * \return the instance
     */
    static Document* getInstance();

    /**
     * Destroy the singleton instance.
     */
    static void destroy();

private:

    /** The single instance */
    static Document* _instance;

    ////////////////////////////////////////////////////////////////////////////
    //
    // ACCESS
    //
    ////////////////////////////////////////////////////////////////////////////
public:
    /**
     * Set the tempo.
     *
     * \param tempo the tempo to be set
     */
    void setTempo(const double tempo);


    /**
     * Get the tempo.
     *
     * \return the tempo
     */
    inline double getTempo(void) const { return _tempo; }


    /**
     * Get multiplier
     *
     * \return the multiplier
     */
    inline double getMultiplier(void) const { return _multiplier; }

    /**
     * Set the multiplier
     *
     * \param multi the multiplier
     */
    inline void setMultiplier(const double multi) {

        _multiplier = multi;
        updateDelays();
        notifyObservers();
    }

    /**
     * Get steadiness flag
     *
     * \return steadiness flag
     */
    inline bool isSteady(void) const { return _steady; }

    /**
     * Set steadiness flag
     *
     * \param steady steadiness flag value
     */
    inline void setSteady(const bool steady) { _steady = steady; }

    /**
     * Get the delay object for a whole note
     *
     * \return the 'whole' delay
     */
    inline Delay* getWholeDelay() const { return _delays[WHOLE]; }

    /**
     * Get the delay object for a half note
     *
     * \return the 'half' delay
     */
    inline Delay* getHalfDelay() const { return _delays[HALF]; }

    /**
     * Get the delay object for a quarter note
     *
     * \return the 'quarter' delay
     */
    inline Delay* getQuarterDelay() const { return _delays[QUARTER]; }

    /**
     * Get the delay object for a eighth note
     *
     * \return the 'eighth' delay
     */
    inline Delay* getEighthDelay() const { return _delays[EIGHTH]; }

    /**
     * Get the delay object for a sixteenth note
     *
     * \return the 'sixteenth' delay
     */
    inline Delay* getSixTeenthDelay() const { return _delays[SIXTEENTH]; }

    /**
     * Get the delay object for a thirtysecond note
     *
     * \return the 'thirtysecond' delay
     */
    inline Delay* getThirtySecondDelay() const { return _delays[THIRTYSECOND]; }

    /**
     * Get steadiness value.
     *
     * \return the steadiness value
     */
    inline double getSteadiness() const { return _steadiness; }

    /**
     * Set steadiness value.
     *
     * \param steadiness the steadiness value.
     */
    inline void setSteadiness(const double steadiness) { _steadiness = steadiness; }

    /**
     * Get MIDI operations availability
     *
     * \return true if MIDI operations are available
     */
    inline bool isMidiClockRunning () const { return _midiClockRunning; }

    /**
     * The the value of the _midiClockRunning flag
     *
     * @param midiClockRunning are we slaved to MIDI Clock ?
     */
    inline void setMidiClockRunning( const bool midiClockRunning ) {

    	_midiClockRunning = midiClockRunning;
    	notifyObservers();
    }

    /**
     * Set tempo source
     *
     * \param source from tempoSource enum
     **/
    inline void setTempoSource (const int source) { _tempoSource = source; }

    /**
     * Get tempo source
     *
     * \ the tempo source, values are from tempoSource enum
     */
    inline int getTempoSource () const { return _tempoSource; }

    /**
     * Set the value of our midiclock timeout;
     *
     * @param timeout has MIDI Clock source timed out ?
     */
    inline void setMidiClockTimeout ( bool timeout) {

        _midiClockTimeout = timeout;

        /*
         * If a MIDI Clock timeout has occured, we notify our observers
         */
        if ( _midiClockTimeout )
            notifyObservers();
    }

    /**
     * Has our MIDI Clock source timed out ?
     *
     * @return well, yes or no
     */
    inline bool isMidiClockTimeout() const { return _midiClockTimeout; }


    ////////////////////////////////////////////////////////////////////////////
	//
	// TEMPO source enum
	//
	////////////////////////////////////////////////////////////////////////////

    enum tempoSource {

    	TEMPO_SOURCE_KEYBOARD,
    	TEMPO_SOURCE_TAP,
    	TEMPO_SOURCE_MIDI_CLOCK
    };

private:

    ////////////////////////////////////////////////////////////////////////////
    //
    // CONSTANTS
    //
    ////////////////////////////////////////////////////////////////////////////

    // Constants used for index and size of Delay vector

    static const int WHOLE = 0;
    static const int HALF = 1;
    static const int QUARTER = 2;
    static const int EIGHTH = 3;
    static const int SIXTEENTH = 4;
    static const int THIRTYSECOND = 5;
    static const int DELAYS_COUNT = 6;

    /** complete steadiness is expressed as 1 as a double */
    static const double FULL_STEADINESS = 1.0;

    // Constants used for the multiplier
public:
    /** Mutlilpier for plain notes */
    static const double MULTIPLIER_PLAIN = 1.0;

    /** Multiplier for dotted notes */
    static const double MULTIPLIER_DOTTED = 1.5;

    /** Mutliplier for triplet notes */
    static const double MULTIPLIER_TRIPLET = 2.0 / 3.0;

private:
    ////////////////////////////////////////////////////////////////////////////
    //
    // MEMBERS
    //
    ////////////////////////////////////////////////////////////////////////////
    /** The tempo */
    double _tempo;

    /** vector of Delay objects */
    vector<Delay*> _delays;

    /** has tempo been tapped steadily ? */
    bool _steady;

    /** stediness value : between 0 and 1, represents how steady taps are */
    double _steadiness;

    /** tempo source */
    int _tempoSource;

    /** The multiplier used for plain, dotted and triplet notes */
    double _multiplier;

    /** Indicates running state of MIDI clock */
    bool _midiClockRunning;

    /** Has MIDI Clock source times out */
    bool _midiClockTimeout;


    ////////////////////////////////////////////////////////////////////////////
    //
    // PRIVATE FUNCTIONS
    //
    ////////////////////////////////////////////////////////////////////////////
    /**
     * Init vector of Delays
     */
    void initDelays(void);

    /**
     * destroy vector of delays
     */
    void destroyDelays(void);

    /**
     * Ask for the delay calculation
     */
    void updateDelays(void);
};
#endif /*DOCUMENT_H_*/
