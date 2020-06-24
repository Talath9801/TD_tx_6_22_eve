#include "hiv.h"

HIV::HIV(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite)
    :Enemy (startWayPoint,game,sprite)
{

}
void HIV::getAttacked(Tower *attacker)
{
    if(num_can_kill>=1)
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
        num_can_kill--;
    }
    else
    {
        m_attackedTowersList.push_back(attacker);
    }
}
