#ifndef HIVPLUS_H
#define HIVPLUS_H

#include "hiv.h"
class HIVplus:public HIV
{
public:
    HIVplus(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/hivplus.png"));
};

#endif // HIVPLUS_H
