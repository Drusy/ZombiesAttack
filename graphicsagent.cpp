#include "graphicsagent.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QPainter>

GraphicsAgent::GraphicsAgent(QGraphicsScene *scene, Agent *agent)
    : _scene(scene), _agent(agent)
{
}

QRectF GraphicsAgent::boundingRect() const
 {
     return _agent->boundingRect();
 }

QPainterPath GraphicsAgent::shape() const
{
    return _agent->shape();
}

void GraphicsAgent::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPointF mapped = mapToParent(_agent->getMovement());
    QPointF pos;

    pos.setX(qMin(qMax(mapped.x(), scene()->sceneRect().left() + 10.0), scene()->sceneRect().right() - 10.0));
    pos.setY(qMin(qMax(mapped.y(), scene()->sceneRect().top() + 10.0), scene()->sceneRect().bottom() - 10.0));

    setPos(pos);
    _agent->setPos(pos);

    setRotation(_agent->rotation());

    painter->setBrush(_agent->color());
    painter->drawPath(_agent->shape());
}

Agent* GraphicsAgent::agent()
{
    return _agent;
}
