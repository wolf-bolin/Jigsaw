#include "clock.h"
#include <QPainter>
#include <QPoint>
#include <QTime>
#include <QTimer>

static QPoint sed[4] = {QPoint(0,-70),QPoint(2,0),
                       QPoint(0,10),QPoint(-2,0)};
static QPoint min[4] = {QPoint(0,-60),QPoint(4,0),
                       QPoint(0,12),QPoint(-4,0)};
static QPoint hour[4] = {QPoint(0,-50),QPoint(6,0),
                       QPoint(0,13),QPoint(-6,0)};
Clock::Clock(QWidget *parent)
    : QWidget(parent)
{
    QTimer * pTimer = new QTimer(this);
    pTimer->start(1000);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(update()));
    resize(200,200);

}

Clock::~Clock()
{

}

void Clock::paintEvent(QPaintEvent *)
{
    QTime time = QTime::currentTime();/* 获取当地当前时间 */
    QPainter paint(this); /* 定义一个绘图设备 */
    /* 窗口大小是(200,200),那么就将坐标系移动到屏幕中央(100,100)作为本地的中心(0,0) 
    (0,0)--------------------
        |         |          |
        |         |          |
        |         |          |
        |         |          |
        |         |(100,100)作为新的(0,0)
        |         |          |
        |         |          |
        |         |          |
        |         |          |
        ---------------------(200,200))
    */
    paint.translate(100, 100);
    //paint.drawLine(0, 0, 100, 100);
    /* 设置渲染效果是各向异性 */
    paint.setRenderHint(QPainter::Antialiasing);
    /* 设置画刷与画笔 */
    paint.setBrush(Qt::red);
    paint.setPen(Qt::red);
    paint.save();
    paint.rotate(6.0 * time.second());
    /* 绘制秒针对应的多边形 */
    paint.drawConvexPolygon(sed, 4);
    paint.restore();
    /* 设置画刷与画笔 */
    paint.setBrush(Qt::blue);
    paint.setPen(Qt::blue);
    paint.save();/* 保存之前的坐标系 */
    paint.rotate(6.0 * (time.minute() + time.second() /60.0));/* 6(360 / 60)度移动一个完整格子，剩下的慢慢移动 */
    /* 绘制分针对应的多边形 */
    paint.drawConvexPolygon(min, 4);
    paint.restore(); /* 恢复之前的坐标系 */
    /* 设置画刷与画笔 */
    paint.setBrush(Qt::black);
    paint.setPen(Qt::black);
    paint.save();
    paint.rotate(30.0 * (time.hour() + time.minute() / 60.0));/* 30(360 / 12)度移动一个完整格子，剩下的慢慢移动 */
    /* 绘制时针对应的多边形 */
    paint.drawConvexPolygon(hour, 4);
    paint.restore();
    /* 绘制表盘 */
    for (int i = 1; i <= 60; i++) {
        paint.rotate(6);/* 坐标轴旋6度 */
        if (i == 60) {
            paint.save();
            paint.setBrush(Qt::red);
            paint.setPen(Qt::red);
            paint.drawLine(0, -98, 0, -82); /* -98*cos(30).. */
            paint.restore();
        } else if (i == 30) {
            paint.save();
            paint.setBrush(Qt::red);
            paint.setPen(Qt::red);
            paint.drawLine(0, -98, 0, -83); /* -98*cos(30).. */
            paint.restore();
        } else if (i == 45 || i == 15) {
            paint.save();
            paint.setBrush(Qt::yellow);
            paint.setPen(Qt::yellow);
            paint.drawLine(0, -98, 0, -84); /* -98*cos(30).. */
            paint.restore();
        } else if (i %5 == 0) {
            paint.save();
            paint.setBrush(Qt::yellow);
            paint.setPen(Qt::yellow);
            paint.drawLine(0, -98, 0, -86); /* -98*cos(30).. */
            paint.restore();
        } else {
            paint.drawLine(0, -98, 0, -88); /* -98*cos(30).. */
        }

    }
    /* 绘制表盘主要数字12,6,9,3 */
    paint.save();
    paint.setBrush(Qt::blue);
    paint.setPen(Qt::blue);
    QFont* pFont = new QFont("华文彩云", -1, 75, false);
    paint.setFont(*pFont);
    paint.drawText(QRectF(-8, -80, 25, 15), "12");
    paint.drawText(QRectF(-4, 70, 25, 15), "6");
    paint.drawText(QRectF(-75, -5, 25, 15), "9");
    paint.drawText(QRectF(70, -5, 25, 15), "3");
    delete pFont;

    paint.restore();

}
