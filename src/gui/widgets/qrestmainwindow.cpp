/*  qrest
 *
 *  Copyright (C) 2008 - Frédéric CORNU
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
	ui.statusbar->setSizeGripEnabled(false);

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
}




QrestMainWindow::~QrestMainWindow() {


}




////////////////////////////////////////////////////////////////////////////////
//
// OBSERVER IMPLEMENTATION
//
////////////////////////////////////////////////////////////////////////////////
void QrestMainWindow::updateView(void) {

	/*
	 * we display delay frequencies as plain float number
	 * ( no scientific format ) with only a precision of 3
	 */
	static const int 	LFO_DISPLAY_PRECISION = 3;
	static const char	LFO_DISPLAY_FORMAT = 'f';

	/*
	 * pixmaps used for steadiness hint
	 */
	static QPixmap 		redHint(":/lights/pix/red_hint.png");
	static QPixmap 		greenHint(":/lights/pix/green_hint.png");


	// update tempo input field with validated value
	ui.tempoEdit->setText(QString::number(_document->getTempo()));

	// update delay display fields
	ui.quarterPeriodEdit->setText(
			QString::number(qRound(_document->getQuarterDelay()->getPeriod())));

	ui.quarterLfoEdit->setText(
			QString::number(_document->getQuarterDelay()->getFrenquency(),
			LFO_DISPLAY_FORMAT,
			LFO_DISPLAY_PRECISION));

	ui.wholePeriodEdit->setText(
			QString::number(qRound(_document->getWholeDelay()->getPeriod())));

	ui.wholeLfoEdit->setText(
			QString::number(_document->getWholeDelay()->getFrenquency(),
			LFO_DISPLAY_FORMAT,
			LFO_DISPLAY_PRECISION));

	ui.halfPeriodEdit->setText(
			QString::number(qRound(_document->getHalfDelay()->getPeriod())));

	ui.halfLfoEdit->setText(
			QString::number(_document->getHalfDelay()->getFrenquency(),
			LFO_DISPLAY_FORMAT,
			LFO_DISPLAY_PRECISION));

	ui.eighthPeriodEdit->setText(
			QString::number(qRound(_document->getEighthDelay()->getPeriod())));

	ui.eighthLfoEdit->setText(
			QString::number(_document->getEighthDelay()->getFrenquency(),
			LFO_DISPLAY_FORMAT,
			LFO_DISPLAY_PRECISION));

	ui.sixteenthPeriodEdit->setText(
			QString::number(qRound(_document->getSixTeenthDelay()->getPeriod())));

	ui.sixteenthLfoEdit->setText(
			QString::number(_document->getSixTeenthDelay()->getFrenquency(),
			LFO_DISPLAY_FORMAT,
			LFO_DISPLAY_PRECISION));

	ui.thirtySecondPeriodEdit->setText(
			QString::number(qRound(_document->getThirtySecondDelay()->getPeriod())));

	ui.thirtySecondLfoEdit->setText(
			QString::number(_document->getThirtySecondDelay()->getFrenquency(),
			LFO_DISPLAY_FORMAT,
			LFO_DISPLAY_PRECISION));

	// give a light and statusbar message according to steadiness
	if ( _document->isTempoFromTap() ) {

		if ( _document->isSteady() ) {

			statusPermMessage(tr("You're steady"));
			ui.steadyHint->setPixmap(greenHint);

		} else {

			statusPermMessage(tr("Keep tapping..."));
			ui.steadyHint->setPixmap(redHint);
		}

	} else {

		statusPermMessage("");
		ui.steadyHint->setPixmap(NULL);
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
