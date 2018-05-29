#include "ballanimation.h"
#include <QPaintEvent>
#include <QPainter>
#include <QTime>
#include <QDebug>

/*
 * Note: m_origin is the origin of the ball in the square
 * this->height and this->width are the size of the square
 * (really its the size of the widget)
 * */

BallAnimation::BallAnimation(QWidget *parent) :
    QWidget(parent),
    m_origin(QPoint(48,50))

{
    setFixedSize(m_size, m_size);
}

void BallAnimation::setOrigin(const QPoint &origin)
{
    m_origin = origin;
}

void BallAnimation::addToOrigin(const QPoint &point)
{

    m_origin += point;
    qDebug() << "pos X: " << m_origin.x() << " Pos Y: " << m_origin.y();
}


void BallAnimation::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawRect(QRect(0,0,width()-1,height()-1));
    painter.setBrush(Qt::blue);
    painter.setPen(Qt::red);
    painter.drawEllipse(m_origin,m_bwidth,m_bheight);
    this->m_bheight = 10;
    this->m_bwidth = 10;
}

void BallAnimation::collisionDetect()
{
    if(m_origin.y() <= 0 + 12 && this->yMod < 0)
    {
        this->yMod *= -1 * randGen();
        this->m_bheight = 6;
    }else if(m_origin.x() >= this->width() - 12 && this->xMod > 0){
        this->xMod *= -1 * randGen();
        this->m_bwidth = 6;
    }else if(m_origin.y() >= this->height() - 12 && this->yMod > 0){
        this->yMod *= -1 * randGen();
        this->m_bheight = 6;
    }else if(m_origin.x() <= 0 + 12 && this->xMod < 0){
        this->xMod *= -1 * randGen();
        this->m_bwidth = 6;
    }

    int prev_x = this->xMod;
    int prev_y = this->yMod;

    this->yMod %= 4 +1;
    this->xMod %= 4 +1;

    if(this->xMod >= 0 && prev_x < 0)
        this->xMod += -1;
    else if(this->yMod >= 0 && prev_y < 0)
        this->yMod += -1;
    else if(this->xMod <= 0 && prev_x >= 0)
        this->xMod += 1;
    else if(this->yMod <= 0 && prev_y >= 0)
        this->yMod += 1;

    //check if it glitches out and flies out
    if(m_origin.y() >= this-> height() || m_origin.y() < 0 || m_origin.x() >= this->height() || m_origin.x() < 0)
        setOrigin(QPoint(50, 50));
}

int BallAnimation::randGen()
{
    int max = 2;
    qsrand(QDateTime::currentMSecsSinceEpoch()%5000); //q seed random

    int my_rand = qrand();
    my_rand %= max;
    return (my_rand + 1);
}

void BallAnimation::setMove(int mv_x, int mv_y)
{
    collisionDetect();
    addToOrigin( QPoint( (mv_x * xMod), (mv_y * yMod) ));
}
