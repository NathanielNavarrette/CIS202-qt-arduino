#ifndef BALLANIMATION_H
#define BALLANIMATION_H

#include <QWidget>
//#include <QGraphicsObject>

class BallAnimation : public QWidget
{
    Q_OBJECT
public:
    explicit BallAnimation(QWidget *parent = nullptr);
    void setOrigin(const QPoint &origin);
    void setMove(int x, int y);
    void addToOrigin(const QPoint &origin);


signals:

public slots:
    void paintEvent(QPaintEvent* event);

private:
    void collisionDetect();
    int randGen();
    int m_size = 150;
    QPoint m_origin;

    int xMod = 1;
    int yMod = 1;

    int m_bwidth = 10;
    int m_bheight = 10;
};

#endif // BALLANIMATION_H
