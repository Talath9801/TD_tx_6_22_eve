#include "enemyharmonway.h"
#include <QTimer>
#include <mainwindow.h>
#include "utility.h"
#include "waypoint.h"

EnemyHarmOnWay::EnemyHarmOnWay(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite)
    :Enemy (startWayPoint,game,sprite)
{
    timer_enemyharmonway=new QTimer(this);
    connect(timer_enemyharmonway,SIGNAL(timeout()),this,SLOT(dospecial()));
    timer_enemyharmonway->start(1000);

}

void EnemyHarmOnWay::dospecial()
{
    doHarmOnWay();
}

EnemyHarmOnWay::~EnemyHarmOnWay()
{
    m_attackedTowersList.clear();
    m_destinationWayPoint = NULL;
    mainw = NULL;
}

void EnemyHarmOnWay::doHarmOnWay()
{
    mainw->decreaseMoney(20);
    //mainw->update();
}
