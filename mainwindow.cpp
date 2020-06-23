#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include "audioplayer.h"
#include "plistreader.h"
#include "tlymcell.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>


static const int TowerCost = 300;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, m_waves(0)
	, m_playerHp(5)
	, m_playrGold(1000)
	, m_gameEnded(false)
	, m_gameWin(false)
{
	ui->setupUi(this);

	preLoadWavesInfo();
	loadTowerPositions();
	addWayPoints();

	m_audioPlayer = new AudioPlayer(this);
	m_audioPlayer->startBGM();

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
	timer->start(30);

	// 设置300ms后游戏启动
	QTimer::singleShot(300, this, SLOT(gameStart()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::loadTowerPositions()
{
	QFile file(":/config/TowersPosition.plist");
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
		return;
	}

	PListReader reader;
	reader.read(&file);

	QList<QVariant> array = reader.data();
	foreach (QVariant dict, array)
	{
		QMap<QString, QVariant> point = dict.toMap();
		int x = point.value("x").toInt();
		int y = point.value("y").toInt();
		m_towerPositionsList.push_back(QPoint(x, y));
	}

	file.close();
}

void MainWindow::paintEvent(QPaintEvent *)
{
	if (m_gameEnded || m_gameWin)
	{
		QString text = m_gameEnded ? "YOU LOST!!!" : "YOU WIN!!!";
		QPainter painter(this);
		painter.setPen(QPen(Qt::red));
		painter.drawText(rect(), Qt::AlignCenter, text);
		return;
	}

	QPixmap cachePix(":/image/Bg.png");
	QPainter cachePainter(&cachePix);

	foreach (const TowerPosition &towerPos, m_towerPositionsList)
		towerPos.draw(&cachePainter);

	foreach (const Tower *tower, m_towersList)
		tower->draw(&cachePainter);

	foreach (const Enemy *enemy, m_enemyList)
		enemy->draw(&cachePainter);

	foreach (const Bullet *bullet, m_bulletList)
		bullet->draw(&cachePainter);

	drawWave(&cachePainter);
	drawHP(&cachePainter);
	drawPlayerGold(&cachePainter);

	QPainter painter(this);
	painter.drawPixmap(0, 0, cachePix);

    painter.setBrush(QColor("#deb887"));
    painter.drawRect(970,10,250,80);
    //painter.drawRect(970,100,250,80);
    //painter.drawRect(970,190,250,80);
    //painter.drawRect(970,280,250,80);
    //if(remember_tower_kind==1)painter.drawRect(970,280,250,80);

    QPixmap m_cell(":/image/tlymcell.png");
    painter.drawPixmap(970,10,80,80,m_cell);

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPoint = event->pos();
	auto it = m_towerPositionsList.begin();
	while (it != m_towerPositionsList.end())
	{
        if (canBuyTower() && it->containPoint(pressPoint) && !it->hasTower()&&event->button()==Qt::LeftButton&&remember_tower_kind==0)
		{
			m_audioPlayer->playSound(TowerPlaceSound);
			m_playrGold -= TowerCost;

			Tower *tower = new Tower(it->centerPos(), this);
            it->setHasTower(tower);
			m_towersList.push_back(tower);
			update();
			break;
		}
        else if (it->containPoint(pressPoint)&&it->hasTower()&&event->button()==Qt::RightButton)
        {
            removedTower(it->the_tower_in);
            it->the_tower_in=NULL;
            it->setNotHasTower();
        }
        //建塔，TLymCell类，记忆数值为1
        else if(canBuyTower() && it->containPoint(pressPoint) && !it->hasTower()&&event->button()==Qt::LeftButton&&remember_tower_kind==1)
        {
             m_playrGold-=TowerCost;
             Tower *tower=new TLymCell(it->centerPos(),this);
             it->setHasTower(tower);
             m_towersList.push_back(tower);
             update();
             remember_tower_kind=0;
             break;
        }

		++it;

	}

    //点击侧栏，选择tower种类
    if(point_in_rect(rec1,pressPoint))
    {
        remember_tower_kind=1;   //数值改变已成功
    }

}
bool MainWindow::point_in_rect(QRect &rec, QPoint &p)
{
    bool xin=(p.x()>=rec.x()&&p.x()<=rec.x()+rec.width());
    bool yin=(p.y()>=rec.y()&&p.y()<=rec.y()+rec.height());
    return (xin&&yin);
}

bool MainWindow::canBuyTower() const
{
	if (m_playrGold >= TowerCost)
		return true;
	return false;
}

void MainWindow::drawWave(QPainter *painter)
{
	painter->setPen(QPen(Qt::red));
	painter->drawText(QRect(400, 5, 100, 25), QString("WAVE : %1").arg(m_waves + 1));
}

void MainWindow::drawHP(QPainter *painter)
{
	painter->setPen(QPen(Qt::red));
	painter->drawText(QRect(30, 5, 100, 25), QString("HP : %1").arg(m_playerHp));
}

void MainWindow::drawPlayerGold(QPainter *painter)
{
	painter->setPen(QPen(Qt::red));
	painter->drawText(QRect(200, 5, 200, 25), QString("GOLD : %1").arg(m_playrGold));
}

void MainWindow::doGameOver()
{
	if (!m_gameEnded)
	{
		m_gameEnded = true;
		// 此处应该切换场景到结束场景
		// 暂时以打印替代,见paintEvent处理
	}
}

void MainWindow::awardGold(int gold)
{
	m_playrGold += gold;
	update();
}

AudioPlayer *MainWindow::audioPlayer() const
{
	return m_audioPlayer;
}

void MainWindow::addWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(785,50));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(785,480));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(582,480));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(582,165));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(373,165));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(373,480));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(160,480));
    m_wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(160,50));
    m_wayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);
}

void MainWindow::getHpDamage(int damage/* = 1*/)
{
	m_audioPlayer->playSound(LifeLoseSound);
	m_playerHp -= damage;
	if (m_playerHp <= 0)
		doGameOver();
}

void MainWindow::removedEnemy(Enemy *enemy)
{
	Q_ASSERT(enemy);

	m_enemyList.removeOne(enemy);
	delete enemy;

	if (m_enemyList.empty())
	{
		++m_waves;
		if (!loadWave())
		{
			m_gameWin = true;
			// 游戏胜利转到游戏胜利场景
			// 这里暂时以打印处理
		}
	}
}
void MainWindow::removedTower(Tower *tower)
{
    Q_ASSERT(tower);
    m_towersList.removeOne(tower);
    delete tower;
}

void MainWindow::removedBullet(Bullet *bullet)
{
	Q_ASSERT(bullet);

	m_bulletList.removeOne(bullet);
	delete bullet;
}

void MainWindow::addBullet(Bullet *bullet)
{
	Q_ASSERT(bullet);

	m_bulletList.push_back(bullet);
}

void MainWindow::updateMap()
{
	foreach (Enemy *enemy, m_enemyList)
		enemy->move();
	foreach (Tower *tower, m_towersList)
        tower->checkE();
	update();
}

void MainWindow::preLoadWavesInfo()
{
	QFile file(":/config/Waves.plist");
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
		return;
	}

	PListReader reader;
	reader.read(&file);

	// 获取波数信息
	m_wavesInfo = reader.data();

	file.close();
}

bool MainWindow::loadWave()
{
	if (m_waves >= m_wavesInfo.size())
		return false;

	WayPoint *startWayPoint = m_wayPointsList.back();
	QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

	for (int i = 0; i < curWavesInfo.size(); ++i)
	{
		QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
		int spawnTime = dict.value("spawnTime").toInt();

		Enemy *enemy = new Enemy(startWayPoint, this);
		m_enemyList.push_back(enemy);
		QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
	}

	return true;
}

QList<Enemy *> MainWindow::enemyList() const
{
	return m_enemyList;
}

void MainWindow::gameStart()
{
	loadWave();
}
