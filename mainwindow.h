#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"

//#include <string>


namespace Ui {
class MainWindow;
}

class WayPoint;
class Enemy;
class Bullet;
class AudioPlayer;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void getHpDamage(int damage = 1);
	void removedEnemy(Enemy *enemy);
    //新加
    void removedTower(Tower *tower);

	void removedBullet(Bullet *bullet);
	void addBullet(Bullet *bullet);
    void awardmoney(int money);
    void decreaseMoney(int money);


	AudioPlayer* audioPlayer() const;
	QList<Enemy *> enemyList() const;
    //std::string sdfa="sf";
    int remember_tower_kind=0;
    bool point_in_rect(QRect &,QPoint &);

protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);

private slots:
	void updateMap();
	void gameStart();

private:
	void loadTowerPositions();
	void addWayPoints();
	bool loadWave();
	bool canBuyTower() const;
	void drawWave(QPainter *painter);
	void drawHP(QPainter *painter);
	void drawPlayerGold(QPainter *painter);
	void doGameOver();
	void preLoadWavesInfo();
    QRect rec0=QRect(970,10,250,80);
    QRect rec1=QRect(970,100,250,80);
    QRect rec2=QRect(970,190,250,80);
    QRect rec3=QRect(970,280,250,80);

private:
	Ui::MainWindow *		ui;
    int					     _waves;
    int						myHp;
    int						mymoney;
    bool					_gameEnded;
    bool					_gameWin;
    AudioPlayer *			_audioPlayer;
    QList<QVariant>			_wavesInfo;
    QList<TowerPosition>	_towerPositionsList;
    QList<Tower *>			_towersList;
    QList<WayPoint *>		_wayPointsList;
    QList<Enemy *>			_enemyList;
    QList<Bullet *>			_bulletList;
};

#endif // MAINWINDOW_H
