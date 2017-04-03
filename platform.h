#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsItem>
#include <QPainter>

#include "checkpoint.h"

class Checkpoint;

class Platform : public QGraphicsItem
{
public:
        Platform();
        ~Platform();

private:
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
        Checkpoint *first, *second, *third;

};

#endif // PLATFORM_H
