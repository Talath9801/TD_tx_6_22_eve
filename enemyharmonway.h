#ifndef ENEMYHARMONWAY_H
#define ENEMYHARMONWAY_H

#include "enemy.h"
class EnemyHarmOnWay:public Enemy
{
public:
    EnemyHarmOnWay(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/enemyharmonway.png"));
};

#endif // ENEMYHARMONWAY_H
