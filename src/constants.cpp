/*
 *  qrest
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

#include "constants.h"

const char* Constants::VERSION_STRING = "0.4.1";

#ifdef _WIN32
	const char* Constants::I18N_FOLDER_LOCATION = "i18n";
	const char* Constants::ONLINE_HELP_LOCATION = "doc/html";
#else
	const char* Constants::I18N_FOLDER_LOCATION = "/usr/share/qrest/i18n";
	const char* Constants::ONLINE_HELP_LOCATION = "/usr/share/qrest/doc/html";
#endif

Constants::Constants() {


}

Constants::~Constants() {

}
