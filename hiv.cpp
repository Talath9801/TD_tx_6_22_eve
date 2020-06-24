#include "hiv.h"

HIV::HIV(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite)
    :Enemy (startWayPoint,game,sprite)
{

}
void HIV::getAttacked(Tower *attacker)
{
    if(donekilling==false)
    {
        mainw->removedTower(attacker);
        donekilling=true;
    }
    else
    {
        m_attackedTowersList.push_back(attacker);
    }
}
