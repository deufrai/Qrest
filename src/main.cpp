/*
 *  qest
 *
 *  Copyright (C) 2008-2013 - Frédéric CORNU
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

#ifndef QT_NO_DEBUG
#include <QDebug>
#endif

#include <QApplication>
#include <QTranslator>
#include <QStringList>

#ifdef Q_WS_MAC
#include <QLibraryInfo>
#endif

#include "gui/widgets/qrestmainwindow.h"
#include "constants.h"
#include "helpers/localeHelper.h"
#include "settings/settings.h"
#include "midi/events/midieventfactory.h"
#include "midi/midihelper.h"
#include "model/document.h"

/**
 * Install translator into the application
 *
 * \param app : the target application
 * \param filePrefix : prefix used to ID this tranlsation
 * \param folderPath : path to the folder where translation is located
 * \param locale : locale to use for UI translation
 */
void installTranslator( QApplication& app, QString& filePrefix, QString& folderPath, QString& locale );

/**
 * Load objects serialized as QStrings in our Settings
 */
void loadSettings();

/**
 * Save objects into QStrings in our Settings
 */
void saveSettings();

//////////////////////////////////////////////////
//
// Life starts here
//
//////////////////////////////////////////////////
int main( int argc, char *argv[] ) {

    QApplication application( argc, argv );

    // load settings
    loadSettings();

    /* set UI locale according to (in order of priority)
     *
     *  - saved prefrences
     *  - commandLine argument
     *  - system default
     */
    QString locale;
    Document* pDoc = Document::getInstance();

    if( Settings::getInstance()->getSettings().contains( Settings::UI_PREFERRED_LOCALE ) ) {

        locale = Settings::getInstance()->getSettings().value( Settings::UI_PREFERRED_LOCALE ).toString();
        pDoc->setLocale( locale );

    } else if( 2 == argc ) {

        locale = QString( argv[1] );
        pDoc->setLocale( locale );

    } else {

        locale = LocaleHelper::getLocale();
        pDoc->setLocale( Constants::LOCALE_SYSDEFAULT );
    }

    QString appTransfilePrefix = "qrest_";
    QString appTransFolderPath = ":/i18n";
    installTranslator( application, appTransfilePrefix, appTransFolderPath, locale );

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
    installTranslator(application, qtTransfilePrefix, qtTransFolderPath, locale);

    // Don't show icons for menu items on Mac
    application.setAttribute(Qt::AA_DontShowIconsInMenus);
#endif

    // create main window
    QrestMainWindow mainWindow;
    mainWindow.show();

    int exec = application.exec();

    // save settings
    saveSettings();

    return exec;
}

////////////////////////////////////////////////////////////////////////////
//
// TOOLS
//
////////////////////////////////////////////////////////////////////////////

void installTranslator( QApplication& app, QString& filePrefix, QString& folderPath, QString& locale ) {

    QTranslator* pTranslator = new QTranslator();
    bool isTransLoaded = pTranslator->load( filePrefix + locale, folderPath );

    if( isTransLoaded ) {

#ifndef QT_NO_DEBUG
        qDebug() << "Translation file loaded successfully :" << filePrefix + locale;
#endif

        app.installTranslator( pTranslator );

    } else {

        qWarning( "Failed to load translation file : %s%s", filePrefix.toStdString().c_str(),
                locale.toStdString().c_str() );
    }

}

void loadSettings() {

    if( Settings::getInstance()->getSettings().contains( Settings::MIDI_TRIGGER_EVENT ) ) {

        QStringList list =
                Settings::getInstance()->getSettings().value( Settings::MIDI_TRIGGER_EVENT, 0 ).toStringList();

        Document::getInstance()->setTriggerEvent( MidiEventFactory::createEvent( list ) );
    }
}

void saveSettings() {

    const MidiEvent* event = Document::getInstance()->getTriggerEvent();

    if( event ) {

        QStringList list;

        if( const MidiNoteOn* note = dynamic_cast<const MidiNoteOn*>( event ) ) {

            list = MidiHelper::noteToStringList( note );

        } else if( const MidiProgramChange* program = dynamic_cast<const MidiProgramChange*>( event ) ) {

            list = MidiHelper::programToStringList( program );
        }

        Settings::getInstance()->getSettings().setValue( Settings::MIDI_TRIGGER_EVENT, list );
        Settings::getInstance()->getSettings().sync();
    }
}

