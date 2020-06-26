#ifndef HIV_H
#define HIV_H

#include "enemy.h"
#include "towerposition.h"

class HIV:public Enemy
{
public:
    HIV(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/hiv.png"));
    ~HIV();
    void getAttacked(Tower *attacker);
    void set_num_can_kill(int x){num_can_kill=x;}
protected:
    int num_can_kill=1;
};

#endif // HIV_H
