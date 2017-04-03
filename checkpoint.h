#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QGraphicsItem>
#include <QPainter>

using namespace std;

class Checkpoint : public QGraphicsItem
{
public:
        Checkpoint(QRectF rect, int orientation);
        ~Checkpoint();

private:
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
         QRectF bound;
         int check;
};

#endif // CHECKPOINT_H
