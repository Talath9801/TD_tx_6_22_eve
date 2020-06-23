#include "blymcell.h"

BLymCell::BLymCell(QPoint pos, MainWindow *game, const QPixmap &sprite)
    :Tower (pos,game,sprite)
{
    set_range_of_fire(110);
    set_per_damage(8);
    set_rate_of_attacking(400);
}
