#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "mainwindow.h"
#include "utility.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize Tower::sizeofTower(80, 80);

Tower::Tower(QPoint pos, MainWindow *game, const QPixmap &sprite/* = QPixmap(":/image/tower.png"*/)
    : if_on_fire(false)
    , range_of_fire(130)
    , per_damage(6)
    , rate_of_attacking(1000)
    , the_enemy(NULL)
    , mainw(game)
    , tower_position(pos)
    , tower_picture(sprite)
    , tower_cost(300)
    ,life_span(5000)//生命长度为5秒
{
    tower_timer = new QTimer(this);
    connect(tower_timer, SIGNAL(timeout()), this, SLOT(shot()));

    /*t_life_timer=new QTimer;
    connect(t_life_timer,SIGNAL(timeout()),this,SLOT(removeTower()));
    tower_timer->start(life_span);//在lifespan之后调用removeTower()*/

}

Tower::~Tower()
{
    delete tower_timer;
    tower_timer= NULL;

    delete t_life_timer;
    t_life_timer=NULL;
}
void Tower::removeTower()
{
    mainw->removedTower(this);
}

void Tower::checkE()//看范围内的敌人
{
    if (the_enemy)//当前敌人
    {
        if (!collisionWithCircle(tower_position, range_of_fire, the_enemy->pos(), 1))//塔与敌人的距离超过范围
            cantSeeE();//看不见敌人
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        QList<Enemy *> enemyList = mainw->enemyList();
        foreach (Enemy *enemy, enemyList)
        {
            if (collisionWithCircle(tower_position, range_of_fire, enemy->pos(), 1))
            {
                findEnemytoAttack(enemy);
                break;
            }
        }
    }
}

void Tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::yellow);
    painter->drawEllipse(tower_position, range_of_fire, range_of_fire);
    painter->drawPixmap(tower_position.x()-sizeofTower.width()/2,tower_position.y()-sizeofTower.height()/2,80,80,tower_picture);
    painter->restore();

}

void Tower::attackE()
{
    tower_timer->start(rate_of_attacking);
}

void Tower::findEnemytoAttack(Enemy *e)
{
    the_enemy = e;
    attackE();
    the_enemy->getAttacked(this);
}

void Tower::shot()
{
    Bullet *bullet = new Bullet(tower_position, the_enemy->pos(), per_damage, the_enemy, mainw);
    bullet->move();
    mainw->addBullet(bullet);
}

void Tower::killcurrentE()
{
    if (the_enemy)
        the_enemy = NULL;

    tower_timer->stop();

}

void Tower::cantSeeE()
{
    the_enemy->gotLostSight(this);
    if (the_enemy)
        the_enemy = NULL;

    tower_timer->stop();
}
