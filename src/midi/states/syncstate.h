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

#ifndef SYNCSTATE_H_
#define SYNCSTATE_H_

#include <QTimer>
#include <QObject>

#include "midistate.h"

/**
 * The state in which we are syncing to MIDI Clock
 *
 * We will react to these specific events :
 *
 * - MidiClock
 * - MidiStart
 * - MidiContinue
 * - MidiStart
 *
 * And once we saw the first MidiClock event, we want to detect if we stop recieving more MidiClock
 * events without having recieved an MidiStop first.
 * That would tell us that MIDI Clock input has been lost accidentally
 */
class SyncState: public QObject, public MidiState {

Q_OBJECT

public:
    SyncState();
    virtual ~SyncState();

    virtual void processEvent(const MidiEvent* event);

    virtual void reset();

    /**
     * we tell the document that a timeout has occurred
     */
private slots:
    void onMidiClockTimeoutDetectorTimeout();

private:
    /** rolling counter of recieved MidiClock events */
    unsigned char _midiClockCounter;

    /** Timer used for MDI Clock timeout detection */
    QTimer* _midiClockTimeoutDetector;
};

#endif /* SYNCSTATE_H_ */
