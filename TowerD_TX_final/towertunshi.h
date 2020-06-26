#ifndef TOWERTUNSHI_H
#define TOWERTUNSHI_H
#include "tower.h"


class TowerTunshi:public Tower
{
public:
    TowerTunshi(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/phagocyte.png"));
    void set_num_can_eat(int x){can_eat=x;}
    void killcurrentE();
    void draw(QPainter *painter) const;
public slots:
    void shot();
protected:
    int can_eat=2;
};

#endif // TOWERTUNSHI_H
