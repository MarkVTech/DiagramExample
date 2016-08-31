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

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QColor>
#include <QBrush>
#include <QColorDialog>
#include <QDebug>
#include <QPainterPath>
#include <QGraphicsPathItem>
#include <QTransform>

#include "mainwindow.h"
#include "drawingscene.h"
#include "ui_mainwindow.h"
#include "rectangleshape.h"
#include "polygonshape.h"
#include "shims.h"
#include "shapebase.h"
#include "edge.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mBrush(Qt::gray),
    mPen(Qt::white),
    mPathItem(0)
{
    ui->setupUi(this);

    ui->changeBrushButton->setVisible(false);
    ui->changePenButton->setVisible(false);

    ui->graphicsView->setBackgroundBrush(QBrush(QColor("black")));
    mDrawingScene = new DrawingScene(0, 0, 640, 480, this);
    ui->graphicsView->setScene(mDrawingScene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    //ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    RectangleShape* mri1 = new RectangleShape(QSize(34, 67), mDrawingScene->router());
    mDrawingScene->addShape(mri1);
    mri1->setPos(47, 60);
    mri1->setPen(mPen);
    mri1->setBrush(mBrush);
    connect(mri1, SIGNAL(shapeMoved()), this, SLOT(handleShapeMoved()));

    RectangleShape* mri2 = new RectangleShape(QSize(45, 110), mDrawingScene->router());
    mDrawingScene->addShape(mri2);
    mri2->setPos(100, 110);
    mri2->setPen(mPen);
    mri2->setBrush(mBrush);
    connect(mri2, SIGNAL(shapeMoved()), this, SLOT(handleShapeMoved()));

    RectangleShape* mri3 = new RectangleShape(QSize(110, 110), mDrawingScene->router());
    mDrawingScene->addShape(mri3);
    mri3->setPos(200, 110);
    mri3->setPen(mPen);
    mri3->setBrush(mBrush);
    connect(mri3, SIGNAL(shapeMoved()), this, SLOT(handleShapeMoved()));

    RectangleShape* mri4 = new RectangleShape(QSize(40, 20), mDrawingScene->router());
    mDrawingScene->addShape(mri4);
    mri4->setPos(375, 110);
    mri4->setPen(mPen);
    mri4->setBrush(mBrush);
    connect(mri4, SIGNAL(shapeMoved()), this, SLOT(handleShapeMoved()));

    QPolygonF triangle;
    triangle << QPointF(0.0, 0.0) << QPointF(50.0, 0.0) << QPointF(25.0, 25.0);
    PolygonShape* poly1 = new PolygonShape(triangle, mDrawingScene->router());
    mDrawingScene->addShape(poly1);
    poly1->setPos(100, 50);
    poly1->setPen(mPen);
    poly1->setBrush(mBrush);
    connect(poly1, SIGNAL(shapeMoved()), this, SLOT(handleShapeMoved()));

    QPainterPath qpp1;
    qpp1.addEllipse(QRectF(0,0, 100, 50));
    QList<QPolygonF> list = qpp1.toSubpathPolygons(QTransform());
    QPolygonF ellipse;
    for ( int idx=0; idx<list.size(); ++idx )
    {
        ellipse << list.at(idx);
    }
    PolygonShape* poly2 = new PolygonShape(ellipse, mDrawingScene->router());
    mDrawingScene->addShape(poly2);
    poly2->setPen(mPen);
    poly2->setBrush(mBrush);
    connect(poly2, SIGNAL(shapeMoved()), this, SLOT(handleShapeMoved()));

    QPainterPath qpp2;
    qpp2.moveTo(0,0);
    qpp2.cubicTo(99, 0, 50, 50, 99, 99);
    QList<QPolygonF> list2 = qpp2.toSubpathPolygons(QTransform());
    QPolygonF curved;
    for ( int idx=0; idx<list2.size(); ++idx )
    {
        curved << list2.at(idx);
    }
    PolygonShape* poly3 = new PolygonShape(curved, mDrawingScene->router());
    mDrawingScene->addShape(poly3);
    poly3->setPen(mPen);
    poly3->setBrush(mBrush);
    QPointF thePoint = qpp2.pointAtPercent(0.75);
    qDebug() << "thePoint is" << thePoint;
    QGraphicsEllipseItem* qgie = mDrawingScene->addEllipse(QRectF(thePoint, QSize(10, 10)), QPen(Qt::red), QBrush(Qt::green));
    qgie->setZValue(4);
    qgie->setParentItem(poly3);
    connect(poly3, SIGNAL(shapeMoved()), this, SLOT(handleShapeMoved()));

    Edge* edge1 = new Edge("first", mDrawingScene->router(), mri1, mri2);
    edge1->setPen(QPen(Qt::green));
    mDrawingScene->addEdge(edge1);

    Edge* edge2 = new Edge("second", mDrawingScene->router(), mri1, mri3);
    edge2->setPen(QPen(Qt::red));
    mDrawingScene->addEdge(edge2);

    Edge* edge3 = new Edge("third", mDrawingScene->router(), mri2, mri3);
    edge3->setPen(QPen(Qt::yellow));
    mDrawingScene->addEdge(edge3);

    Edge* edge4 = new Edge("fourth", mDrawingScene->router(), mri4, mri1);
    edge4->setPen(QPen(Qt::cyan));
    mDrawingScene->addEdge(edge4);

    Edge* edge5 = new Edge("fifth", mDrawingScene->router(), mri4, mri2);
    edge5->setPen(QPen(Qt::blue));
    mDrawingScene->addEdge(edge5);

    Edge* edge6 = new Edge("sixth", mDrawingScene->router(), mri3, mri4);
    edge6->setPen(QPen(Qt::magenta));
    mDrawingScene->addEdge(edge6);

    Edge* edge7 = new Edge("seventh", mDrawingScene->router(), mri3, poly1);
    edge7->setPen(QPen(QColor("pink")));
    mDrawingScene->addEdge(edge7);

    Edge* edge8 = new Edge("eigth", mDrawingScene->router(), mri4, poly1);
    edge8->setPen(QPen(QColor("orange")));
    mDrawingScene->addEdge(edge8);

    Edge* edge9 = new Edge("eigth", mDrawingScene->router(), poly1, poly2);
    edge9->setPen(QPen(QColor("white")));
    mDrawingScene->addEdge(edge9);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_changeBrushButton_clicked()
{
    QColor newColor = QColorDialog::getColor();
    mBrush = QBrush(newColor);
}

void MainWindow::on_changePenButton_clicked()
{
    QColor newColor = QColorDialog::getColor();
    mPen = QPen(newColor);
}

void MainWindow::handleShapeMoved()
{
#if 0
    //qDebug() << "handleShapeMoved";
    QPainterPath path = makePainterPath(mConnRef);

    if ( mPathItem )
        mDrawingScene->removeItem(mPathItem);

    mPathItem = mDrawingScene->addPath(path, QColor("yellow"));
    mPathItem->setZValue(0);
#endif
}
