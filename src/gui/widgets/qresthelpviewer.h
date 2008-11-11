/*
 *  qrest
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

#ifndef QRESTHELPVIEWER_H
#define QRESTHELPVIEWER_H

#include <QtGui/QMainWindow>
#include "ui_qresthelpviewer.h"

/**
 * Provides facility to browser HTML online help.
 *
 * Implemented as a singleton.
 */
class QrestHelpViewer : public QMainWindow
{
    Q_OBJECT


	//INIT
public:
    ~QrestHelpViewer();
private:
	QrestHelpViewer(QWidget *parent = 0);

    /** the unique instance */
    static QrestHelpViewer* instance;

public:
	/**
	 * Get the unique instance.
	 *
	 * \return the unique instance.
	 */
	static QrestHelpViewer* getInstance();

	/**
	 * Destroy help window
	 */
	static void destroy();

private:
	// MEMBERS
    Ui::QrestHelpViewerClass ui;

    // FUNCTIONS
    /**
     * return online html index file path according to system locale
     *
     * \param locale system's current locale
     *
     * \return path to index.html file in correct folder
     */
    QString getHelpPathFromLocale(const QString& locale) const;
};

#endif // QRESTHELPVIEWER_H
