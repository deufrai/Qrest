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

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <QSettings>

/**
 * Handles user settings.
 *
 * Uses singleton implementation.
 */
class Settings {

    ////////////////////////////////////////////////////////////////////////////
    //
    // INIT
    //
    ////////////////////////////////////////////////////////////////////////////
private:
    Settings();
    virtual ~Settings();

    ////////////////////////////////////////////////////////////////////////////
    //
    // MEMBERS
    //
    ////////////////////////////////////////////////////////////////////////////
private:
    /**
     * user's preferences.
     */
    QSettings _settings;

    /**
     * The only instance.
     */
    static Settings* _instance;

    ////////////////////////////////////////////////////////////////////////////
    //
    // QSettings KEYS
    //
    ////////////////////////////////////////////////////////////////////////////
public:
    /** key used to store window position. */
    static const char* WINDOW_POSITION;

    /** key used to store 'remember window position' flag. */
    static const char* REMEMBER_WINDOW_POSITION;

    // default values
    /** key used to store default window x position. */
    static const int WINDOW_POSITON_DEFAULT_X = 30;

    /** key used to store default window y position. */
    static const int WINDOW_POSITON_DEFAULT_Y = 30;

    /** key used to store 'remember window position' flag default value. */
    static const bool REMEMBER_WINDOW_POSITION_DEFAULT = false;

    ////////////////////////////////////////////////////////////////////////////
    //
    // INTERFACE
    //
    ////////////////////////////////////////////////////////////////////////////
public:
    /**
     * Get the only instance.
     *
     * \return the only instance.
     */
    static Settings* getInstance();

    /**
     * Release memory.
     */
    static void destroy();

    ////////////////////////////////////////////////////////////////////////////
    //
    // ACCESS
    //
    ////////////////////////////////////////////////////////////////////////////
    /**
     * get a reference to QSettings object.
     *
     * \return a reference to QSettings object.
     */
    inline QSettings& getSettings() {
        return _settings;
    }

};

#endif /* SETTINGS_H_ */
