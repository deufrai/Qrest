/*
 *  qrest
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

#ifndef LOCALEHELPER_H_
#define LOCALEHELPER_H_

#include <QString>
#include <QLocale>

/**
 * A set of static helper functions to deal with locales.
 */
class LocaleHelper {

private:
	LocaleHelper();
	virtual ~LocaleHelper();

	/**
	 * System locale description.
	 */
	static QString locale;

public:

    /**
     * Get path to help file according to system locale.
     *
     * \return the path
     */
    static QString getHelpFilePath(void);

    /**
     * Get path to default (en) help file.
     *
     * \return the path
     */
    static QString getDefaultHelpFilePath();

    /**
     * get system locale
     *
     * \return the system locale
     */
    static QString getLocale();
};

#endif /* LOCALEHELPER_H_ */
