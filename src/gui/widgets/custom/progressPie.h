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

#ifndef PROGRESSPIE_H_
#define PROGRESSPIE_H_

#include <QWidget>

class QPaintEvent;
class QMouseEvent;

/**
 * Custom widget : a pie representing a double value between 0 and 1, wich gets
 * painted red when value is below a defined threshold and painted green
 * when value is above threshold.
 */
class ProgressPie: public QWidget {

Q_OBJECT

public:
    ////////////////////////////////////////////////////////////////////////////
    //
    // INIT
    //
    ////////////////////////////////////////////////////////////////////////////
    ProgressPie(QWidget* parent = 0);
    virtual ~ProgressPie();

    ////////////////////////////////////////////////////////////////////////////
    //
    // ACCESS
    //
    ////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////
    //
    // OVERRIDES
    //
    ////////////////////////////////////////////////////////////////////////////
protected:
    /**
     * Overrides QWidget::paintEvent.
     *
     * \param event the recieved paint event.
     */
    void paintEvent(QPaintEvent *event);

    ////////////////////////////////////////////////////////////////////////////
    //
    // SLOTS
    //
    ////////////////////////////////////////////////////////////////////////////
public slots:
    /**
     * set value and repaint widget.
     *
     * \param value the value to set
     */
    void setValue(const double value);

    ////////////////////////////////////////////////////////////////////////////
    //
    // MEMBERS
    //
    ////////////////////////////////////////////////////////////////////////////
private:
    /** the threshold. */
    double _threshold;

    /** the value. */
    double _value;

    /** red brush. */
    QBrush* _pRedBrush;

    /** dark green brush. */
    QBrush* _pGreenBrush;
};

#endif /* PROGRESSPIE_H_ */
