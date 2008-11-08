/*
 *  zest
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

#ifndef ZESTMAINWINDOW_H
#define ZESTMAINWINDOW_H

#include <QtGui/QMainWindow>
#include "../forms/ui_zestmainwindow.h"
#include "../../dp/observer.h"
#include "../../model/document.h"


/**
 * Zest Easy Studio Toolkit main window
 */
class ZestMainWindow : public QMainWindow, Observer
{
    Q_OBJECT

public:

	// INIT

    ZestMainWindow(QWidget *parent = 0);
    ~ZestMainWindow();

    // INTERFACE

    /**
     * update view to reflect App data changes
     */
    virtual void updateView();

private slots:

	// SLOTS

	/**
	 * Slot that gets called when 'return' is presses with tempo edit field
	 * focused.
	 */
    void on_tempoEdit_returnPressed();

    /**
     * Slot that gets called when 'tap' button is pressed
     */
    void on_tapButton_pressed();

    /**
     * Slot that gets called when 'plain' radio button is clicked
     */
    void on_plainRadio_clicked();

    /**
     * Slot that gets called when 'dotted' radio button is clicked
     */
    void on_dottedRadio_clicked();

    /**
     * Slot that gets called when 'triplet' radio button is clicked
     */
    void on_tripletRadio_clicked();

	/**
	 * Slot that gets called upon "Quit" action triggering
	 */
	void on_actionQuit_triggered();

	/**
	 * Slot that gets called upon "About" action triggering
	 */
	void on_actionAbout_triggered();

	/**
	 * Slot that gets called upon "Help" action triggering
	 */
	void on_actionHelp_triggered();

private:
	// EVENT HANDLERS

	/**
	 * Custom event handler used for tempo edit field and mousewheel events
	 *
	 * \param target the object tagetted by the event
	 * \param event the event to be handled
	 *
	 * \return true if event should not be handled by other handlers.
	 */
	virtual bool eventFilter(QObject *target, QEvent *event);

	// FUNCTIONS

	/**
	 * Give the focus to tempo input field.
	 */
    void setFocusToTempoInput(void) const;

    /**
     * pass tempo input field content value to app data
     */
    void processTempoInput(void) const;

    /**
     * Display a permanent message in status bar
     *
     * \param message the message to display
     */
    void statusPermMessage(const QString& message) const;

    /**
     * Display a temporary message in status bar
     *
     * \param message the message to display
     */
    void statusTempMessage(const QString& message) const;

	// MEMBERS

	/** The GUI subclass */
    Ui::ZestMainWindowClass ui;

    /** Application data store */
    Document* _document;

};

#endif // ZESTMAINWINDOW_H
