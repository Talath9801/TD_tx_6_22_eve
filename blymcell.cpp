#include "blymcell.h"
#include "bulletslow.h"
#include "mainwindow.h"
#include "enemy.h"
#include "utility.h"
#include <QPainter>


BLymCell::BLymCell(QPoint pos, MainWindow *game, const QPixmap &sprite)
    :Tower (pos,game,sprite)
{
    set_range_of_fire(120);
    set_per_damage(0);
    set_rate_of_attacking(1000);
    set_tower_type_num(5);
}

void BLymCell::shot()
{
    Bullet *bullet = new BulletSlow(tower_position, the_enemy->pos(), per_damage, the_enemy, mainw);
    bullet->move();
    mainw->addBullet(bullet);
}
void BLymCell::checkE()
{
    if (the_enemy)//当前敌人
    {
        if (!collisionWithCircle(tower_position, range_of_fire, the_enemy->pos(), 1)||the_enemy->getwalkingspeed()<=1)
            //塔与敌人的距离超过范围  或者减速到底了
            cantSeeE();//看不见敌人
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        QList<Enemy *> enemyList = mainw->enemyList();
        foreach (Enemy *enemy, enemyList)
        {
            if (collisionWithCircle(tower_position, range_of_fire, enemy->pos(), 1)&&enemy->getwalkingspeed()>=1.5)
                //减速到底了的就不再打了
            {
                findEnemytoAttack(enemy);
                break;
            }
        }
    }
}
void BLymCell::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#33fff5ee"));
    painter->drawEllipse(tower_position, range_of_fire, range_of_fire);
    painter->drawPixmap(tower_position.x()-sizeofTower.width()/2,tower_position.y()-sizeofTower.height()/2,100,100,tower_picture);
    painter->restore();
}

