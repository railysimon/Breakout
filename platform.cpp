#include "platform.h"

Platform::Platform()
{
    first = new Checkpoint(QRectF(0, 0, 30, 2), 0);
    second = new Checkpoint(QRectF(0, 0, 30, 2), 0);
    third = new Checkpoint(QRectF(0, 0, 30, 2), 0);
}

Platform::~Platform()
{

}

QRectF Platform::boundingRect() const
{
    return QRectF(0, 0, 90, 10);
}

void Platform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    painter->setBrush(Qt::white);
    painter->setPen(QPen(Qt::NoPen));
    painter->drawRect(rect);

    first->setPos(this->x(), this->y());
    second->setPos(this->x() + 30, this->y());
    third->setPos(this->x() + 60, this->y());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
