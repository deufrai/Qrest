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

#include "qresthelpviewer.h"
#include "../../constants.h"
#include <QLocale>
#include <QDir>
#include <QDebug>

QrestHelpViewer* QrestHelpViewer::instance = NULL;

QrestHelpViewer::QrestHelpViewer(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);

	/*
	 *  we try to get online help translated according to user's locale.
	 *  if it doesn't exist, we fallback to english
	 */
    QString locale = QLocale::system().name().section('_', 0, 0);
	QString helpPath = getHelpPathFromLocale(locale);

	if ( ! QFile::exists(helpPath) ) {

		qWarning() << "QrestHelpViewer : Online help has not yet been translated for locale"
				 << locale
				 << "- defaulting to english";

		helpPath = getHelpPathFromLocale("en");
	}



	ui.helpBrowser->setSource(QUrl(helpPath));
}




QrestHelpViewer::~QrestHelpViewer()
{

}

QString QrestHelpViewer::getHelpPathFromLocale(const QString& locale) const {

	QString helpPath;

	helpPath.append(Constants::ONLINE_HELP_LOCATION)
	    .append(QDir::separator())
	    .append(locale)
	    .append(QDir::separator())
	    .append("index.html");

	return helpPath;

}

QrestHelpViewer* QrestHelpViewer::getInstance() {

	if ( NULL == instance ) {

		instance = new QrestHelpViewer();
	}

	return instance;
}

void QrestHelpViewer::destroy() {

	if ( instance ) {

		delete instance;
		instance = NULL;
	}
}
