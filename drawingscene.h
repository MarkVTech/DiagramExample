/*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
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

#ifndef DRAWINGSCENE_H
#define DRAWINGSCENE_H

#include <QObject>
#include <QRectF>
#include <QGraphicsScene>

class ShapeBase;

namespace Avoid
{
    class Router;
}

class ShapeBase;
class Edge;

class DrawingScene : public QGraphicsScene
{
    Q_OBJECT

public:
    DrawingScene(QObject *parent=0);
    DrawingScene(const QRectF& sceneRect, QObject *parent=0);
    DrawingScene(qreal x, qreal y, qreal width, qreal height, QObject *parent=0);

    ~DrawingScene();

    static DrawingScene* mStaticDrawingScene;

    void addShape(ShapeBase *shape);
    void addEdge(Edge* edge);

    Avoid::Router* router() const;
    void drawDiagram();

private slots:
    void handleSelectionChange();

#if 0
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
#endif

private:
    Avoid::Router* mRouter;

    void makeRouter_p();
    static void handleConnectorCallback_p(void* context);
};

#endif // DRAWINGSCENE_H
