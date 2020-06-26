#ifndef BULLETEAT_H
#define BULLETEAT_H
#include "bullet.h"

class BulletEat:public Bullet
{
public:
    BulletEat(QPoint ori_posi, QPoint enemy_posi, int _damage, Enemy *the_e,
              MainWindow *mw, const QPixmap &_pict = QPixmap(":/image/bulleteat.png"));
};

#endif // BULLETEAT_H
