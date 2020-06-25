#ifndef TOWERRANGEALL_H
#define TOWERRANGEALL_H
#include "tower.h"

class TowerRangeAll:public Tower
{
public:
    TowerRangeAll(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/towerrangeall.png"));
};

#endif // TOWERRANGEALL_H
