#include "towertunshi.h"
#include <QTimer>
#include "mainwindow.h"

TowerTunshi::TowerTunshi(QPoint pos, MainWindow *game, const QPixmap &sprite)
    :Tower (pos,game,sprite)
{
     set_tower_type_num(3);
     set_per_damage(200);
}
void TowerTunshi::killcurrentE()
{
    if (the_enemy)
        the_enemy = NULL;

    tower_timer->stop();
    can_eat--;
    if(can_eat<=0)
    {
        mainw->removedTower(this);
    }
}
