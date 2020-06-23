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
    , range_of_fire(110)
    , per_damage(10)
    , rate_of_attacking(500)
    , the_enemy(NULL)
    , mainw(game)
    , tower_position(pos)
    , tower_picture(sprite)
{
    tower_timer = new QTimer(this);
    connect(tower_timer, SIGNAL(timeout()), this, SLOT(shot()));
}

Tower::~Tower()
{
    delete tower_timer;
    tower_timer= NULL;
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
