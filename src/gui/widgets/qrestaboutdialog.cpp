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

#include "qrestaboutdialog.h"
#include <QLabel>
#include "../../constants.h"

QrestAboutDialog::QrestAboutDialog(const char* versionString, QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);

	QString aboutString;

	aboutString.append("<center>")
		.append("<h2>")
			.append("Qrest Really Easy Studio Toolkit")
		.append("</h2>")
		.append("<p>")
			.append("Version : ")
			.append(versionString)
		.append("</p>")
		.append("<p>")
			.append(tr("Author")).append(" : <a href=\"mailto:fcornu@wardsback.org?subject=Qrest\">fcornu@wardsback.org</a>")
		.append("</p>")
		.append("<p>")
			.append(tr("Website")).append(" : <a href=\"http://www.qrest.org/\">http://www.qrest.org</a>")
		.append("</p>")
	.append("</center>");

	ui.aboutLabel->setText(aboutString);

}

QrestAboutDialog::~QrestAboutDialog()
{

}
