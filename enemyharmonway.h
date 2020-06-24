#ifndef ENEMYHARMONWAY_H
#define ENEMYHARMONWAY_H
//#include <QObject>

#include "enemy.h"
class EnemyHarmOnWay:public Enemy
{
public:
    EnemyHarmOnWay(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/enemyharmonway.png"));
    ~EnemyHarmOnWay();
    void doHarmOnWay();
    QTimer *timer_enemyharmonway;

public slots:
    void dospecial();

};

#endif // ENEMYHARMONWAY_H
