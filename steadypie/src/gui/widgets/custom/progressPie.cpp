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
#include <QDebug>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

ProgressPie::ProgressPie(QWidget* parent)
: _threshold(0.9),
_value(0.0) {


}

ProgressPie::~ProgressPie() {

}


void ProgressPie::mousePressEvent(QMouseEvent* event) {

	//TODO : Not yet implemented!!!
	qDebug() << "mousePressEvent : Not yet implemented!!!";
}



void ProgressPie::mouseMoveEvent(QMouseEvent* event) {

	//TODO : Not yet implemented!!!
	qDebug() << "mouseMoveEvent : Not yet implemented!!!";
}



void ProgressPie::paintEvent(QPaintEvent* event) {

	//TODO : Finish me
	qDebug() << "paintEvent : start";

	QPainter painter(this);

	QBrush* pBrush;
	if ( _value < 200 ) {

		pBrush = new QBrush (Qt::red);

	} else {

		pBrush = new QBrush (Qt::darkGreen);
	}

	painter.setBrush(*pBrush);
	painter.setPen(Qt::NoPen);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.drawPie(0,0,minimumSizeHint().width() -5,minimumSizeHint().height() -5,0, static_cast<int>(_value*16));

	delete pBrush;

	qDebug() << "paintEvent : end";
}



void ProgressPie::setValue(const double value) {

	_value = value;
	repaint();
}
