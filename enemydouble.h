#ifndef ENEMYDOUBLE_H
#define ENEMYDOUBLE_H

#include "enemy.h"
class EnemyDouble:public Enemy
{
public:
    EnemyDouble(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/enemydouble.png"));
    void doDoubleBlood();
    QTimer * timer_enemydouble;

public slots:
    void dospecial();
};

#endif // ENEMYDOUBLE_H
