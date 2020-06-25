#include "towertunshi.h"


TowerTunshi::TowerTunshi(QPoint pos, MainWindow *game, const QPixmap &sprite)
    :Tower (pos,game,sprite)
{
     set_tower_type_num(3);
     set_per_damage(200);
}
