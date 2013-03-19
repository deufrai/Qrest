/*
 *  qrest
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

    /** key used to store MIDI port name */
    static const char* MIDI_PORT_NAME;

    /** key used to store MIDI port default name */
    static const char* MIDI_PORT_NAME_DEFAUT;

    /** key used to store MIDI device name */
    static const char* MIDI_DEVICE;

    /** key used to store MIDI device name when MIDI has never been used */
    static const char* MIDI_DEVICE_DEFAULT;

    /** key used to store the TAP MIDI trigger event */
    static const char* MIDI_TRIGGER_EVENT;

    /** key used to store user preferred locale */
    static const char* UI_PREFERRED_LCOALE;

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
