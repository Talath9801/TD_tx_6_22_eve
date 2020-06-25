#include "towerrangeall.h"

TowerRangeAll::TowerRangeAll(QPoint pos, MainWindow *game, const QPixmap &sprite)
    :Tower (pos,game,sprite)
{
     set_tower_type_num(2);
}
