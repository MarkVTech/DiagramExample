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

#include <libavoid/router.h>
#include <libavoid/shape.h>

#include "shapebase.h"

ShapeBase::ShapeBase(Avoid::Router *router, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    mRouter(router),
    mShapeRef(0),
    mName("default"),
    mPen(Qt::white),
    mBrush(Qt::black)
{

}

QString ShapeBase::name() const
{
    return mName;
}

void ShapeBase::setName(const QString &name)
{
   mName = name;
}

QPen ShapeBase::pen() const
{
    return mPen;
}

void ShapeBase::setPen(const QPen &pen)
{
    mPen = pen;
    update();
}

QBrush ShapeBase::brush() const
{
    return mBrush;
}

void ShapeBase::setBrush(const QBrush &brush)
{
    mBrush = brush;
    update();
}

void ShapeBase::setRouter(Avoid::Router *router)
{
    mRouter = router;
}

const Avoid::Router *ShapeBase::router() const
{
    return mRouter;
}

const Avoid::ShapeRef *ShapeBase::shapeRef() const
{
    return mShapeRef;
}


const Avoid::ShapeConnectionPin *ShapeBase::pin() const
{
    return mPin;
}

Avoid::ConnEnd *ShapeBase::connectionEnd() const
{
   return mConnEnd;
}
