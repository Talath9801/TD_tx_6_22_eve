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
/*protected:
    QTimer *   timer_enemyharmonway;
    int rate_of_harm=1000;*/
/*public slots:
    void doHarmOnWay();*/
};

#endif // ENEMYHARMONWAY_H
