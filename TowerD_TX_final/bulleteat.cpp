#include "bulleteat.h"

BulletEat::BulletEat(QPoint ori_posi, QPoint enemy_posi, int _damage, Enemy *the_e,
                     MainWindow *mw, const QPixmap &_pict)
    :Bullet (ori_posi,enemy_posi,_damage,the_e,mw,_pict)
{

}
