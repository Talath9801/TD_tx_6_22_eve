#ifndef BLYMCELLPLUS_H
#define BLYMCELLPLUS_H
#include "blymcell.h"

class BLymCellPlus:public BLymCell
{
public:
    BLymCellPlus(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/blymcellplus.png"));
    void draw(QPainter *painter) const;
};

#endif // BLYMCELLPLUS_H
