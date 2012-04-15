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

#ifndef MIDIMROADCASTER_H_
#define MIDIMROADCASTER_H_

#include <QObject>

/**
 * The only purpose of this class is to recieve calls from the various
 * platform specific MIDI listeners and translate thoses into Qt signals.
 *
 * The point in this class is de-coupling the MidiEngine thread from the GUI thread
 *
 * Since the events fired from the MidiEngine thread will affect what is displayed
 * on the GUI, we must use Qt signals to avoid GUI modifications from outside
 * the main application"s event loop.
 *
 * So this class's Qt signals are connected to slots of this same class.
 **/
class MidiBroadcaster : public QObject {

Q_OBJECT

	////////////////////////////////////////////////////////////////////////////
	//
	// INIT
	//
	////////////////////////////////////////////////////////////////////////////
private:
	MidiBroadcaster();
	virtual ~MidiBroadcaster();

	////////////////////////////////////////////////////////////////////////////
	//
	// INTERFACE
	//
	////////////////////////////////////////////////////////////////////////////
public:
	/** The single instance */
	static MidiBroadcaster* _instance;

	/** Instanciate and/or return the single instance */
	static MidiBroadcaster* getInstance();

	/**
	 * Simply emits a Qt signal (bip()) when MIDI engine detects a quarter note has
	 * ellapsed while recieving MIDI Clock.
	 */
	void onMidiQuarter();

	////////////////////////////////////////////////////////////////////////////
	//
	// SIGNALS
	//
	////////////////////////////////////////////////////////////////////////////
signals:
	void bip();

	////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC SLOTS
	//
	////////////////////////////////////////////////////////////////////////////
public slots:
	/**
	 * Ask the TapTempoCalculator to take the current time into account
	 */
	void onBip();
};

#endif /* MIDIMROADCASTER_H_ */
