#ifndef ENEMYPLUS_H
#define ENEMYPLUS_H
#include <enemy.h>

class EnemyPlus:public Enemy
{
public:
    EnemyPlus(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/enemyplus.png"));
    ~EnemyPlus();
};

#endif // ENEMYPLUS_H
