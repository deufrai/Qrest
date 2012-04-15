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

#ifndef MIDIENGINE_H_
#define MIDIENGINE_H_

#include <QThread>

/**
 * Main interface for MIDI operations implemented as a Singleton
 *
 * Will hide platform sepcific implementation.
 *
 * Will run in a thread that will keep listening for these MIDI evnents :
 *
 *   - MIDI clock
 *   - Transport stop
 *   - Transport resume
 *
 * and post these infos to the MidiBroadcaster in charge of emitting Qt signals
 */
class MidiEngine: public QThread {

protected:
    ////////////////////////////////////////////////////////////////////////////
    //
    // INIT
    //
    ////////////////////////////////////////////////////////////////////////////
	MidiEngine();
	virtual ~MidiEngine();


    ////////////////////////////////////////////////////////////////////////////
    //
    // SINGLETON
    //
    ////////////////////////////////////////////////////////////////////////////
private:
	static MidiEngine* _instance;

public:
	/**
	 * Instanciate the Singleton
	 *
	 * \return the unique instance
	 */
	static MidiEngine* getInstance();


    ////////////////////////////////////////////////////////////////////////////
    //
    // INTERFACE
    //
    ////////////////////////////////////////////////////////////////////////////
	/**
	 * Initialize the platform specific MIDI implementation
	 */
	virtual void init() = 0;

	/**
	 * Read next MIDI event
	 */
	virtual void readEvent() = 0;

private:
    ////////////////////////////////////////////////////////////////////////////
    //
    // PRIVATE FUNCTIONS
    //
    ////////////////////////////////////////////////////////////////////////////
	/**
	 * QThread implementation
	 */
	void run();


    ////////////////////////////////////////////////////////////////////////////
    //
    // PRIVATE FUNCTIONS
    //
    ////////////////////////////////////////////////////////////////////////////
protected:
	/** count how many MIDI clock events have been recieved */
	int nTickCounter;
};

#endif /* MIDIENGINE_H_ */
