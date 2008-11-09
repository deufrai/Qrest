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

#include "zesthelpviewer.h"
#include "../../constants.h"
#include <QLocale>
#include <QDir>
#include <QDebug>

ZestHelpViewer* ZestHelpViewer::instance = NULL;

ZestHelpViewer::ZestHelpViewer(QWidget *parent)
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

		qDebug() << "Online help has not yet been translated for locale"
				 << locale
				 << "- defaulting to english";

		helpPath = getHelpPathFromLocale("en");
	}



	ui.helpBrowser->setSource(QUrl(helpPath));
}




ZestHelpViewer::~ZestHelpViewer()
{

}

QString ZestHelpViewer::getHelpPathFromLocale(const QString& locale) const {

	QString helpPath;

	helpPath.append(Constants::ONLINE_HELP_LOCATION)
	    .append(QDir::separator())
	    .append(locale)
	    .append(QDir::separator())
	    .append("index.html");

	return helpPath;

}

ZestHelpViewer* ZestHelpViewer::getInstance() {

	if ( NULL == instance ) {

		instance = new ZestHelpViewer();
	}

	return instance;
}

void ZestHelpViewer::destroy() {

	if ( instance ) {

		delete instance;
		instance = NULL;
	}
}
