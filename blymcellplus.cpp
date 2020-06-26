#include "blymcellplus.h"
#include <QPainter>

BLymCellPlus::BLymCellPlus(QPoint pos, MainWindow *game, const QPixmap &sprite)
    :BLymCell(pos,game,sprite)
{
    set_range_of_fire(150);
    set_per_damage(0);
    set_rate_of_attacking(1000);
    set_tower_type_num(6);
}
void BLymCellPlus::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#77fff5ee"));
    painter->drawEllipse(tower_position, range_of_fire, range_of_fire);
    painter->drawPixmap(tower_position.x()-sizeofTower.width()/2,tower_position.y()-sizeofTower.height()/2,100,100,tower_picture);
    painter->restore();
}
