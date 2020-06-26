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
#include "towertunshi.h"
#include "tunshiplus.h"
#include "blymcell.h"
#include "blymcellplus.h"
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

    draw_Enemy_Wave(&cachePainter);
    draw_player_HP(&cachePainter);
    draw_Player_money(&cachePainter);

    QPainter painter(this);
    painter.drawPixmap(0, 0, cachePix);
    //  画出棕色背景底图
    /*painter.setBrush(QColor("#cd853f"));
    painter.setPen(Qt::NoPen);
    painter.drawRect(955,0,277,640);


    painter.setBrush(QColor("#deb887"));
    painter.drawRect(rec0);
    painter.drawRect(rec1);//第一栏
    painter.drawRect(rec2);//第二栏
    painter.drawRect(rec3);
    painter.drawRect(rec5);


    painter.setBrush(QColor("#22f5f5f5"));
    painter.drawRect(rec4);
    painter.drawRect(rec6);

    //                                                         画细胞的图片和文字信息
    QPixmap m_cell(":/image/tlymcell.png");//
    painter.drawPixmap(970,100,80,80,m_cell);
    painter.setPen(Qt::black);
    painter.drawText(QRect(1050,100,170,80),QString("相比默认塔，攻击范围缩小但攻击频率和强度增大"));

    m_cell.load(":/image/towerrangeall.png");
    painter.drawPixmap(970,190,80,80,m_cell);
    painter.setPen(Qt::black);
    painter.drawText(QRect(1050,190,170,80),QString("对HIV及其变种有防御功能，攻击HIV的时候自己不会死"));

    m_cell.load(":/image/tower.png");
    painter.drawPixmap(970,10,80,80,m_cell);
    painter.setPen(Qt::black);
    painter.drawText(QRect(1050,10,170,80),QString("默认类型塔，无需点击本栏，可以直接在地图的方框处点击建塔"));

    m_cell.load(":/image/phagocyte.png");
    painter.drawPixmap(970,280,80,80,m_cell);
    painter.setPen(Qt::black);
    painter.drawText(QRect(1050,280,170,80),QString("吞噬细胞,吞噬进入范围的病毒，吞噬2个之后自动死亡，攻击HIV时不被其杀死"));

    m_cell.load(":/image/phagocyteplus.png");
    painter.drawPixmap(970,370,80,80,m_cell);
    painter.setPen(Qt::black);
    painter.drawText(QRect(1050,370,170,80),QString("吞噬细胞升级版，不能直接点击此栏建塔，在已有吞噬细胞上点击即可升级"));

    m_cell.load(":/image/blymcell.png");
    painter.drawPixmap(970,460,80,80,m_cell);
    painter.setPen(Qt::black);
    painter.drawText(QRect(1050,460,170,80),QString("B淋巴细胞，分泌抗体，可减慢病毒的速度,减慢到一定值不再减慢"));

    m_cell.load(":/image/blymcellplus.png");
    painter.drawPixmap(970,550,80,80,m_cell);
    painter.setPen(Qt::black);
    painter.drawText(QRect(1050,550,170,80),QString("B淋巴细胞升级，不能直接点击此栏建塔，在已有B淋巴细胞上点击即可升级"));

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

    m_cell.load(":/image/enemy.png");
    painter.drawPixmap(10,650,80,80,m_cell);
    painter.setPen(Qt::black);
    painter.drawText(QRect(95,650,100,130),QString("普通病毒"));

    m_cell.load(":/image/enemyplus.png");
    painter.drawPixmap(215,650,80,80,m_cell);
    painter.setPen(Qt::black);
    painter.drawText(QRect(300,650,100,130),QString("普通病毒升级版，跑得更快，血更厚"));

    m_cell.load(":/image/enemyharmonway.png");
    painter.drawPixmap(420,650,80,80,m_cell);
    painter.setPen(Qt::black);
    painter.drawText(QRect(505,650,100,130),QString("未被杀死时，每秒钟减少玩家经济20点，易导致玩家经济死亡"));

    m_cell.load(":/image/enemydouble.png");
    painter.drawPixmap(625,650,80,80,m_cell);
    painter.setPen(Qt::black);
    painter.drawText(QRect(710,650,100,130),QString("只要未被杀死，每10秒钟病毒血量翻倍"));

    m_cell.load(":/image/hiv.png");
    painter.drawPixmap(830,650,80,80,m_cell);
    painter.setPen(Qt::black);
    painter.drawText(QRect(915,650,100,130),QString("HIV病毒，可以杀死对其发动攻击的第一个细胞，特殊细胞除外"));

    m_cell.load(":/image/hivplus.png");
    painter.drawPixmap(1035,650,80,80,m_cell);
    painter.setPen(Qt::black);
    painter.drawText(QRect(1120,650,100,130),QString("HIV病毒升级版，可以杀死对其发动攻击的前三个细胞，特殊细胞除外"));*/


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
        else if(canBuyTower() && it->containPoint(pressPoint) && !it->hasTower()&&event->button()==Qt::LeftButton&&remember_tower_kind==3)
            //                         吞噬细胞
        {
            Tower *tower=new TowerTunshi(it->centerPos(),this);
            it->setHasTower(tower);
            _towersList.push_back(tower);
            mymoney-=tower->get_tower_cost();
            update();
            remember_tower_kind=0;
            break;
        }
        //吞噬细胞升级：先拆后建
        else if(canBuyTower() && it->containPoint(pressPoint) && it->hasTower()&&event->button()==Qt::LeftButton&&it->the_tower_in->get_tower_type_num()==3)
            //                         它是吞噬细胞
        {
            removedTower(it->the_tower_in);
            it->the_tower_in=NULL;
            it->setNotHasTower();
            //m_playrGold-=TowerCost;
            Tower *tower=new TunshiPlus(it->centerPos(),this);
            it->setHasTower(tower);
            _towersList.push_back(tower);
            mymoney-=tower->get_tower_cost();
            update();
            remember_tower_kind=0;
            break;
        }
        else if(canBuyTower() && it->containPoint(pressPoint) && !it->hasTower()&&event->button()==Qt::LeftButton&&remember_tower_kind==5)
            //B淋巴细胞
        {
            //m_playrGold-=TowerCost;
            Tower *tower=new BLymCell(it->centerPos(),this);
            it->setHasTower(tower);
            _towersList.push_back(tower);
            mymoney-=tower->get_tower_cost();
            update();
            remember_tower_kind=0;
            break;
        }

        else if(canBuyTower() && it->containPoint(pressPoint) && it->hasTower()&&event->button()==Qt::LeftButton&&it->the_tower_in->get_tower_type_num()==5)
            //                         它是B细胞
        {
            removedTower(it->the_tower_in);
            it->the_tower_in=NULL;
            it->setNotHasTower();
            //m_playrGold-=TowerCost;
            Tower *tower=new BLymCellPlus(it->centerPos(),this);
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
    else if(point_in_rect(rec3,pressPoint))
    {
        remember_tower_kind=3;
    }
    else if(point_in_rect(rec5,pressPoint))
    {
        remember_tower_kind=5;
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

void MainWindow::draw_Enemy_Wave(QPainter *painter)
{
    painter->setPen(QPen(QColor("#a0522d")));
    painter->drawText(QRect(570, 5, 200, 40), QString("敌人波数 : %1/20").arg(_waves + 1));
}

void MainWindow::draw_player_HP(QPainter *painter)
{
    painter->setPen(QPen(QColor("#a0522d")));
    painter->drawText(QRect(230, 5, 200,40), QString("玩家血量 : %1").arg(myHp));
}

void MainWindow::draw_Player_money(QPainter *painter)
{
    painter->setPen(QPen(QColor("#a0522d")));
    painter->drawText(QRect(390, 5, 200, 40), QString("玩家经济 : %1").arg(mymoney));
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
        if (!load_Enemy_Wave())
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

bool MainWindow::load_Enemy_Wave()
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
    load_Enemy_Wave();
}
