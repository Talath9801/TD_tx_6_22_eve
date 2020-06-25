#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waypoint.h"
#include "enemy.h"
#include "enemydouble.h"
#include "enemyplus.h"
#include "hiv.h"
#include "hivplus.h"
#include "enemyharmonway.h"
#include "bullet.h"
#include "audioplayer.h"
#include "plistreader.h"
#include "tlymcell.h"
#include "towerrangeall.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>



static const int maxTowerCost = 300;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _waves(0)
    , myHp(50)
    , mymoney(1000)
    , _gameEnded(false)
    , _gameWin(false)
{
    ui->setupUi(this);

    preLoadWavesInfo();
    loadTowerPositions();
    addWayPoints();

    _audioPlayer = new AudioPlayer(this);
    _audioPlayer->startBGM();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);

    // 设置300ms后游戏启动
    QTimer::singleShot(300, this, SLOT(gameStart()));

    //decreaseMoney(30);
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
        _towerPositionsList.push_back(QPoint(x, y));
    }

    file.close();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if (_gameEnded || _gameWin)
    {
        QString text = _gameEnded ? "YOU LOST!!!" : "YOU WIN!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }

    QPixmap cachePix(":/image/Bg.png");
    QPainter cachePainter(&cachePix);

    foreach (const TowerPosition &towerPos, _towerPositionsList)
        towerPos.draw(&cachePainter);

    foreach (const Tower *tower, _towersList)
        tower->draw(&cachePainter);

    foreach (const Enemy *enemy, _enemyList)
        enemy->draw(&cachePainter);

    foreach (const Bullet *bullet, _bulletList)
        bullet->draw(&cachePainter);

    drawWave(&cachePainter);
    drawHP(&cachePainter);
    drawPlayerGold(&cachePainter);

    QPainter painter(this);
    painter.drawPixmap(0, 0, cachePix);
    //  画出棕色背景底图
    painter.setBrush(QColor("#cd853f"));
    painter.setPen(Qt::NoPen);
    painter.drawRect(955,0,277,640);


    painter.setBrush(QColor("#deb887"));
    painter.drawRect(rec1);//第一栏
    painter.drawRect(rec2);//第二栏

    //                                                         画细胞的图片和文字信息
    QPixmap m_cell(":/image/tlymcell.png");//
    painter.drawPixmap(970,100,80,80,m_cell);
    painter.setPen(Qt::black);
    painter.drawText(QRect(1050,100,170,80),QString("攻击范围110，攻击频率400ms，每次对敌人造成的伤害8，花费300"));

    m_cell.load(":/image/towerrangeall.png");
    painter.drawPixmap(970,190,80,80,m_cell);
    painter.setPen(Qt::black);
    painter.drawText(QRect(1050,190,170,80),QString("对HIV及其变种有防御功能，攻击HIV的时候自己不会死"));


    painter.setBrush(QColor("#cd853f"));
    painter.setPen(Qt::NoPen);
    painter.drawRect(0,638,1232,152);
    painter.setBrush(QColor("#faebd7"));
    painter.drawRect(5,645,200,140);
    painter.drawRect(210,645,200,140);
    painter.drawRect(415,645,200,140);
    painter.drawRect(620,645,200,140);
    painter.drawRect(825,645,200,140);
    painter.drawRect(1030,645,200,140);


}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPoint = event->pos();
    auto it = _towerPositionsList.begin();
    while (it != _towerPositionsList.end())
    {
        if (canBuyTower() && it->containPoint(pressPoint) && !it->hasTower()&&event->button()==Qt::LeftButton&&remember_tower_kind==0)
        {
            _audioPlayer->playSound(TowerPlaceSound);
            //m_playrGold -= TowerCost;

            Tower *tower = new Tower(it->centerPos(), this);
            //tower->located_positio
            it->setHasTower(tower);
            _towersList.push_back(tower);
            mymoney-=tower->get_tower_cost();
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
            //m_playrGold-=TowerCost;
            Tower *tower=new TLymCell(it->centerPos(),this);
            it->setHasTower(tower);
            _towersList.push_back(tower);
            mymoney-=tower->get_tower_cost();
            update();
            remember_tower_kind=0;
            break;
        }
        else if(canBuyTower() && it->containPoint(pressPoint) && !it->hasTower()&&event->button()==Qt::LeftButton&&remember_tower_kind==2)
        {
            //m_playrGold-=TowerCost;
            Tower *tower=new TowerRangeAll(it->centerPos(),this);
            it->setHasTower(tower);
            _towersList.push_back(tower);
            mymoney-=tower->get_tower_cost();
            update();
            remember_tower_kind=0;
            break;
        }

        ++it;

    }

    //                                                              点击侧栏，选择tower种类，记录数值编号
    if(point_in_rect(rec1,pressPoint))
    {
        remember_tower_kind=1;
    }
    else if(point_in_rect(rec2,pressPoint))
    {
        remember_tower_kind=2;
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
    if (mymoney >= maxTowerCost)
        return true;
    return false;
}

void MainWindow::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(400, 5, 100, 25), QString("WAVE : %1").arg(_waves + 1));
}

void MainWindow::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(30, 5, 100, 25), QString("HP : %1").arg(myHp));
}

void MainWindow::drawPlayerGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(200, 5, 200, 25), QString("GOLD : %1").arg(mymoney));
}

void MainWindow::doGameOver()
{
    if (!_gameEnded)
    {
        _gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

void MainWindow::awardmoney(int money)
{
    mymoney += money;
    update();
}
void MainWindow::decreaseMoney(int money)
{
    mymoney -=money;
    update();
    if(mymoney<0)
        doGameOver();
}

AudioPlayer *MainWindow::audioPlayer() const
{
    return _audioPlayer;
}

void MainWindow::addWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(785,50));
    _wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(785,480));
    _wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(582,480));
    _wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(582,165));
    _wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(373,165));
    _wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(373,480));
    _wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(160,480));
    _wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(160,50));
    _wayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);
}

void MainWindow::getHpDamage(int damage/* = 1*/)
{
    _audioPlayer->playSound(LifeLoseSound);
    myHp -= damage;
    if (myHp <= 0)
        doGameOver();
}

void MainWindow::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    _enemyList.removeOne(enemy);
    delete enemy;

    if (_enemyList.empty())
    {
        ++_waves;
        if (!loadWave())
        {
            _gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}
void MainWindow::removedTower(Tower *tower)
{
    Q_ASSERT(tower);
    _towersList.removeOne(tower);
    delete tower;
}

void MainWindow::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    _bulletList.removeOne(bullet);
    delete bullet;
}

void MainWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    _bulletList.push_back(bullet);
}

void MainWindow::updateMap()
{
    foreach (Enemy *enemy, _enemyList)
        enemy->move();
    foreach (Tower *tower, _towersList)
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
    _wavesInfo = reader.data();

    file.close();
}

bool MainWindow::loadWave()
{
    if (_waves >= _wavesInfo.size())
        return false;

    WayPoint *startWayPoint = _wayPointsList.back();
    QList<QVariant> curWavesInfo = _wavesInfo[_waves].toList();

    for (int i = 0; i < curWavesInfo.size(); ++i)
    {
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();
        int enemyType =dict.value("enemyType").toInt();

        switch(enemyType)
        {
        case 0:
        {
            Enemy *enemy = new Enemy(startWayPoint, this);
            _enemyList.push_back(enemy);
            QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
        }
            break;
        case 1:
        {
            EnemyPlus *enemy = new EnemyPlus(startWayPoint, this);
            _enemyList.push_back(enemy);
            QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
        }
            break;
        case 2:
        {
            EnemyHarmOnWay *enemy = new EnemyHarmOnWay(startWayPoint, this);
            _enemyList.push_back(enemy);
            QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
        }
            break;

        case 3:
        {
            EnemyDouble *enemy = new EnemyDouble(startWayPoint, this);
            _enemyList.push_back(enemy);
            QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
        }
            break;
        case 4:
        {
            HIV *enemy = new HIV(startWayPoint, this);
            _enemyList.push_back(enemy);
            QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
        }
            break;
        case 5:
        {
            HIVplus *enemy = new HIVplus(startWayPoint, this);
            _enemyList.push_back(enemy);
            QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
        }
            break;
        default:
            exit(-1);
        }
    }

    return true;
}

QList<Enemy *> MainWindow::enemyList() const
{
    return _enemyList;
}

void MainWindow::gameStart()
{
    loadWave();
}
