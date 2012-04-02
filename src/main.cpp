/*
 *  qest
 *
 *  Copyright (C) 2008-2011 - Frédéric CORNU
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

/** \mainpage Qrest Really Easy Studio Toolkit
 *
 *	\section intro Introduction
 *
 *	Qrest is still under heavy work.
 *
 *	Website : http://www.qrest.org
 *
 *	Have fun
 */

#include "model/document.h"
#include <QtGui>
#include <QApplication>
#include "gui/widgets/qrestmainwindow.h"
#include "constants.h"
#include "helpers/localeHelper.h"

int main(int argc, char *argv[]) {

    QApplication application(argc, argv);

    // create and install a translator according to system locale
    QTranslator translator;

    bool bTransLoaded = translator.load("qrest_" + LocaleHelper::getLocale(), ":/i18n");

    if (bTransLoaded) {

#ifndef QT_NO_DEBUG
        qDebug() << "Translation file loaded successfully";
#endif

        application.installTranslator(&translator);

    } else {

        qWarning() << "Failed to load translation file";
    }

    // create app data
    Document::getInstance();

    // create and show main window
    QrestMainWindow mainWindow;
    mainWindow.resize(mainWindow.minimumSizeHint());
    mainWindow.show();

    int nResult = application.exec();

    // release APP data
    Document::destroy();

    return nResult;
}
