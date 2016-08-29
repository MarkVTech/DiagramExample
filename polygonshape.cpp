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

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QPainter>
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QRectF>
#include <QPointF>
#include <QDebug>
#include <QPolygonF>


#include <libavoid/router.h>
#include <libavoid/shape.h>

#include "shims.h"

#include "polygonshape.h"

PolygonShape::PolygonShape(const QPolygonF &polygon, Avoid::Router* router, QGraphicsItem *parent) :
    ShapeBase(router, parent),
    mPolygon(polygon),
    mBorder(0.0)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);

    Avoid::Polygon rect = convertPolygon(mPolygon);
    mShapeRef = new Avoid::ShapeRef(mRouter, rect);

    mPin = new Avoid::ShapeConnectionPin(mShapeRef, 1,
                                  Avoid::ATTACH_POS_CENTRE,
                                  Avoid::ATTACH_POS_CENTRE, true,
                                  0.0, Avoid::ConnDirAll);

    mConnEnd = new Avoid::ConnEnd(mShapeRef, 1);

    setZValue(1);
}

QRectF PolygonShape::boundingRect() const
{
    return mPolygon.boundingRect();
}

void PolygonShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen usePen;
    QBrush useBrush;

    if ( isSelected() )
    {
        usePen = QPen(mPen.brush(), mPen.widthF(), Qt::DashLine);
        useBrush = mBrush;
    }
    else
    {
        usePen = mPen;
        useBrush = mBrush;
    }

    painter->setPen(usePen);
    painter->setBrush(useBrush);
    painter->drawPolygon(mPolygon);

}

QVariant PolygonShape::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{

    if ( change == ItemPositionChange )
    {
        QRectF br = mPolygon.boundingRect();

        QPointF origPos = pos();
        QPointF newPos = value.toPointF();
        QRectF sceneRect = scene()->sceneRect();

        qreal checkX, checkY;

        checkX = sceneRect.right() - br.width() - mBorder;
        checkY = sceneRect.bottom() - br.height() - mBorder;

        if ( newPos.x() > checkX )
            newPos.setX(checkX);
        else if ( newPos.x() < sceneRect.left() + mBorder )
            newPos.setX(br.left() + mBorder);

        if ( newPos.y() > checkY )
            newPos.setY(checkY);
        else if ( newPos.y() < sceneRect.top()  + mBorder )
            newPos.setY(br.top() + mBorder);

        mRouter->moveShape(mShapeRef, newPos.x()-origPos.x(), newPos.y()-origPos.y());
        mRouter->processTransaction();

        emit shapeMoved();

        return newPos;
    }

    return QGraphicsObject::itemChange(change, value);
}

int PolygonShape::type() const
{
    return Type;
}


#if 0
void MyPolygonItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug() << "DOUBLE CLICK";
}

void MyPolygonItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug() << "Mouse MOVE";

    QGraphicsItem::mouseMoveEvent(mouseEvent);
}

void MyPolygonItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsItem::mousePressEvent(mouseEvent);
}

void MyPolygonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}
#endif
