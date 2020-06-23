#ifndef TLYMCELL_H
#define TLYMCELL_H
#include <tower.h>

class TLymCell:public Tower
{
public:
    TLymCell(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/tlymcell.png"));
};

#endif // TLYMCELL_H
