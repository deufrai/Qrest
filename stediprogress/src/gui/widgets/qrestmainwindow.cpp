/*  qrest
 *
 *  Copyright (C) 2008-2009 - Frédéric CORNU
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

#include <QtDebug>
#include <QTimer>
#include <QMessageBox>
#include <QApplication>
#include <QWheelEvent>
#include "qrestmainwindow.h"
#include "../../process/tapTempoCalculator.h"
#include "qrestaboutdialog.h"
#include "../../constants.h"
#include "qresthelpviewer.h"
#include "../../settings/settings.h"
#include "qrestpreferencesdialog.h"


////////////////////////////////////////////////////////////////////////////////
//
// INIT
//
////////////////////////////////////////////////////////////////////////////////

QrestMainWindow::QrestMainWindow(QWidget *parent)
: QMainWindow(parent), _document(Document::getInstance()) {

	// register as an observer for app data
	_document->registerObserver(this);

	// setting up GUI
	ui.setupUi(this);

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
    if ( Settings::getInstance()->getSettings().value(
    		Settings::REMEMBER_WINDOW_POSITION,
    		Settings::REMEMBER_WINDOW_POSITION_DEFAULT).toBool() ) {

    	move(Settings::getInstance()->getSettings().value(Settings::WINDOW_POSITION,
    					QPoint(Settings::WINDOW_POSITON_DEFAULT_X,
    							Settings::WINDOW_POSITON_DEFAULT_Y)).toPoint());
    }
}





QrestMainWindow::~QrestMainWindow() {

	// store position into user's prefences.
	Settings::getInstance()->getSettings().setValue(
			Settings::WINDOW_POSITION,
			this->pos());

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


	// give a light and statusbar message according to steadiness
	if ( _document->isTempoFromTap() ) {

		qDebug() << "Steadiness:" << _document->getSteadiness();
		qDebug() << "ProgressBar maximum:" << ui.steadinessBar->maximum();

		ui.steadinessBar->setValue(qRound(_document->getSteadiness() * ui.steadinessBar->maximum()));
		qDebug() << "ProgressBar value:" << ui.steadinessBar->value();

		if ( _document->isSteady() ) {

			statusPermMessage(tr("You're steady"));

		} else {

			statusPermMessage(tr("Keep tapping..."));
		}

	} else {

		statusClear();
		ui.steadinessBar->setValue(ui.steadinessBar->maximum());
	}
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
	if ( text.toDouble() != _document->getTempo() ) {

		statusPermMessage(tr("Recalculation needed"));

	} else {

		statusClear();
	}

}





void QrestMainWindow::on_tapButton_pressed() {

	TapTempoCalculator::getInstance()->process();
}




void QrestMainWindow::on_plainRadio_clicked() {

	Document::getInstance()->setMultiplier(Document::MULTIPLIER_PLAIN);
}




void QrestMainWindow::on_dottedRadio_clicked() {

	Document::getInstance()->setMultiplier(Document::MULTIPLIER_DOTTED);
}




void QrestMainWindow::on_tripletRadio_clicked() {

	Document::getInstance()->setMultiplier(Document::MULTIPLIER_TRIPLET);
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

	QrestPreferencesDialog dlg(this);

	dlg.resize(dlg.minimumSizeHint());

	dlg.exec();
}



void QrestMainWindow::on_actionHelp_triggered() {

	QrestHelpViewer* pViewer = QrestHelpViewer::getInstance();

	pViewer->showNormal();

	// we wait for the window to be visible before activating and rasing it
	QTimer::singleShot(25,this, SLOT(raiseHelp()));


}




void QrestMainWindow::raiseHelp() {

	QrestHelpViewer* pViewer = QrestHelpViewer::getInstance();

	pViewer->activateWindow();
	pViewer->raise();


}



////////////////////////////////////////////////////////////////////////////////
//
// EVENT HANDLERS
//
////////////////////////////////////////////////////////////////////////////////
bool QrestMainWindow::eventFilter(QObject* target, QEvent* event) {

	// handling of mousewheel events onto temo input field
	if ( target == ui.tempoEdit && event->type() == QEvent::Wheel ) {

		QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);

		// most mice work in steps of 15 degrees
		int numDegrees = wheelEvent->delta() / 8;
		int numSteps = numDegrees / 15;

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
			QString::number(qRound(_document->getSixTeenthDelay()->getPeriod())));

	ui.thirtySecondPeriodEdit->setText(
			QString::number(qRound(_document->getThirtySecondDelay()->getPeriod())));

}





void QrestMainWindow::updateLfoDisplays(void) {

	/*
	 * we display delay frequencies as plain float number
	 * ( no scientific format ) with only a precision of 3
	 */
	static const int 	LFO_DISPLAY_PRECISION = 3;
	static const char	LFO_DISPLAY_FORMAT = 'f';

	ui.quarterLfoEdit->setText(
			QString::number(_document->getQuarterDelay()->getFrequency(),
					LFO_DISPLAY_FORMAT,
					LFO_DISPLAY_PRECISION));

	ui.wholeLfoEdit->setText(
			QString::number(_document->getWholeDelay()->getFrequency(),
					LFO_DISPLAY_FORMAT,
					LFO_DISPLAY_PRECISION));

	ui.halfLfoEdit->setText(
			QString::number(_document->getHalfDelay()->getFrequency(),
					LFO_DISPLAY_FORMAT,
					LFO_DISPLAY_PRECISION));

	ui.eighthLfoEdit->setText(
			QString::number(_document->getEighthDelay()->getFrequency(),
					LFO_DISPLAY_FORMAT,
					LFO_DISPLAY_PRECISION));

	ui.sixteenthLfoEdit->setText(
			QString::number(_document->getSixTeenthDelay()->getFrequency(),
					LFO_DISPLAY_FORMAT,
					LFO_DISPLAY_PRECISION));

	ui.thirtySecondLfoEdit->setText(
			QString::number(_document->getThirtySecondDelay()->getFrequency(),
					LFO_DISPLAY_FORMAT,
					LFO_DISPLAY_PRECISION));

}




void QrestMainWindow::processTempoInput(void) const {

	// tempo has been entered numerically
	_document->setTempoFromTap(false);

	// get tempo input field content and pass it to document
	_document->setTempo(ui.tempoEdit->text().toDouble());
}




void QrestMainWindow::statusPermMessage(const QString& message) const {

	ui.statusbar->showMessage(message);
}




void QrestMainWindow::statusTempMessage(const QString& message) const {

	// temp messages are shown for 1.5 seconds
	static const int STATUSBAR_TEMP_TIMEOUT = 1500;

	ui.statusbar->showMessage(message, STATUSBAR_TEMP_TIMEOUT);
}




void QrestMainWindow::statusClear(void) const {

	ui.statusbar->clearMessage();
}