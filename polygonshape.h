/*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright (C) 2016  Mark E. Wilson
*
*/

#ifndef POLYGONSHAPE_H
#define POLYGONSHAPE_H

#include <memory>

#include <QRectF>
#include <QSize>
#include <QRectF>
#include <QPen>
#include <QBrush>
#include <QGraphicsObject>

#include <libavoid/router.h>

#include "shapebase.h"

class QGraphicsItem;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;

namespace Avoid
{
    class Router;
    class ShapeRef;
    class ShapeConnectionPin;
    class ConnEnd;
}

class PolygonShape : public ShapeBase
{
    Q_OBJECT

public:
    enum
    {
        Type = UserType + 1
    };

    PolygonShape(const QPolygonF& size, Avoid::Router *router, QGraphicsItem* parent=0);

    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget=0);

    virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value);

    int type() const;

    const Avoid::ShapeConnectionPin* pin() const;

#if 0
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
#endif

signals:
    void shapeMoved();

private:
    QPolygonF mPolygon;
    qreal mBorder;


};

#endif // MYRECTANGLEITEM_H
