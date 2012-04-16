/*
 *  qest
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

#include <QtGui>
#include <QLibraryInfo>
#include <QApplication>

#include "model/document.h"
#include "gui/widgets/qrestmainwindow.h"
#include "constants.h"
#include "helpers/localeHelper.h"
#include "midi/midiengine.h"
#include "midi/midibroadcaster.h"


/**
 * Install translator into the application
 *
 * \param app : the target application
 * \param filePrefix : prefix used to ID this tranlsation
 * \param folderPath : path to the folder where translation is located
 */
void installTranslator (QApplication& app, QString& filePrefix, QString& folderPath);



//////////////////////////////////////////////////
//
// Life starts here
//
//////////////////////////////////////////////////
int main(int argc, char *argv[]) {

    QApplication application(argc, argv);

    // create and install translators for the application according to system locale
    QString appTransfilePrefix= "qrest_";
    QString appTransFolderPath = ":/i18n";
    installTranslator(application, appTransfilePrefix, appTransFolderPath);


#ifdef Q_WS_MAC

    /*
     * on Mac :
     *
     * - some menu entries are merged into the "application menu" and their translations are
     *   provided by a Qt specific translation file
     *
     * - no icons are shown next to menu items
     */

    // install translator for Qt itself
    QString qtTransfilePrefix= "qt_";
    QString qtTransFolderPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    installTranslator(application, qtTransfilePrefix, qtTransFolderPath);

    // Don't show icons for menu items on Mac
    application.setAttribute(Qt::AA_DontShowIconsInMenus);
#endif


    // create and show main window
    QrestMainWindow mainWindow;
    mainWindow.resize(mainWindow.minimumSizeHint());
    mainWindow.show();

    // connections
    QObject::connect(MidiBroadcaster::getInstance(),
    		SIGNAL(bip()),
    		MidiBroadcaster::getInstance(),
    		SLOT(onBip()));

    QObject::connect(MidiBroadcaster::getInstance(),
    		SIGNAL(start()),
    		MidiBroadcaster::getInstance(),
    		SLOT(onStart()));

    QObject::connect(MidiBroadcaster::getInstance(),
    	    SIGNAL(stop()),
    	    MidiBroadcaster::getInstance(),
    	    SLOT(onStop()));



    // init MIDI manager
    MidiEngine::getInstance()->start();

    return application.exec();
}



void installTranslator (QApplication& app, QString& filePrefix, QString& folderPath) {


    QTranslator* pTranslator = new QTranslator();

    bool isTransLoaded = pTranslator->load(filePrefix + LocaleHelper::getLocale(), folderPath);

    if (isTransLoaded) {

#ifndef QT_NO_DEBUG
        qDebug() << "Translation file loaded successfully : " << filePrefix + LocaleHelper::getLocale();
#endif

        app.installTranslator(pTranslator);

    } else {

        qWarning() << "Failed to load translation file : " << filePrefix + LocaleHelper::getLocale();
    }

}
