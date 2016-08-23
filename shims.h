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

#ifndef SHIMS_H_
#define SHIMS_H_

#include <QRectF>
#include <QPointF>
#include <QPolygonF>
#include <QPainterPath>

#include <libavoid/geomtypes.h>
#include <libavoid/connector.h>

QPointF convertPoint(const Avoid::Point& point);

Avoid::Point convertPoint(const QPointF& point);


QRectF convertRectangle(const Avoid::Rectangle& rect);

Avoid::Rectangle convertRectangle(const QRectF& rect);




Avoid::Polygon convertPolygon(const QRectF& rect);

Avoid::Polygon convertPolygon(const QPolygonF& polygon);

QPolygonF convertPolygon(const Avoid::Polygon& polygon);



QPainterPath convertPolyLine(const Avoid::PolyLine& polyline);

QPainterPath makePainterPath(Avoid::ConnRef* connection);

QPolygonF createArrow(const QPointF& start, const QPointF& end);

QPolygonF createArrow(Avoid::ConnRef* connection);

#endif // SHIMS_H_

