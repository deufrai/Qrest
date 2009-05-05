/*
 *  qrest
 *
 *  Copyright (C) 2008-2009 - Frédéric CORNU
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

#include "progressPie.h"
#include "../../../constants.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QLineEdit>

////////////////////////////////////////////////////////////////////////////
//
// INIT
//
////////////////////////////////////////////////////////////////////////////
ProgressPie::ProgressPie(QWidget* parent)
: QWidget(parent),
  _threshold(0.0),
  _value(0.0),
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

}


////////////////////////////////////////////////////////////////////////////
//
// OVERRIDES
//
////////////////////////////////////////////////////////////////////////////
void ProgressPie::paintEvent(QPaintEvent* event) {

	QPainter painter(this);

	/*
	 * paint in red if value is below threshold
	 */
	if ( _value < _threshold ) {

		painter.setBrush(*_pRedBrush);

	} else {

		painter.setBrush(*_pGreenBrush);
	}

	painter.setRenderHint(QPainter::Antialiasing, true);

	/*
	 * Qt draws angles with 1/16 degree precision.
	 */
	static const int STEPS = 16;

	/*
	 * pie is drawn starting from top, so we set startAngle at -270°
	 */
	static const int TOP = -270*STEPS;

	/**
	 * how many degrees in a full circle ?
	 */
	static const int FULL_CIRCLE = 360;

	/*
	 * We don't want the widget to disappear
	 */
	if ( _value < Constants::STEADINESS_ALWAYS_SHOW_VALUE ) {

		_value = Constants::STEADINESS_ALWAYS_SHOW_VALUE;
	}

	/*
	 * draw pie
	 */
	painter.setPen(Qt::NoPen);

	painter.drawPie(this->visibleRegion().boundingRect(),
			TOP,
			static_cast<int>(- FULL_CIRCLE * _value * STEPS ));

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
