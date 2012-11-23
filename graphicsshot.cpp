#include "graphicsshot.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QPainter>

GraphicsShot::GraphicsShot(QGraphicsScene *scene, GraphicsAgent *startItem, GraphicsAgent *endItem) :
    _scene(scene),
    _startItem(startItem),
    _endItem(endItem)
{
    _shotTimer.setSingleShot(false);
    _shotTimer.start(600);

    connect(&_shotTimer, SIGNAL(timeout()), this, SLOT(onShotOver()));
}

QRectF GraphicsShot::boundingRect() const
 {
    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()));
 }

void GraphicsShot::onShotOver()
{
    emit shotOver(this, _endItem);
}

QPainterPath GraphicsShot::shape() const
{
    return QGraphicsLineItem::shape();
}

void GraphicsShot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen newPen = pen();
    newPen.setWidth(2);
    newPen.setColor(Qt::gray);
    newPen.setStyle(Qt::DotLine);

    setLine(_startItem->x(), _startItem->y(),
            _endItem->x(), _endItem->y());

    painter->setPen(newPen);
    painter->drawLine(line());
}
