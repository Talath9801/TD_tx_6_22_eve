#ifndef HIV_H
#define HIV_H

#include "enemy.h"
#include "towerposition.h"

class HIV:public Enemy
{
public:
    HIV(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/hiv.png"));
    void getAttacked(Tower *attacker);
protected:
    bool donekilling=false;
};

#endif // HIV_H
