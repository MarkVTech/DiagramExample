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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBrush>
#include <QPen>
#include <QGraphicsPathItem>

class DrawingScene;

namespace Avoid
{
    class ConnRef;
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_changeBrushButton_clicked();
    void on_changePenButton_clicked();
    void handleShapeMoved();

private:
    Ui::MainWindow *ui;

    DrawingScene* mDrawingScene;

    QBrush mBrush;
    QPen mPen;

    Avoid::ConnRef* mConnRef;

    QGraphicsPathItem* mPathItem;
};

#endif // MAINWINDOW_H
