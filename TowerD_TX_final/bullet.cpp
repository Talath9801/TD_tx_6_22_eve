#include "bullet.h"
#include "enemy.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPropertyAnimation>

const QSize Bullet::sizeofBullet(15,15);

Bullet::Bullet(QPoint ori_posi, QPoint enemy_posi, int _damage, Enemy *the_e,
               MainWindow *mw, const QPixmap &_pict)
    : originPosition(ori_posi)
    , enemyPosition(enemy_posi)
    , bullet_picture(_pict)
    , bullet_position(ori_posi)
    , the_enemy(the_e)
    , mainw(mw)
    , perdam(_damage)
{
}

void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(bullet_position.x(),bullet_position.y(),15,15, bullet_picture);
}
void Bullet::setposition(QPoint _position)
{
    bullet_position=_position;
}

QPoint Bullet::cu_position() const
{
    return bullet_position;
}

void Bullet::move()
{
    // 100毫秒内击中敌人
    static const int time_to_enemy = 100;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "bullet_position");
    animation->setDuration(time_to_enemy);
    animation->setStartValue(originPosition);
    animation->setEndValue(enemyPosition);
    connect(animation, SIGNAL(finished()), this, SLOT(get_to_enemy()));

    animation->start();
}

void Bullet::get_to_enemy()
{
    if (mainw->enemyList().indexOf(the_enemy) != -1)
        the_enemy->getDamage(perdam);
    mainw->removedBullet(this);
}

