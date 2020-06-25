#include "tunshiplus.h"
#include <QPainter>

TunshiPlus::TunshiPlus(QPoint pos, MainWindow *game, const QPixmap &sprite)
    :TowerTunshi(pos,game,sprite)
{
    set_tower_type_num(4);
    set_per_damage(200);
    set_rate_of_attacking(120);
    set_range_of_fire(110);
    set_num_can_eat(5);
}
void TunshiPlus::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#77dc143c"));
    painter->drawEllipse(tower_position, range_of_fire, range_of_fire);
    painter->drawPixmap(tower_position.x()-sizeofTower.width()/2,tower_position.y()-sizeofTower.height()/2,100,100,tower_picture);
    painter->restore();
}
