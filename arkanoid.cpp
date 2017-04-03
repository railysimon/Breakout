#include "arkanoid.h"

Arkanoid::Arkanoid(QWidget *parent) : QDialog(parent), score(0)
{
    Layout();
    CreateBricks(4);

    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(Move()));
    timer->start();

    BallDirection();

    lose = nullptr;
}

Arkanoid::~Arkanoid()
{

}

void Arkanoid::Layout()
{
    this->setFixedSize(530, 500);
    scene = new QGraphicsScene(0, 0, width(), height());

    QLinearGradient gradient(0, 0, width(), height());
    gradient.setColorAt(0.5, QColor(65, 63, 63));
    gradient.setColorAt(1, QColor(44, 104, 151));

    QGraphicsRectItem *bg = scene->addRect(0, 0, width(), height());
    bg->setBrush(gradient);

    Score();

    CreateLifes();

    QGraphicsView *view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    left = scene->addLine(0, 0, 0, height());
    right = scene->addLine(width(), 0, width(), height());
    bottom = scene->addLine(0, height(), width(), height());
    top = scene->addLine(0, 0, width(), 0);

    platform = new Platform;
    scene->addItem(platform);
    scene->addItem(platform->first);
    scene->addItem(platform->second);
    scene->addItem(platform->third);
    platform->setPos(width() / 2, height() - 30);

    CreateBall();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);
    this->setLayout(layout);

}

void Arkanoid::CreateBricks(int size)
{
   Bricks *brick;
   int pos_x = 5, pos_y = 40;

   srand(time(NULL));

   for(int i=0; i<size; i++)
   {
       for(int j=0; j<7; j++)
       {
           brick = new Bricks(QColor(rand() % 250, rand() % 250, rand() % 250));
           brick->setPos(pos_x, pos_y);
           scene->addItem(brick);
           bricks.push_back(brick);
           scene->addItem(brick->top_border);
           scene->addItem(brick->left_border);
           scene->addItem(brick->right_border);
           pos_x += 75;
       }

       pos_y += 20;
       pos_x = 5;
   }
}

void Arkanoid::CreateBall()
{
    ball = scene->addEllipse(width() / 2, height() / 2, 20, 20);
    QRadialGradient grad(width() / 2, height() / 2, 20);
    grad.setColorAt(0.5, QColor(Qt::yellow));
    grad.setColorAt(1, QColor(150, 50, 150));
    ball->setPen(QPen(Qt::NoPen));
    ball->setBrush(grad);
}

void Arkanoid::CreateLifes()
{
    int step = 0;

    for(int i=0; i<3; i++)
    {
        lifes[i] = scene->addEllipse(5 + step, 17, 10, 10);
        lifes[i]->setBrush(QBrush(Qt::red));
        step += 15;
    }
}

void Arkanoid::Score()
{
    text = new QGraphicsTextItem("Score: " + QString::number(score));
    text->setFont(QFont("Ubuntu", 10, QFont::Bold));
    text->setDefaultTextColor(Qt::white);
    text->setPos(width() - 80, 10);
    scene->addItem(text);
}

void Arkanoid::Lose()
{
    timer->stop();
    scene->removeItem(lifes[0]);
    lose = new QGraphicsTextItem("Lose!");
    lose->setFont(QFont("Ubuntu", 24, QFont::Bold));
    lose->setPos(width() / 2 - 40, height() / 2);
    lose->setDefaultTextColor(Qt::white);
    scene->addItem(lose);
    scene->removeItem(ball);

    score = 0;

    Score();

    for(int i=0; i<bricks.size(); i++)
        scene->removeItem(bricks[i]);

    bricks.clear();
}

void Arkanoid::BallDirection()
{
    srand(time(NULL));
    int choice = rand() % 2 + 1;

    switch(choice)
    {
        case 1: {
                    step_x = -1;
                    step_y = 1;
                    break;
                }

        case 2: {
                    step_x = 1;
                    step_y = 1;
                    break;
                }
    }
}

void Arkanoid::NewLevel()
{
    srand(time(NULL));
    int size = rand() % 6 + 1;

    bricks.clear();
    CreateBricks(size);
    scene->removeItem(ball);
    CreateBall();
    BallDirection();
}

void Arkanoid::Move()
{
    if(ball->collidesWithItem(left)) // colide with main borders
        step_x = 1;

    if(ball->collidesWithItem(right))
        step_x = -1;

    for(int i=0; i<bricks.size(); i++) // colide with bricks
    {
        if(ball->collidesWithItem(bricks[i]->top_border))
        {
            step_y = -1;
            scene->removeItem(bricks[i]->top_border);
            scene->removeItem(bricks[i]->left_border);
            scene->removeItem(bricks[i]->right_border);
            scene->removeItem(bricks[i]);
            bricks.removeAt(i);

            score++;
            scene->removeItem(text);
            Score();

            continue;
        }

        if(ball->collidesWithItem(bricks[i]->left_border))
        {
            step_x = -1;
            scene->removeItem(bricks[i]->left_border);
            scene->removeItem(bricks[i]->right_border);
            scene->removeItem(bricks[i]->top_border);
            scene->removeItem(bricks[i]);
            bricks.removeAt(i);

            score++;
            scene->removeItem(text);
            Score();

            continue;
        }

        if(ball->collidesWithItem(bricks[i]->right_border))
        {
            step_x = 1;
            scene->removeItem(bricks[i]->right_border);
            scene->removeItem(bricks[i]->left_border);
            scene->removeItem(bricks[i]->top_border);
            scene->removeItem(bricks[i]);
            bricks.removeAt(i);

            score++;
            scene->removeItem(text);
            Score();

            continue;
        }

        if(ball->collidesWithItem(bricks[i]))
        {
            scene->removeItem(bricks[i]->top_border);
            scene->removeItem(bricks[i]->left_border);
            scene->removeItem(bricks[i]->right_border);
            scene->removeItem(bricks[i]);
            bricks.removeAt(i);
            step_y = 1;

            score++;
            scene->removeItem(text);
            Score();

            continue;
        }
    }

    if(ball->collidesWithItem(top)) // colide with main border
            step_y = 1;

    if(ball->collidesWithItem(platform->second)) // colide with platform
            step_y = -1;

    if(ball->collidesWithItem(platform->first))
    {
            step_y = -1;
            step_x = -1;
    }

    if(ball->collidesWithItem(platform->third))
    {
            step_y = -1;
            step_x = 1;
    }

    if(ball->collidesWithItem(bottom)) // colide with bottom
    {
        static int counter = 2;

        if(counter)
        {
            scene->removeItem(lifes[counter--]);
            scene->removeItem(ball);
            CreateBall();
            BallDirection();
        }
        else
        {
            Lose();

            counter = 2;
        }

    }

    if(!bricks.size()) NewLevel();

    ball->setPos(ball->x() + step_x, ball->y() + step_y); // moving
}

void Arkanoid::keyPressEvent(QKeyEvent *event)
{
    static bool press = false;

    if(event->key() == Qt::Key_A && !press)
        if(platform->x() > 0)
            platform->setPos(platform->x() - 5, platform->y());

    if(event->key() == Qt::Key_D && !press)
        if(platform->x() < width() - 90)
            platform->setPos(platform->x() + 5, platform->y());

    if(lose)
        if(event->key() == Qt::Key_Space)
        {
            CreateBall();
            CreateLifes();
            CreateBricks(4);

            timer->start();
            scene->removeItem(lose);
            lose = nullptr;
            BallDirection();
        }

    static QGraphicsTextItem *pause;

    if(event->key() == Qt::Key_Space && !lose)
    {
        if(!press)
        {
            pause = new QGraphicsTextItem("Pause");
            pause->setFont(QFont("Ubuntu", 24, QFont::Bold));
            pause->setPos(width() / 2 - 50, height() / 2);
            pause->setDefaultTextColor(Qt::white);
            scene->addItem(pause);

            timer->stop();
            press = true;
        }
        else
             {
                scene->removeItem(pause);
                timer->start();
                press = false;
             }
    }

}
