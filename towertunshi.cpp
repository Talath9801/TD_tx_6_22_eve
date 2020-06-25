#include "towertunshi.h"
#include <QTimer>
#include "mainwindow.h"
#include "bulleteat.h"
#include "enemy.h"
#include <QPainter>


TowerTunshi::TowerTunshi(QPoint pos, MainWindow *game, const QPixmap &sprite)
    :Tower (pos,game,sprite)
{
     set_tower_type_num(3);
     set_per_damage(200);
     set_rate_of_attacking(100);
     set_range_of_fire(110);
}
void TowerTunshi::killcurrentE()
{
    if (the_enemy)
        the_enemy = NULL;

    tower_timer->stop();
    can_eat--;
    if(can_eat<=0)
    {
        //mainw->removedTower(this);
        auto it = mainw->_towerPositionsList.begin();
        while (it != mainw->_towerPositionsList.end())
        {
            if (it->containPoint(this->get_tower_pos()))
            {
                it->setNotHasTower();
                break;
            }
            ++it;
        }
        mainw->removedTower(this);
    }
}


void TowerTunshi::shot()
{
    Bullet *bullet = new BulletEat(tower_position, the_enemy->pos(), per_damage, the_enemy, mainw);
    bullet->move();
    mainw->addBullet(bullet);
}

void TowerTunshi::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#44dc143c"));
    painter->drawEllipse(tower_position, range_of_fire, range_of_fire);
    painter->drawPixmap(tower_position.x()-sizeofTower.width()/2,tower_position.y()-sizeofTower.height()/2,100,100,tower_picture);
    painter->restore();
}
