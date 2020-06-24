#ifndef HIV_H
#define HIV_H

#include "enemy.h"
class HIV:public Enemy
{
public:
    HIV(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/hiv.png"));
};

#endif // HIV_H
