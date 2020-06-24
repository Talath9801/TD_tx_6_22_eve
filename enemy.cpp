#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include "utility.h"
#include "mainwindow.h"
#include "audioplayer.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

static const int Health_Bar_Width = 20;

const QSize Enemy::ms_fixedSize(80,80);

Enemy::Enemy(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite/* = QPixmap(":/image/enemy.png")*/)
	: QObject(0)
	, m_active(false)
	, m_maxHp(40)
	, m_currentHp(40)
    , m_walkingSpeed(2.5)
	, m_pos(startWayPoint->pos())
	, m_destinationWayPoint(startWayPoint->nextWayPoint())
    , mainw(game)
	, m_sprite(sprite)
{
}

Enemy::~Enemy()
{
	m_attackedTowersList.clear();
	m_destinationWayPoint = NULL;
    mainw = NULL;
}

void Enemy::doActivate()
{
	m_active = true;
}

void Enemy::move()
{
	if (!m_active)
		return;

	if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
	{
        if (m_destinationWayPoint->nextWayPoint())
		{
            m_pos = m_destinationWayPoint->pos();
			m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
		}
		else
		{
            mainw->getHpDamage();
            mainw->removedEnemy(this);
			return;
		}
	}
     QPoint targetPoint = m_destinationWayPoint->pos();
	qreal movementSpeed = m_walkingSpeed;
	QVector2D normalized(targetPoint - m_pos);
	normalized.normalize();
	m_pos = m_pos + normalized.toPoint() * movementSpeed;

}

void Enemy::draw(QPainter *painter) const
{
	if (!m_active)
		return;

    painter->save();
	static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);

    painter->drawPixmap(offsetPoint.x(),offsetPoint.y(),80,80, m_sprite);//enemy
    painter->setBrush(QColor("#99ffffff"));
    painter->setPen(Qt::NoPen);
    painter->drawRect(offsetPoint.x(),offsetPoint.y(),60,20);//text background
    painter->setPen(QPen(Qt::black));
    painter->drawText(QRect(offsetPoint.x(),offsetPoint.y(),60,20),QString("hp:%1").arg(m_currentHp));
    //

	painter->restore();
}

void Enemy::getRemoved()
{
	if (m_attackedTowersList.empty())
		return;

	foreach (Tower *attacker, m_attackedTowersList)
        attacker->killcurrentE();
    mainw->removedEnemy(this);
}

void Enemy::getDamage(int damage)
{
    //m_game->audioPlayer()->playSound(LaserShootSound);
	m_currentHp -= damage;
    if (m_currentHp <= 0)
	{

        //m_game->audioPlayer()->playSound(EnemyDestorySound);
        mainw->awardmoney(200);
        getRemoved();
	}
}

void Enemy::getAttacked(Tower *attacker)
{
	m_attackedTowersList.push_back(attacker);
}


void Enemy::gotLostSight(Tower *attacker)
{
	m_attackedTowersList.removeOne(attacker);
}

QPoint Enemy::pos() const
{
	return m_pos;
}
