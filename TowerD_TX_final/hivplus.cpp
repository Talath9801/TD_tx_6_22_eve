#include "hivplus.h"

HIVplus::HIVplus(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite)
    :HIV(startWayPoint,game,sprite)
{
     set_num_can_kill(3);
}
