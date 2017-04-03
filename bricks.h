#ifndef BRICKS_H
#define BRICKS_H

#include <QGraphicsItem>
#include <QPainter>

#include "checkpoint.h"

using namespace std;

class Checkpoint;

class Bricks : public QGraphicsItem
{

public:
        Bricks(QColor cl);
        ~Bricks();

private:
         QRectF boundingRect() const;
         void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
         QColor color;

public:
         Checkpoint *top_border, *right_border, *left_border;

};

#endif // BRICKS_H
