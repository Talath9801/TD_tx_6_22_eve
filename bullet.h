#ifndef BULLET_H
#define BULLET_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class MainWindow;

class Bullet : QObject
{
	Q_OBJECT
    Q_PROPERTY(QPoint bullet_position READ cu_position WRITE setposition)

public:
    Bullet(QPoint ori_posi, QPoint enemy_posi, int _damage, Enemy *the_e,
           MainWindow *mw, const QPixmap &_pict = QPixmap(":/image/bullet.png"));

	void draw(QPainter *painter) const;
	void move();
    void setposition(QPoint pos);
    QPoint cu_position() const;

protected slots:
    virtual void get_to_enemy();

protected:
    const QPoint	originPosition;
    const QPoint	enemyPosition;
    const QPixmap	bullet_picture;
    QPoint			bullet_position;
    Enemy *			the_enemy;
    MainWindow *	mainw;
    int				perdam;

    static const QSize sizeofBullet;
};

#endif // BULLET_H
