#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <mainwindow.h>

class WayPoint;
class QPainter;
class MainWindow;
class Tower;

class Enemy : public QObject
{
	Q_OBJECT
public:
	Enemy(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/enemy.png"));
	~Enemy();

	void draw(QPainter *painter) const;
    virtual void move();
	void getDamage(int damage);
	void getRemoved();
    virtual void getAttacked(Tower *attacker);
	void gotLostSight(Tower *attacker);
	QPoint pos() const;
    void setmaxHp(int x){m_maxHp=x;}
    void setcurrentHp(int x){m_currentHp=x;}
    void setwalkingspeed(qreal x){m_walkingSpeed=x;}
    qreal getwalkingspeed(){return m_walkingSpeed;}

public slots:
	void doActivate();
public slots:
    virtual void dospecial(){}
//protected slots:
  //  void doHarmOnWay(){mainw->getHpDamage();}

protected:
	bool			m_active;
    int				m_maxHp;
	int				m_currentHp;
	qreal			m_walkingSpeed;
    QPoint			m_pos;
	WayPoint *		m_destinationWayPoint;
    MainWindow *	mainw;
	QList<Tower *>	m_attackedTowersList;

    int rate_of_harm=1000;

	const QPixmap	m_sprite;
	static const QSize ms_fixedSize;


};

#endif // ENEMY_H
