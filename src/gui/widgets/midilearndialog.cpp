#include "midilearndialog.h"
#include "../../midi/midicontroller.h"
#include "../../midi/events/midinoteon.h"
#include "../../midi/events/midicontrolchange.h"
#include "../../midi/events/midiprogramchange.h"
#include "../../helpers/midihelper.h"
#include "../../model/document.h"

MidiLearnDialog::MidiLearnDialog(QWidget *parent)
: QDialog(parent),
  _candidate(0) {

	ui.setupUi(this);

	connect(MidiController::getInstance(),
	        SIGNAL(learnedEvent(const MidiEvent*)),
	        this,
	        SLOT(onEventLearned(const MidiEvent*)));

	// switch MIDI controller to learning mode
	MidiController::getInstance()->startLearning();
}

MidiLearnDialog::~MidiLearnDialog() {

}

void MidiLearnDialog::onEventLearned(const MidiEvent* event) {


    if ( event != 0 ) {

        /* in here we are sure to recieve an event that is of one of those types
         *
         *  - NoteOn
         *  - Control Change
         *  - Program Change
         *
         *  because in learn mode, the midicontroller will send a NULL if it received
         *  any other type of MIDI event
         *
         *  so we delete the old candidate & store this new event as a new candidate
         */
        delete _candidate;
        _candidate = event;

        // channel info is common to these 3 types
        ui.channelEdit->setText(
                QString::number( (int) ((dynamic_cast<const MidiSimpleEvent*> (_candidate))->getChannel()) ) );

        if ( const MidiNoteOn* note = dynamic_cast<const MidiNoteOn*> (_candidate) ) {

            /*
             * Note ON
             */
            ui.typeEdit->setText(tr("Note ON"));
            ui.valueLabel->setText(tr("Note : "));
            ui.valueEdit->setText(QString::fromStdString(MidiHelper::getNoteNameFromNoteNumber(
                    note->getValue1())));

        } else if ( const MidiControlChange* cc = dynamic_cast<const MidiControlChange*> (_candidate) ) {

            /*
             * Control change
             */
            ui.typeEdit->setText(tr("Conctrol Change"));
            ui.valueLabel->setText(tr("Control # : "));
            ui.valueEdit->setText(QString::number(cc->getValue1()));

        } else if ( const MidiProgramChange* pc = dynamic_cast<const MidiProgramChange*> (_candidate) ) {

            /*
             * Program change
             */
            ui.typeEdit->setText(tr("Program Change"));
            ui.valueLabel->setText(tr("Program # : "));
            ui.valueEdit->setText(QString::number(pc->getValue1()));
        }
    }
}

void MidiLearnDialog::accept() {

    MidiController::getInstance()->stopLearning();
    Document::getInstance()->setTriggerEvent(_candidate);
    QDialog::accept();
}

void MidiLearnDialog::reject() {

    MidiController::getInstance()->stopLearning();
    delete _candidate;
    QDialog::reject();

}
