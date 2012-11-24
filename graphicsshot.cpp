#include "graphicsshot.h"
#include "graphicsagent.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QPainter>

GraphicsShot::GraphicsShot(QGraphicsScene *scene, GraphicsAgent *startItem, GraphicsAgent *endItem) :
    _scene(scene),
    _startItem(startItem),
    _endItem(endItem)
{
}

QRectF GraphicsShot::boundingRect() const
 {
    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()));
 }

QPainterPath GraphicsShot::shape() const
{
    return QGraphicsLineItem::shape();
}

void GraphicsShot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen newPen = pen();
    newPen.setWidth(2);
    newPen.setColor(_startItem->agent()->color());
    newPen.setStyle(Qt::DotLine);

    setLine(_startItem->x(), _startItem->y(),
            _endItem->x(), _endItem->y());

    painter->setPen(newPen);
    painter->drawLine(line());
}
