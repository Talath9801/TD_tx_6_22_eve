#ifndef TUNSHIPLUS_H
#define TUNSHIPLUS_H
#include "towertunshi.h"

class TunshiPlus:public TowerTunshi
{
public:
    TunshiPlus(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/phagocyteplus.png"));
    void draw(QPainter *painter) const;
};

#endif // TUNSHIPLUS_H
