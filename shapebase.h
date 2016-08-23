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

#ifndef SHAPEBASE_H
#define SHAPEBASE_H

#include <QGraphicsObject>
#include <QPen>
#include <QBrush>
#include <QString>

namespace Avoid
{
class Router;
class ShapeRef;
class ConnEnd;
class ShapeConnectionPin;
}

class ShapeBase : public QGraphicsObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QPen pen READ pen WRITE setPen)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush)

public:
    ShapeBase( Avoid::Router *router, QGraphicsItem* parent=0);

    QString name() const;
    void setName(const QString& name);

    QPen pen() const;
    void setPen(const QPen& pen);

    QBrush brush() const;
    void setBrush(const QBrush& brush);

    void setRouter(Avoid::Router *router);
    const Avoid::Router* router() const;

    const Avoid::ShapeRef* shapeRef() const;

    const Avoid::ShapeConnectionPin* pin() const;

    Avoid::ConnEnd *connectionEnd() const;

protected:
    Avoid::Router* mRouter;
    Avoid::ShapeRef* mShapeRef;
    Avoid::ShapeConnectionPin* mPin;
    Avoid::ConnEnd* mConnEnd;

    QString mName;
    QPen mPen;
    QBrush mBrush;
};

#endif // SHAPEBASE_H
