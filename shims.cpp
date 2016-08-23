/*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Foobar is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright (C) 2016  Mark E. Wilson
*
*/

#include <iostream>
#include <cmath>

#include "shims.h"


QPointF convertPoint(const Avoid::Point &point)
{
    return QPointF(point.x, point.y);
}

Avoid::Point convertPoint(const QPointF &point)
{
    return Avoid::Point(point.x(), point.y());
}

QRectF convertRectangle(const Avoid::Rectangle &rect)
{
    QRectF newRect;

    newRect.setTopRight(QPointF(rect.at(0).x, rect.at(0).y));
    newRect.setBottomRight(QPointF(rect.at(1).x, rect.at(1).y));
    newRect.setBottomLeft(QPointF(rect.at(2).x, rect.at(2).y));
    newRect.setTopLeft(QPointF(rect.at(3).x, rect.at(3).y));


    return newRect;
}


Avoid::Rectangle convertRectangle(const QRectF &rect)
{
    QPointF topLeft = rect.topLeft();
    QPointF bottomRight = rect.bottomRight();

    return Avoid::Rectangle(
            Avoid::Point(topLeft.x(), topLeft.y()),
            Avoid::Point(bottomRight.x(), bottomRight.y())
    );
}

Avoid::Polygon convertPolygon(const QRectF& rect)
{
    Avoid::Polygon newPolygon;

    newPolygon.setPoint(0, convertPoint(rect.topRight()));
    newPolygon.setPoint(1, convertPoint(rect.bottomRight()));
    newPolygon.setPoint(2, convertPoint(rect.bottomLeft()));
    newPolygon.setPoint(3, convertPoint(rect.topLeft()));

    return newPolygon;
}

Avoid::Polygon convertPolygon(const QPolygonF& polygon)
{
    Avoid::Polygon newPolygon;
    newPolygon.ps.clear();

    for (int idx=0; idx<polygon.size(); ++idx )
        newPolygon.ps.push_back(
                Avoid::Point(polygon[idx].x(), polygon[idx].y())
        );


    return newPolygon;
}

QPolygonF convertPolygon(const Avoid::Polygon &polygon)
{
    QPolygonF newPolygon;

    for ( unsigned int idx=0; idx<polygon.ps.size(); ++idx)
    {
        newPolygon.push_back(convertPoint(polygon.at(idx)));
    }

    return newPolygon;
}


QPainterPath convertPolyLine(const Avoid::PolyLine& polyline)
{
    Avoid::Point p = polyline.at(0);
    QPainterPath path(QPointF(p.x, p.y));

    for (size_t i=0; i<polyline.size(); ++i )
    {
        Avoid::Point point = polyline.at(i);
        path.lineTo(QPointF(point.x, point.y));
    }

    return path;
}

QPainterPath makePainterPath(Avoid::ConnRef* connection)
{
    QPointF arrowStart, arrowEnd;

    const Avoid::PolyLine displayRoute = connection->displayRoute();

    Avoid::Point p = displayRoute.at(0);
    QPainterPath path(QPointF(p.x, p.y));

    for (size_t i=0; i<displayRoute.size(); ++i )
    {
        Avoid::Point point = displayRoute.at(i);
        path.lineTo(QPointF(point.x, point.y));
    }

    return path;

}


 QPolygonF createArrow(const QPointF& start, const QPointF& end)
{
    qreal Pi = 3.14;
    qreal arrowSize = 10;

    QPolygonF arrowHead;

    QLineF line(end, start);

    double angle = ::acos(line.dx() / line.length());

    if ( line.dy() >= 0 )
        angle = (Pi * 2) - angle;

    QPointF arrowP1 = line.p1() + QPointF(sin(angle+Pi/3)*arrowSize,
            cos(angle+Pi/3)*arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle+Pi-Pi/3)*arrowSize,
            cos(angle+Pi-Pi/3)*arrowSize);


    arrowHead.clear();
    arrowHead << line.p1() << arrowP1 << arrowP2;

    return arrowHead;
}

QPolygonF createArrow(Avoid::ConnRef* connection)
{
    Avoid::PolyLine route = connection->displayRoute();
    int size = route.size();
    Avoid::Point start = route.at(size-2);
    Avoid::Point end = route.at(size-1);
    return createArrow(convertPoint(start), convertPoint(end));
}

