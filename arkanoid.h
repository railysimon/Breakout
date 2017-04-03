#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QVBoxLayout>
#include <QVector>
#include <QKeyEvent>
#include <QTimer>
#include <QLinearGradient>
#include <QGraphicsTextItem>
#include <QRadialGradient>

#include <ctime>
#include "bricks.h"
#include "platform.h"
#include "checkpoint.h"

class Bricks;
class Platform;

class Arkanoid : public QDialog
{
    Q_OBJECT

public:
    Arkanoid(QWidget *parent = 0);
    ~Arkanoid();

private:
        QGraphicsScene *scene;
        QVector<Bricks*> bricks;
        QGraphicsLineItem *left, *right, *top, *bottom;
        Platform *platform;
        QGraphicsEllipseItem *ball;
        QTimer *timer;
        QGraphicsTextItem *text, *lose;
        QGraphicsEllipseItem *lifes[3];

private:
         int step_x, step_y;
         int score;

private:
         void Layout();
         void CreateBricks(int size);
         void CreateBall();
         void CreateLifes();
         void Score();
         void Lose();
         void BallDirection();
         void NewLevel();

protected:
         virtual void keyPressEvent(QKeyEvent *event);

private slots:
                void Move();

};

#endif // DIALOG_H
