#include "hiv.h"

HIV::HIV(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite)
    :Enemy (startWayPoint,game,sprite)
{

}
void HIV::getAttacked(Tower *attacker)
{
    if(donekilling==false)
    {
        auto it = mainw->_towerPositionsList.begin();
        while (it != mainw->_towerPositionsList.end())
        {
            if (it->containPoint(attacker->get_tower_pos()))
            {
                it->setNotHasTower();
                break;
            }
            ++it;
        }
        //                                上面要将attacker所在的塔基设置为“无塔”
        mainw->removedTower(attacker);
        donekilling=true;
    }
    else
    {
        m_attackedTowersList.push_back(attacker);
    }
}
