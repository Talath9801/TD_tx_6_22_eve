#ifndef BULLETSLOW_H
#define BULLETSLOW_H
#include "bullet.h"

class BulletSlow:public Bullet
{
public:
    BulletSlow(QPoint ori_posi, QPoint enemy_posi, int _damage, Enemy *the_e,
               MainWindow *mw, const QPixmap &_pict = QPixmap(":/image/bulletslow.png"));
};

#endif // BULLETSLOW_H
