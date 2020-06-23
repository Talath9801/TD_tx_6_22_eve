#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include "tower.h"

class QPainter;

class TowerPosition
{
public:
	TowerPosition(QPoint pos, const QPixmap &sprite = QPixmap(":/image/open_spot.png"));

    void setHasTower(Tower* tower_put_in, bool hasTower = true);
    void setNotHasTower(){m_hasTower=false;}
	bool hasTower() const;
	const QPoint centerPos() const;
	bool containPoint(const QPoint &pos) const;
    Tower *     the_tower_in=NULL;

	void draw(QPainter *painter) const;

private:
	bool		m_hasTower;
	QPoint		m_pos;
	QPixmap		m_sprite;
    //Tower *     the_tower_in;

	static const QSize ms_fixedSize;
};

#endif // TOWERPOSITION_H
