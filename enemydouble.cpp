#include "enemydouble.h"
#include <QTimer>
EnemyDouble::EnemyDouble(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite)
    :Enemy (startWayPoint,game,sprite)
{
    timer_enemydouble=new QTimer(this);
    connect(timer_enemydouble,SIGNAL(timeout()),this,SLOT(dospecial()));
    timer_enemydouble->start(10000);//            每10秒钟血量翻倍
}

void EnemyDouble::doDoubleBlood()
{
    setcurrentHp(m_currentHp*2);
}
void EnemyDouble::dospecial()
{
    doDoubleBlood();
}
EnemyDouble::~EnemyDouble()
{
    m_attackedTowersList.clear();
    m_destinationWayPoint = NULL;
    mainw = NULL;
    if(timer_enemydouble)
        delete timer_enemydouble;
    timer_enemydouble=NULL;
}
