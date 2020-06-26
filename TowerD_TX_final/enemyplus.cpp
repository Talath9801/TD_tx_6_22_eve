#include "enemyplus.h"

EnemyPlus::EnemyPlus(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite)
          :Enemy(startWayPoint,game,sprite)
{
     setmaxHp(60);
     setcurrentHp(60);
     setwalkingspeed(4);
}
