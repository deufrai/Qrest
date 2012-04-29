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

#ifndef QT_NO_DEBUG
#include <QDebug>
#endif

#include "progressPie.h"
#include "../../../constants.h"
#include <QPaintEvent>
#include <QPainter>
#include <QLineEdit>

////////////////////////////////////////////////////////////////////////////
//
// INIT
//
////////////////////////////////////////////////////////////////////////////
ProgressPie::ProgressPie(QWidget* parent) :
    QWidget(parent),
    _value(Constants::PROGRESSPIE_DEFAULT_VALUE),
    _pRedBrush(new QBrush(Qt::red)),
    _pGreenBrush(new QBrush(Qt::darkGreen)) {

    /*
     * we want this widget to be enclosed within a square that has the same
     * height as a default QLineEdit.
     */
    QLineEdit usedForSizeHintHeight;
    int size = usedForSizeHintHeight.sizeHint().height();
    setFixedSize(size, size);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

ProgressPie::~ProgressPie() {

    delete _pGreenBrush;
    delete _pRedBrush;

}

////////////////////////////////////////////////////////////////////////////
//
// OVERRIDES
//
////////////////////////////////////////////////////////////////////////////
void ProgressPie::paintEvent(QPaintEvent* event) {

    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    painter.setRenderHint(QPainter::Antialiasing, true);

    /*
     * Qt draws angles with 1/16 degree precision.
     */
    static const int STEPS = 16;

    /*
     * pie is drawn starting from top, so we set startAngle at -270°
     */
    static const int TOP = -270* STEPS ;

    /*
     * how many degrees in a full circle ?
     */
    static const int FULL_CIRCLE = 360;

    /*
     * draw red circle
     */
    painter.setBrush(*_pRedBrush);
    painter.drawEllipse(this->visibleRegion().boundingRect());

    /*
     * draw green pie
     */
    painter.setBrush(*_pGreenBrush);
    painter.drawPie(this->visibleRegion().boundingRect(), TOP,
            static_cast<int> (-FULL_CIRCLE * _value * STEPS));

    event->accept();

}

////////////////////////////////////////////////////////////////////////////
//
// SLOTS
//
////////////////////////////////////////////////////////////////////////////
void ProgressPie::setValue(const double value) {

    _value = value;
    repaint();
}
