#include "bricks.h"

Bricks::Bricks(QColor cl) : color(cl)
{
    top_border = new Checkpoint(QRectF(0, 0, 70, 2), 0);
    left_border = new Checkpoint(QRectF(0, 0, 2, 15), 1);
    right_border = new Checkpoint(QRectF(0, 0, 2, 15), 1);
}

Bricks::~Bricks()
{

}

QRectF Bricks::boundingRect() const
{
    return QRectF(0, 0, 70, 15);
}

void Bricks::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(color);
    painter->drawRect(rect);

    top_border->setPos(this->x(), this->y());
    left_border->setPos(this->x(), this->y());
    right_border->setPos(this->x() + 70, this->y());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
