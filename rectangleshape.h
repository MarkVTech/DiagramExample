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

#ifndef MYRECTANGLEITEM_H
#define MYRECTANGLEITEM_H

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

class RectangleShape : public ShapeBase
{
    Q_OBJECT

    //Q_PROPERTY(QPen pen READ pen WRITE setPen)
    //Q_PROPERTY(QBrush brush READ brush WRITE setBrush)

public:
    enum
    {
        Type = UserType + 1
    };

    RectangleShape(const QSize& size, Avoid::Router *router, QGraphicsItem* parent=0);

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
    QRectF mRect;
    qreal mBorder;


};

#endif // MYRECTANGLEITEM_H
