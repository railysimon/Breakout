#include "checkpoint.h"


Checkpoint::Checkpoint(QRectF rect, int orientation) : bound(rect)
{
    check = orientation;
}

Checkpoint::~Checkpoint()
{

}

QRectF Checkpoint::boundingRect() const
{
    return bound;
}

void Checkpoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::NoPen));
    if(!check) painter->drawLine(0, 0, bound.width(), 0);
    else painter->drawLine(0, 0, 0, bound.height());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
