#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"


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
    int remember_tower_kind=0;
    bool point_in_rect(QRect &,QPoint &);
    QList<TowerPosition>	_towerPositionsList;

protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);

private slots:
	void updateMap();
	void gameStart();

private:
	void loadTowerPositions();
	void addWayPoints();
    bool load_Enemy_Wave();
	bool canBuyTower() const;
    void draw_Enemy_Wave(QPainter *painter);
    void draw_player_HP(QPainter *painter);
    void draw_Player_money(QPainter *painter);
	void doGameOver();
	void preLoadWavesInfo();
    QRect rec0=QRect(970,10,250,80);
    QRect rec1=QRect(970,100,250,80);
    QRect rec2=QRect(970,190,250,80);
    QRect rec3=QRect(970,280,250,80);
    QRect rec4=QRect(970,370,250,80);
    QRect rec5=QRect(970,460,250,80);
    QRect rec6=QRect(970,540,250,80);


private:
	Ui::MainWindow *		ui;
    int					     _waves;
    int						myHp;
    int						mymoney;
    bool					_gameEnded;
    bool					_gameWin;
    AudioPlayer *			_audioPlayer;
    QList<QVariant>			_wavesInfo;
    QList<Tower *>			_towersList;
    QList<WayPoint *>		_wayPointsList;
    QList<Enemy *>			_enemyList;
    QList<Bullet *>			_bulletList;
};

#endif // MAINWINDOW_H
