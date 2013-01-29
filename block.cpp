#include "block.h"
#include <QStyleOption>

BlockStrategy* BlockStrategy::_instance = 0;

BlockStrategy::BlockStrategy()
{
    _color = Qt::darkMagenta;
}

BlockStrategy* BlockStrategy::instance()
{
    return _instance ? _instance : (_instance = new BlockStrategy());
}


QRectF BlockStrategy::boundingRect() const
 {
     return QRectF(QPoint(-5, -5), QPoint(5, 5));
 }

QPainterPath BlockStrategy::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(QPoint(-5, -5), QPoint(5, 5)));
    return path;
}

void BlockStrategy::execute(Agent *)
{

}

QColor BlockStrategy::color() const
{
    return _color;
}

QString BlockStrategy::toString()
{
    return "BlockStrategy";
}
