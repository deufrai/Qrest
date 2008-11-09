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

#ifndef ZESTHELPVIEWER_H
#define ZESTHELPVIEWER_H

#include <QtGui/QMainWindow>
#include "ui_zesthelpviewer.h"

/**
 * Provides facility to browser HTML online help.
 *
 * Implemented as a singleton.
 */
class ZestHelpViewer : public QMainWindow
{
    Q_OBJECT


	//INIT
public:
    ~ZestHelpViewer();
private:
    ZestHelpViewer(QWidget *parent = 0);

    /** the unique instance */
    static ZestHelpViewer* instance;

public:
	/**
	 * Get the unique instance.
	 *
	 * \return the unique instance.
	 */
	static ZestHelpViewer* getInstance();

	/**
	 * Destroy help window
	 */
	static void destroy();

private:
	// MEMBERS
    Ui::ZestHelpViewerClass ui;

    // FUNCTIONS
    /**
     * return online html index file path according to system locale
     *
     * \param system's current locale
     *
     * \return path to index.html file in correct folder
     */
    QString getHelpPathFromLocale(const QString& locale) const;
};

#endif // ZESTHELPVIEWER_H
