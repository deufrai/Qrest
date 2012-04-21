#ifndef MIDILEARNDIALOG_H
#define MIDILEARNDIALOG_H

#include <QtGui/QDialog>
#include "ui_midilearndialog.h"
#include "../../midi/events/midievent.h"

/**
 * dialog displayed to capture a MIDI event and store
 * is as a trigger for the TAP feature.
 */
class MidiLearnDialog : public QDialog
{
    Q_OBJECT

public:
    MidiLearnDialog(QWidget *parent = 0);
    ~MidiLearnDialog();

public slots:

    /**
     * We recieved a MIDI event
     *
     * @param event : the event
     */
    void onEventLearned(const MidiEvent* event);

    /**
     * Captured event has been accepted as a trigger
     */
    virtual void accept();

    /**
     * dialog is rejected
     */
    virtual void reject();

private:

    /** our candidate MIDI event */
    const MidiEvent* _candidate;

    /** the UI form */
    Ui::MidiLearnDialogClass ui;
};

#endif // MIDILEARNDIALOG_H
