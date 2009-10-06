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

#include "localeHelper.h"
#include "../constants.h"
#include <QLocale>
#include <QDir>

QString LocaleHelper::locale = QLocale::system().name().section('_', 0, 0);

LocaleHelper::LocaleHelper() {}

LocaleHelper::~LocaleHelper() {}

QString LocaleHelper::getTranslationFilePath() {

    QString translationFilePath;

    translationFilePath.append(Constants::I18N_FOLDER_LOCATION)
    .append(QDir::separator())
    .append("qrest_")
    .append(locale);

	return translationFilePath;
}

QString LocaleHelper::getHelpFilePath() {

    QString helpPath;

    helpPath.append(Constants::ONLINE_HELP_LOCATION)
    .append(QDir::separator())
    .append(locale)
    .append(QDir::separator())
    .append("index.html");

    return helpPath;
}


QString LocaleHelper::getDefaultHelpFilePath() {

    QString helpPath;

    helpPath.append(Constants::ONLINE_HELP_LOCATION)
    .append(QDir::separator())
    .append("en")
    .append(QDir::separator())
    .append("index.html");

    return helpPath;
}
