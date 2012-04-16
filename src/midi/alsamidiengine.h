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

#ifndef ALSAMIDIENGINE_H_
#define ALSAMIDIENGINE_H_

#include "midiengine.h"
#include <alsa/asoundlib.h>

/**
 * ALSA (Advanced Linux Sound Architecture) implementation of the MIDI engine
 */
class AlsaMidiEngine: public MidiEngine {

    ////////////////////////////////////////////////////////////////////////////
    //
    // INIT
    //
    ////////////////////////////////////////////////////////////////////////////
public:
	AlsaMidiEngine();
	virtual ~AlsaMidiEngine();


    ////////////////////////////////////////////////////////////////////////////
    //
    // INTERFACE
    //
    ////////////////////////////////////////////////////////////////////////////
	/**
	 * Initialize the platform specific MIDI implementation
	 */
	void init();

	/**
	 * Read next MIDI event
	 */
	int readEvent();


	/////////////////////////////////////////////////////////////////////////////
	//
	// MEMBERS
	//
	/////////////////////////////////////////////////////////////////////////////
private:
	/** handle to the ALSA MIDI sequencer */
	snd_seq_t* 	_seqHandle;

	/** number of the MIDI port, opened on the ALSA sequencer */
	int			_port;

};

#endif /* ALSAMIDIENGINE_H_ */
