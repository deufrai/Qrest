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

#include "midilearndialog.h"
#include "../../midi/midicontroller.h"
#include "../../midi/events/midinoteon.h"
#include "../../midi/events/midiprogramchange.h"
#include "../../midi/midihelper.h"
#include "../../model/document.h"

MidiLearnDialog::MidiLearnDialog( QWidget *parent )
        : QDialog( parent ),
                _candidate( 0 ) {

    ui.setupUi( this );

    displayEvent( Document::getInstance()->getTriggerEvent() );

    connect( MidiController::getInstance(),
            SIGNAL(sigLearnedEvent(const MidiEvent*)),
            this,
            SLOT(onEventLearned(const MidiEvent*)) );

    // switch MIDI controller to learning mode
    MidiController::getInstance()->learnMode();

    // disable OK button
    ui.okButton->setEnabled( false );
}

MidiLearnDialog::~MidiLearnDialog() {

}

void MidiLearnDialog::onEventLearned( const MidiEvent* event ) {

    if( event ) {

        /* in here we are sure to recieve an event that is of one of those types
         *
         *  - NoteOn
         *  - Program Change
         *
         *  because in learn mode, the midicontroller will send a NULL if it received
         *  any other type of MIDI event
         *
         *  so we delete the old candidate & store this new event as a new candidate
         */
        delete _candidate;
        _candidate = event;

        displayEvent( _candidate );
        ui.okButton->setEnabled( true );

    }
}

void MidiLearnDialog::displayEvent( const MidiEvent* event ) {

    if( event ) {

        // channel info is common to these 3 types
        ui.channelEdit->setText(
                QString::number( (int) ( ( dynamic_cast<const MidiSimpleEvent*>( event ) )->getChannel() ) ) );

        if( const MidiNoteOn* note = dynamic_cast<const MidiNoteOn*>( event ) ) {

            /*
             * Note ON
             */
            ui.typeEdit->setText( tr( "Note ON" ) );
            ui.valueLabel->setText( tr( "Note : " ) );
            ui.valueEdit->setText( QString::fromStdString( MidiHelper::getNoteNameFromNoteNumber(
                    note->getValue1() ) ) );

        } else if( const MidiProgramChange* pc = dynamic_cast<const MidiProgramChange*>( event ) ) {

            /*
             * Program change
             */
            ui.typeEdit->setText( tr( "Program Change" ) );
            ui.valueLabel->setText( tr( "Program : " ) );
            ui.valueEdit->setText( QString::number( pc->getValue1() ) );
        }
    }
}

void MidiLearnDialog::accept() {

    MidiController::getInstance()->freeWheel();

    Document* pDocument = Document::getInstance();

    /*
     * We don't overwrite the document's trigger event if we haven't changed it in this dialog
     *
     */
    if( pDocument->getTriggerEvent() != _candidate ) {

        delete pDocument->getTriggerEvent();
        pDocument->setTriggerEvent( _candidate );
    }

    QDialog::accept();
}

void MidiLearnDialog::reject() {

    MidiController::getInstance()->freeWheel();
    delete _candidate;
    QDialog::reject();

}
