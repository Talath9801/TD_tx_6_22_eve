#ifndef BLYMCELL_H
#define BLYMCELL_H
#include <tower.h>

class BLymCell:public Tower
{
public:
    BLymCell(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/blymcell.png"));
public slots:
    void shot();
};

#endif // BLYMCELL_H
