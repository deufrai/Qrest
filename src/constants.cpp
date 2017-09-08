/*
 *  qrest
 *
 *  Copyright (C) 2008-2016 - Frédéric CORNU
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

#include "constants.h"

const char* Constants::VERSION_STRING = "0.6-beta-1";
const char* Constants::MIDI_ENGINE_NAME = "qrest";

const QString Constants::MIDI_TYPE_NOTE = "N";
const QString Constants::MIDI_TYPE_PC = "PC";

const QString Constants::LOCALE_SYSDEFAULT = "sys";
const QString Constants::LOCALE_EN = "en";
const QString Constants::LOCALE_FR = "fr";
const QString Constants::LOCALE_ES = "es";
const QString Constants::LOCALE_PT = "pt";

const double Constants::SECONDS_PER_MINUTE = 60.0;
const double Constants::MILLISEC_PER_SECOND = 1000.0;
const double Constants::STEADINESS_TARGET_RATIO = 0.90;
const double Constants::PROGRESSPIE_DEFAULT_VALUE = 0.0;
const double Constants::PROGRESSPIE_FULL = 1.0;
const double Constants::TEMPO_DEFAULT = 60.0;
const double Constants::TEMPO_MIN = 1.0;
const double Constants::TEMPO_MAX = 999.0;

Constants::Constants() {

}

Constants::~Constants() {

}
