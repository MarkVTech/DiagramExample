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

#include <QPainter>
#include <QPainterPath>
#include <QDebug>

#include <libavoid/connector.h>
#include <libavoid/router.h>

#include "edge.h"
#include "shapebase.h"
#include "shims.h"

Edge::Edge(const QString &name, Avoid::Router* router, ShapeBase *src, ShapeBase *dst, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    mName(name),
    mRouter(router),
    mSrc(src),
    mDst(dst),
    mConnRef(0)
{
    mConnRef = new Avoid::ConnRef(mRouter, *(mSrc->connectionEnd()), *(mDst->connectionEnd()));
    mRouter->processTransaction();
    mPath = makePainterPath(mConnRef);
}

QPainterPath Edge::shape() const
{
    return makePainterPath(mConnRef);
}

QRectF Edge::boundingRect() const
{
    return mPath.boundingRect();
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    prepareGeometryChange();
    mPath = makePainterPath(mConnRef);
    painter->setPen(mPen);
    painter->drawPath(mPath);
}

QString Edge::name() const
{
    return mName;
}

void Edge::setName(const QString &name)
{
   mName = name;
}

QPen Edge::pen() const
{
    return mPen;
}

void Edge::setPen(const QPen &pen)
{
    mPen = pen;
    update();
}

ShapeBase *Edge::source() const
{
   return mSrc;
}

void Edge::setSource(ShapeBase *shape)
{
    mSrc = shape;
}

ShapeBase *Edge::destination() const
{
   return mDst;
}

void Edge::setDestination(ShapeBase *shape)
{
    mDst = shape;
}

Avoid::ConnRef *Edge::connection() const
{
    return mConnRef;
}

QPainterPath Edge::path()
{
    mPath = makePainterPath(mConnRef);
   return mPath;
}
