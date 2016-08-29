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

#include <QDebug>
#include <QList>
#include <QListIterator>

#include <libavoid/router.h>
#include <libavoid/shape.h>
#include <libavoid/connend.h>
#include <libavoid/connector.h>

#include "drawingscene.h"
#include "rectangleshape.h"
#include "edge.h"

DrawingScene* DrawingScene::mStaticDrawingScene = 0;

DrawingScene::DrawingScene(QObject* parent) :
    QGraphicsScene(parent)
{
    makeRouter_p();
    connect(this, SIGNAL(selectionChanged()), this, SLOT(handleSelectionChange()));
    DrawingScene::mStaticDrawingScene = this;
}

DrawingScene::DrawingScene(const QRectF& sceneRect, QObject* parent) :
    QGraphicsScene(sceneRect, parent)
{
    makeRouter_p();
    connect(this, SIGNAL(selectionChanged()), this, SLOT(handleSelectionChange()));
    DrawingScene::mStaticDrawingScene = this;
}

DrawingScene::DrawingScene(qreal x, qreal y, qreal width, qreal height, QObject* parent) :
    QGraphicsScene(x, y, width, height, parent)
{
    makeRouter_p();
    connect(this, SIGNAL(selectionChanged()), this, SLOT(handleSelectionChange()));
    DrawingScene::mStaticDrawingScene = this;
}

DrawingScene::~DrawingScene()
{
    delete mRouter;
}

void DrawingScene::handleConnectorCallback_p(void *context)
{
    Edge* edge = static_cast<Edge*>(context);
    edge->update();
}

void DrawingScene::addShape(ShapeBase *shape)
{
    addItem(shape);
}

void DrawingScene::addEdge(Edge *edge)
{
    edge->connection()->setCallback(&handleConnectorCallback_p, (void*) edge);
    addItem(edge);
}

Avoid::Router *DrawingScene::router() const
{
   return mRouter;
}

void DrawingScene::drawDiagram()
{

}

void DrawingScene::handleSelectionChange()
{
#if 0
    QList<QGraphicsItem*> selected = selectedItems();
    QListIterator<QGraphicsItem*> li(selected);

    while ( li.hasNext() )
    {
        QGraphicsItem* item = li.next();
        MyRectangleItem* mri = qgraphicsitem_cast<MyRectangleItem*>(item);

        //if ( mri )
        //{
            //mri->update();
        //}

    }
#endif
}

void DrawingScene::makeRouter_p()
{
    //mRouter = new Avoid::Router(Avoid::OrthogonalRouting);
    mRouter = new Avoid::Router(Avoid::PolyLineRouting);
    mRouter->setRoutingParameter(Avoid::shapeBufferDistance, 10.0);
    mRouter->setRoutingParameter(Avoid::idealNudgingDistance, 10.0);
    //mRouter->setRoutingOption(Avoid::nudgeOrthogonalSegmentsConnectedToShapes, true);
    //mRouter->setRoutingOption(Avoid::nudgeOrthogonalTouchingColinearSegments, true);
}


#if 0
void DrawingScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void DrawingScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void DrawingScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void DrawingScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

#endif
