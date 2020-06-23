#include "enemyplus.h"

EnemyPlus::EnemyPlus(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite)
           :Enemy (startWayPoint,game,sprite)

{
    m_maxHp=80;
    m_walkingSpeed=3;
}
