#include "blymcell.h"
#include "bulletslow.h"
#include "mainwindow.h"
#include "enemy.h"

BLymCell::BLymCell(QPoint pos, MainWindow *game, const QPixmap &sprite)
    :Tower (pos,game,sprite)
{
    set_range_of_fire(110);
    set_per_damage(8);
    set_rate_of_attacking(400);
    set_tower_type_num(5);
}

void BLymCell::shot()
{
    Bullet *bullet = new BulletSlow(tower_position, the_enemy->pos(), per_damage, the_enemy, mainw);
    bullet->move();
    mainw->addBullet(bullet);
}
