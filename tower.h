#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class MainWindow;
class QTimer;

class Tower : QObject
{
	Q_OBJECT
public:
	Tower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/tower.png"));
	~Tower();

	void draw(QPainter *painter) const;
    void checkE();
    void killcurrentE();
    void attackE();
    void findEnemytoAttack(Enemy *enemy);
    void getRidofB();
    void damageE();
    void cantSeeE();

private slots:
    void shot();

private:
    bool if_on_fire;
    int	 range_of_fire;
    int	 per_damage;
    int	 rate_of_attacking;

    Enemy *			the_enemy;
    MainWindow *	mainw;
    QTimer *		tower_timer;
    const QPoint	tower_position;
    const QPixmap	tower_picture;

    static const QSize sizeofTower;
};

#endif // TOWER_H
