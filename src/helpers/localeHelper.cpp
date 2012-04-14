/*
 *  qrest
 *
 *  Copyright (C) 2008-2012 - Frédéric CORNU
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

QString LocaleHelper::getLocale() {

    return locale;
}


QString LocaleHelper::getHelpFilePath() {

    return QString(":/html/")
            .append(locale)
            .append("/index.html");
}


QString LocaleHelper::getDefaultHelpFilePath() {

    return ":/html/en/index.html";
}
