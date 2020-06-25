#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

//#include <string>

class QPainter;
class Enemy;
class MainWindow;
class QTimer;
//class TowerPosition;


class Tower : QObject
{
	Q_OBJECT
public:
	Tower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/tower.png"));
    ~Tower();

    virtual void draw(QPainter *painter) const;
    virtual void checkE();
    virtual void killcurrentE();
    void attackE();
    void findEnemytoAttack(Enemy *enemy);
    void getRidofB();
    void damageE();
    void cantSeeE();

    void set_range_of_fire(int x){range_of_fire=x;}
    void set_per_damage(int x){per_damage=x;}
    void set_rate_of_attacking(int x){rate_of_attacking=x;}
    void set_tower_cost(int x){tower_cost=x;}
    int  get_tower_cost(){return tower_cost;}
    void set_tower_type_num(int x){tower_type_num=x;}
    QPoint get_tower_pos(){return tower_position;}
    int get_tower_type_num(){return tower_type_num;}
    //TowerPosition  *located_position;
public slots:
    void removeTower();//拆塔

public slots:
    virtual void shot();

protected:
    bool if_on_fire;
    int	 range_of_fire;
    int	 per_damage;
    int	 rate_of_attacking;
    int  life_span;
    int  tower_cost;
    int  tower_type_num=0;

    Enemy *			the_enemy;
    MainWindow *	mainw;
    QTimer *		tower_timer;
    //QTimer *        t_life_timer;
    const QPoint	tower_position;
    const QPixmap	tower_picture;
    //std::string     tower_typename="tower";
    static const QSize sizeofTower;
};

#endif // TOWER_H
