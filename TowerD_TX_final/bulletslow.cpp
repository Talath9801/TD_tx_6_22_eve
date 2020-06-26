#include "bulletslow.h"
#include "mainwindow.h"
#include "enemy.h"

BulletSlow::BulletSlow(QPoint ori_posi, QPoint enemy_posi, int _damage, Enemy *the_e,
                       MainWindow *mw, const QPixmap &_pict)
      :Bullet (ori_posi,enemy_posi,_damage,the_e,mw,_pict)
{

}
void BulletSlow::get_to_enemy()
{
    if (mainw->enemyList().indexOf(the_enemy) != -1)
    {
        the_enemy->getDamage(perdam);
        if(the_enemy->getwalkingspeed()<=1)
        {

        }
        else
        {
            the_enemy->setwalkingspeed(the_enemy->getwalkingspeed()-0.5);
        }
    }
    mainw->removedBullet(this);
}
