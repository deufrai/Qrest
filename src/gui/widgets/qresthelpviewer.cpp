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

#include "qresthelpviewer.h"
#include <QUrl>

QrestHelpViewer* QrestHelpViewer::instance = NULL;

////////////////////////////////////////////////////////////////////////////
//
// INIT
//
////////////////////////////////////////////////////////////////////////////
QrestHelpViewer::QrestHelpViewer(QWidget *parent)
: QMainWindow(parent) {

    ui.setupUi(this);
}

QrestHelpViewer::~QrestHelpViewer() {

}

////////////////////////////////////////////////////////////////////////////
//
// SINGLETON IMPLEMENTATION
//
////////////////////////////////////////////////////////////////////////////
QrestHelpViewer* QrestHelpViewer::getInstance() {

    if (NULL == instance) {

        instance = new QrestHelpViewer();
    }

    return instance;
}

void QrestHelpViewer::destroy() {

    delete instance;
    instance = NULL;
}


void QrestHelpViewer::setSource(const QString& source) {

    ui.helpBrowser->setSource(QUrl::fromLocalFile(source));
}
