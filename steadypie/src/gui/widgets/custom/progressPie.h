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

#ifndef PROGRESSPIE_H_
#define PROGRESSPIE_H_

#include <QWidget>

class QPaintEvent;
class QMouseEvent;

class ProgressPie : public QWidget {

	Q_OBJECT
	
public:

	ProgressPie(QWidget* parent = 0);
	virtual ~ProgressPie();

	inline void setThreshold(const double threshold) {

		_threshold = threshold;
	}

	inline double threshold() const {

		return _threshold;
	}
	

protected:
    void paintEvent(QPaintEvent *event);

public slots:
	void setValue(const double value);

private:
	double 	_threshold;
	double 	_value;
	QBrush*	_pRedBrush;
	QBrush*	_pGreenBrush;
};

#endif /* PROGRESSPIE_H_ */
