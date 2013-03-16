/*  qrest
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

#ifndef QT_NO_DEBUG
#include <QDebug>
#endif

#include <QTimer>
#include <QMessageBox>
#include <QApplication>
#include <QWheelEvent>
#include <QFile>

#include "qrestmainwindow.h"
#include "../../process/tapTempoCalculator.h"
#include "qrestaboutdialog.h"
#include "../../constants.h"
#include "qresthelpviewer.h"
#include "../../settings/settings.h"
#include "../../model/document.h"
#include "../../model/delay.h"
#include "custom/progressPie.h"
#include "../../helpers/localeHelper.h"
#include "../../helpers/widgetsizehelper.h"
#include "../../midi/midicontroller.h"
#include "settingsdialog.h"
#include "midilearndialog.h"

////////////////////////////////////////////////////////////////////////////////
//
// INIT
//
////////////////////////////////////////////////////////////////////////////////

QrestMainWindow::QrestMainWindow(QWidget *parent)
: QMainWindow(parent),
  _document(Document::getInstance()) {

	// register as an observer for app data
	_document->registerObserver(this);

	// setting up GUI
	ui.setupUi(this);

#ifdef Q_WS_MAC
	// set default font sizes
	WidgetSizeHelper::setDefaultFontSize( this );
#endif

    // setup steadiness indicator
    _pie = new ProgressPie();
    ui.tempoInputHorizontalLayout->addWidget(_pie);

	// update view
	updateView();

	// usefull to populate delay times with document updated values
	processTempoInput();

	// give focus to tempo input field
	setFocusToTempoInput();

	// say hello
	statusTempMessage(tr("I'm ready, sir"));

	// register as an event filter for tempo input field
	ui.tempoEdit->installEventFilter(this);

	// move to last position stored in user's preferences if asked.
	if (Settings::getInstance()->getSettings().value(
			Settings::REMEMBER_WINDOW_POSITION,
			Settings::REMEMBER_WINDOW_POSITION_DEFAULT).toBool()) {

		move(
				Settings::getInstance()->getSettings().value(
						Settings::WINDOW_POSITION,
						QPoint(Settings::WINDOW_POSITON_DEFAULT_X,
								Settings::WINDOW_POSITON_DEFAULT_Y)).toPoint());
	}

#ifdef Q_WS_WIN
    /*
     * On windows, there are no virtual MIDI ports. So we must make sure
     * we have a physical device to connect to.
     *
     * We check saved settings and look if we have a prefered MIDI device.
     * If not, we display the settings dialog box
     */
    QString prefredMidiDevice = Settings::getInstance()->getSettings().value(

        Settings::MIDI_DEVICE,
        Settings::MIDI_DEVICE_DEFAULT).toString();

    if ( 0 == prefredMidiDevice.compare(Settings::MIDI_DEVICE_DEFAULT) ) {

        QMessageBox::information(0,
                                QObject::tr("Welcome to Qrest"),
                                QObject::tr("It appears this is your first use of qrest's MIDI features")
                                .append("\n\n")
                                .append(QObject::tr("You are invited to check qrest's MIDI settings and chose the MDI device you want to connect to")));

        on_actionPreferences_triggered();
    }
#endif

    // Open MIDI connection and start listening to incomming events
    if ( MidiController::getInstance()->resetEngine() ) {

        setMidiControlsEnable();

    } else {

        errorMidiDevice();
    }

	// connect MIDI controler signals to our slots
	connect(MidiController::getInstance(), SIGNAL(sigFreewheel()),  this, SLOT(onFreewheel()));
	connect(MidiController::getInstance(), SIGNAL(sigTrigger()),    this, SLOT(onTrigger()));
	connect(MidiController::getInstance(), SIGNAL(sigLearn()),      this, SLOT(onLearn()));
	connect(MidiController::getInstance(), SIGNAL(sigSync()),       this, SLOT(onSync()));
	connect(MidiController::getInstance(), SIGNAL(sigTimeout()),    this, SLOT(onTimeout()));
}

QrestMainWindow::~QrestMainWindow() {

    // store position into user's prefences.
    Settings::getInstance()->getSettings()
                    .setValue(Settings::WINDOW_POSITION,
                              this->pos());

	// save all prefs
	Settings::getInstance()->getSettings().sync();
}

////////////////////////////////////////////////////////////////////////////////
//
// OBSERVER IMPLEMENTATION
//
////////////////////////////////////////////////////////////////////////////////
void QrestMainWindow::updateView(void) {

	// update tempo input field with validated value
	ui.tempoEdit->setText(QString::number(_document->getTempo()));

	// update delay display fields
	updateDelayDisplays();

	// update LFO display fiels
	updateLfoDisplays();

	/*
	 * update steadiness widget and status bar.
	 *
	 * FIXME : Document must not contain info regarding rnutime *state*
	 * FIXME : Find a way to simplify all those tests
	 *
	 */
	// Steadiness widget is displayed full green with empty statusBar only when tempo source is keyboard
	if (_document->getTempoSource() == Document::TEMPO_SOURCE_KEYBOARD) {

		_pie->setValue(Constants::PROGRESSPIE_FULL);
		statusClear();

	} else {

		_pie->setValue(_document->getSteadiness());

		if (_document->getTempoSource() == Document::TEMPO_SOURCE_TAP) {

			if (_document->isSteady()) {

				statusPermMessage(tr("You're steady"));

			} else {

				statusPermMessage(tr("Keep tapping..."));
			}

		} else {

			// here, tempo source is MIDI Clock

			if (_document->isMidiClockRunning()) {

				if (_document->isSteady()) {

					statusPermMessage(tr("MIDI Clock Sync : Locked"));

				} else {

					statusPermMessage(tr("MIDI Clock Sync : Acquiring..."));
				}

			} else {

				statusClear();
			}
		}
	}

	/*
	 * update steadiness widget's tooltip text
	 */
	_pie->setToolTip(
			tr("Displayed BPM reliability : %n", 0,
					(int) (_document->getSteadiness() * 100)).append("%"));
}



void QrestMainWindow::onTimeout() {

    // and display a warning
    QString lMessage = QString("<p><b>")
	                    .append(tr("MIDI CLock synchronisation has been lost"))
	                    .append("</b></p><p>")
	                    .append(tr("External MIDI Clock source stopped emitting without sending the STOP command."))
	                    .append("</p><p>")
	                    .append(tr("MIDI Clock slave mode will be disabled."))
	                    .append("</p>");

    QMessageBox::warning(this,
            tr("MIDI Clock timeout"), lMessage);
}

////////////////////////////////////////////////////////////////////////////////
//
// SLOTS
//
////////////////////////////////////////////////////////////////////////////////
void QrestMainWindow::on_tempoEdit_returnPressed() {

	processTempoInput();

	// set focus to tempo input field
	setFocusToTempoInput();
}

void QrestMainWindow::on_tempoEdit_textEdited(const QString& text) {

	/*
	 * If displayed value is different to last valid value
	 * we tell user that resulting values must be recalculated
	 */
	if (text.toDouble() != _document->getTempo()) {

		statusPermMessage(tr("Recalculation needed"));

	} else {

		statusClear();
	}

}

void QrestMainWindow::on_tapButton_pressed() {

	_document->setTempoSource(_document->TEMPO_SOURCE_TAP);
	TapTempoCalculator::getInstance()->process();
}

void QrestMainWindow::on_plainRadio_clicked() {

	_document->setMultiplier(Document::MULTIPLIER_PLAIN);
}

void QrestMainWindow::on_dottedRadio_clicked() {

	_document->setMultiplier(Document::MULTIPLIER_DOTTED);
}

void QrestMainWindow::on_tripletRadio_clicked() {

	_document->setMultiplier(Document::MULTIPLIER_TRIPLET);
}

void QrestMainWindow::on_actionQuit_triggered() {

	this->close();
}

void QrestMainWindow::on_actionAbout_triggered() {

	QrestAboutDialog dlg(Constants::VERSION_STRING, this);

	dlg.adjustSize();

	dlg.exec();
}

void QrestMainWindow::on_actionPreferences_triggered() {

    /*
     * Show preferences dialog
     */
	SettingsDialog dlg(this);
	dlg.resize(dlg.minimumSizeHint());

	/*
	 * If dialog has been accpeted, we take new values into account
	 */
	if ( dlg.exec() == QDialog::Accepted ) {


	    // save 'remember me'
	    Settings::getInstance()->getSettings().setValue(

	            Settings::REMEMBER_WINDOW_POSITION,
	            dlg.getRememberWindowPosition());

	    /*
	     * if midi input port name has been changed, we reset the midi engine with that new name
	     */
	    QString midiInputPortOldName = Settings::getInstance()->getSettings().value(

	            Settings::MIDI_PORT_NAME,
	            Settings::MIDI_PORT_NAME_DEFAUT).toString();

	    if (QString::compare(dlg.getInputPortName(), midiInputPortOldName)) {

	        // save midi input port name
	        Settings::getInstance()->getSettings().setValue(
	                Settings::MIDI_PORT_NAME, dlg.getInputPortName());

	        // reset MIDI engine
	        if ( MidiController::getInstance()->resetEngine() ) {

	            setMidiControlsEnable();

	        } else {

	            errorMidiDevice();
	        }
	    }

#ifdef Q_WS_WIN

	    /*
	     * if connected device has changed, we reset the connection
	     */
        QString oldConnectedDevice = Settings::getInstance()->getSettings().value(

                Settings::MIDI_DEVICE,
                Settings::MIDI_DEVICE_DEFAULT).toString();

        QString newConnectedDevice = dlg.getDeviceName();

        if ( oldConnectedDevice.compare(newConnectedDevice) ) {

            // save connected device
            Settings::getInstance()->getSettings().setValue(
                        Settings::MIDI_DEVICE,
                        newConnectedDevice);

            // start listening to that device
            if ( MidiController::getInstance()->resetPort() ) {

                setMidiControlsEnable();

            } else {

                errorMidiDevice();
            }
        }
#endif
    }
}

void QrestMainWindow::on_actionHelp_triggered() {

	QrestHelpViewer* pViewer = QrestHelpViewer::getInstance();

	/*
	 *  we try to get online help translated according to user's locale.
	 *  if it doesn't exist, we fallback to english
	 */
	QString helpPath = LocaleHelper::getHelpFilePath();

	if (!QFile::exists(helpPath)) {

		qWarning("Online help has not yet been translated for current system locale.\n\
				Defaulting to english");

		helpPath = LocaleHelper::getDefaultHelpFilePath();
	}

	if (QFile::exists(helpPath)) {

		pViewer->setSource(helpPath);
		pViewer->showNormal();

		// we wait for the window to be visible before activating and rasing it
		QTimer::singleShot(25, this, SLOT(raiseHelp()));

	} else {

		qWarning("Default help file couln't be found...");

		QString warningMessage;

		warningMessage.append("<b>")
		        .append(tr("Online help file could not be found."))
		        .append("</b><br />")
		        .append(tr("Please consider reporting this as a bug on Qrest's website."))
		        .append("<br />")
		        .append("<center><a href=\"http://www.qrest.org\">http://www.qrest.org</a></center>");

		QMessageBox::warning(this, tr("Warning : No help file found"), warningMessage);
	}

}

void QrestMainWindow::raiseHelp() {

	QrestHelpViewer* pViewer = QrestHelpViewer::getInstance();

	pViewer->activateWindow();
	pViewer->raise();

}

/**
 * Slot that gets called when 'freewheel' radio button is clicked
 */
void QrestMainWindow::on_freewheelRadio_clicked() {

    MidiController::getInstance()->freeWheel();
}

/**
 * Slot that gets called when 'MIDI sync' radio button is clicked
 */
void QrestMainWindow::on_syncRadio_clicked() {

    MidiController::getInstance()->syncMode();
}

/**
 * Slot that gets called when 'MIDI TapTempo' radio button is clicked
 */
void QrestMainWindow::on_triggerRadio_clicked() {

    if ( checkIfTriggerModePossible() ) {

        MidiController::getInstance()->triggerMode();
    }
}

void QrestMainWindow::onFreewheel() {

    setTempoInputControlsEnable(true);
    ui.freewheelRadio->setChecked(true);
    statusClear();
}

void QrestMainWindow::onTrigger() {

    setTempoInputControlsEnable(true);
    ui.triggerRadio->setChecked(true);
}

void QrestMainWindow::onLearn() {

    setTempoInputControlsEnable(true);
    ui.freewheelRadio->setChecked(true);
}

void QrestMainWindow::onSync() {

    setTempoInputControlsEnable(false);
    ui.syncRadio->setChecked(true);
    statusPermMessage(tr("MIDI Clock Sync : Waiting..."));
}

////////////////////////////////////////////////////////////////////////////////
//
// EVENT HANDLERS
//
////////////////////////////////////////////////////////////////////////////////
bool QrestMainWindow::eventFilter(QObject* target, QEvent* event) {

	// handling of mousewheel events onto temo input field
	if (target == ui.tempoEdit && event->type() == QEvent::Wheel) {

		QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);

		/*
		 * most mice work in steps of 15 degrees
		 * and Qt's wheel rotation is express in 8th of a degree
		 */
		static const int WHEEL_PRECISION = 8;
		static const int STEP_SIZE = 15;

		int numDegrees = wheelEvent->delta() / WHEEL_PRECISION;
		int numSteps = numDegrees / STEP_SIZE;

		double tempo = ui.tempoEdit->text().toDouble();

		ui.tempoEdit->setText(QString::number(tempo + numSteps));

		// do the math !!
		processTempoInput();
		setFocusToTempoInput();

		return true;

	} else {

		return QMainWindow::eventFilter(target, event);
	}
}

void QrestMainWindow::closeEvent(QCloseEvent* event) {

	QrestHelpViewer::destroy();
	event->accept();
}

////////////////////////////////////////////////////////////////////////////////
//
// PRIVATE FUNCTIONS
//
////////////////////////////////////////////////////////////////////////////////
void QrestMainWindow::setTempoInputControlsEnable(bool enabled = true) {

    ui.tempoEdit->setEnabled(enabled);
    ui.tapButton->setEnabled(enabled);
}

bool QrestMainWindow::checkIfTriggerModePossible() {

    if ( ! _document->getTriggerEvent() ) {

        QString message = QString("<p>")
                .append(tr("A MIDI trigger event for TAPTEMPO has not yet been set"))
                .append("</p>")
                .append(tr("You will be redirected to the trigger configuration window"));

        QMessageBox::warning(this,

                tr("No configured MIDI trigger"),
                message
        );

        MidiLearnDialog dlg(this);
        dlg.exec();
    }

    return _document->getTriggerEvent() != 0;
}

void QrestMainWindow::setFocusToTempoInput(void) const {

	ui.tempoEdit->setFocus();
	ui.tempoEdit->selectAll();
}

void QrestMainWindow::updateDelayDisplays(void) {

	ui.quarterPeriodEdit->setText(
			QString::number(qRound(_document->getQuarterDelay()->getPeriod())));

	ui.wholePeriodEdit->setText(
			QString::number(qRound(_document->getWholeDelay()->getPeriod())));

	ui.halfPeriodEdit->setText(
			QString::number(qRound(_document->getHalfDelay()->getPeriod())));

	ui.eighthPeriodEdit->setText(
			QString::number(qRound(_document->getEighthDelay()->getPeriod())));

	ui.sixteenthPeriodEdit->setText(
			QString::number(
					qRound(_document->getSixTeenthDelay()->getPeriod())));

	ui.thirtySecondPeriodEdit->setText(
			QString::number(
					qRound(_document->getThirtySecondDelay()->getPeriod())));
}

void QrestMainWindow::updateLfoDisplays(void) {

	/*
	 * we display delay frequencies as plain float number
	 * ( no scientific format ) with only a precision of 3
	 */
	static const int LFO_DISPLAY_PRECISION = 3;
	static const char LFO_DISPLAY_FORMAT = 'f';

	ui.quarterLfoEdit->setText(
			QString::number(_document->getQuarterDelay()->getFrequency(),
					LFO_DISPLAY_FORMAT, LFO_DISPLAY_PRECISION));

	ui.wholeLfoEdit->setText(
			QString::number(_document->getWholeDelay()->getFrequency(),
					LFO_DISPLAY_FORMAT, LFO_DISPLAY_PRECISION));

	ui.halfLfoEdit->setText(
			QString::number(_document->getHalfDelay()->getFrequency(),
					LFO_DISPLAY_FORMAT, LFO_DISPLAY_PRECISION));

	ui.eighthLfoEdit->setText(
			QString::number(_document->getEighthDelay()->getFrequency(),
					LFO_DISPLAY_FORMAT, LFO_DISPLAY_PRECISION));

	ui.sixteenthLfoEdit->setText(
			QString::number(_document->getSixTeenthDelay()->getFrequency(),
					LFO_DISPLAY_FORMAT, LFO_DISPLAY_PRECISION));

	ui.thirtySecondLfoEdit->setText(
			QString::number(_document->getThirtySecondDelay()->getFrequency(),
					LFO_DISPLAY_FORMAT, LFO_DISPLAY_PRECISION));
}

void QrestMainWindow::processTempoInput(void) const {

	// tempo has been entered numerically
	_document->setTempoSource(Document::TEMPO_SOURCE_KEYBOARD);

	// get tempo input field content and pass it to document
	_document->setTempo(ui.tempoEdit->text().toDouble());
}

void QrestMainWindow::statusPermMessage(const QString& message) const {

	ui.statusbar->showMessage(message);
}

void QrestMainWindow::statusTempMessage(const QString& message) const {

	ui.statusbar->showMessage(message, Constants::STATUSBAR_TEMP_TIMEOUT);
}

void QrestMainWindow::statusClear(void) const {

	ui.statusbar->clearMessage();
}

void QrestMainWindow::errorMidiDevice() {

    QString prefreredMidiDevice = Settings::getInstance()->getSettings().value(

            Settings::MIDI_DEVICE,
            Settings::MIDI_DEVICE_DEFAULT).toString();

    QMessageBox::critical(this,
            tr("MIDI Connection failure"),
            tr("MIDI connection could not be made to device : ").append(prefreredMidiDevice));

    setMidiControlsEnable(false);

}

void QrestMainWindow::setMidiControlsEnable(bool enable) {

    ui.syncRadio->setEnabled(enable);
    ui.triggerRadio->setEnabled(enable);
}
