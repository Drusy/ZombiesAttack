#include "agent.h"
#include "model.h"
#include "zombiestrategy.h"
#include "humanstrategy.h"
#include "zombiestrategy.h"
#include "hunterstrategy.h"

#include <QDebug>
#include <cmath>

unsigned Agent::Index = 0;

Agent::Agent(StrategyEnum strategy):
    _pos(QPoint(0, 0)),
    _rotation(0),
    _angle(0),
    _speed(0)
{
    _index = Index++;
    setStrategy(strategy);
    _strategy->addOne();

    _deathTimer.setSingleShot(true);
    connect(&_deathTimer, SIGNAL(timeout()), this, SLOT(onDeathTime()));

    _reload.setSingleShot(true);  
}

Agent::~Agent()
{
    _strategy->removeOne();
}

void Agent::setStrategy(StrategyEnum strategy)
{
    switch (strategy)
    {
    case human:
        _strategy = HumanStrategy::instance();
        break;
    case zombie:
        _strategy = ZombieStrategy::instance();
        break;
    case hunter:
        _strategy = HunterStrategy::instance();
        break;
    }
}

void Agent::onDeathTime()
{
    emit deadAgent(this);
}

bool Agent::isAlive()
{
    return !_deathTimer.isActive();
}

void Agent::kill()
{
    if (!_deathTimer.isActive())
        _deathTimer.start(800);
}

QRectF Agent::boundingRect() const
{
    return _strategy->boundingRect();
}

QPainterPath Agent::shape() const
{
    return _strategy->shape();
}

void Agent::setPos(int x, int y)
{
    _pos.setX(x);
    _pos.setY(y);
}

int Agent::x() const
{
    return _pos.x();
}

int Agent::y() const
{
    return _pos.y();
}

QColor Agent::color() const
{
    return _strategy->color();
}

void Agent::setRotation(qreal rotation)
{
    _rotation = rotation;
}

qreal Agent::rotation()
{
    return _rotation;
}

unsigned Agent::index()
{
    return _index;
}

QPointF Agent::pos() const
{
    return _pos;
}

void Agent::setPos(const QPointF &pos)
{
    _pos = pos;
}

void Agent::update()
{
    _strategy->execute(this);
}

QPointF Agent::getMovement() const
{
    return _notMapped;
}

void Agent::setMovement(const QPointF &movement)
{
    _notMapped = movement;
}

qreal Agent::addAngle(qreal value)
{
    _angle += value;

    return _angle;
}

qreal Agent::addSpeed(qreal value)
{
    _speed += value;

    return _speed;
}

void Agent::changeStrategy(Strategy *strategy)
{
    _strategy->removeOne();
    _strategy = strategy;
    _strategy->addOne();
}

void Agent::resetIndex()
{
    Index = 0;
}

bool Agent::isZombie()
{
    return (_strategy == ZombieStrategy::instance());
}

bool Agent::isHunter()
{
    return (_strategy == HunterStrategy::instance());
}

void Agent::reload()
{
    _reload.start(1000);
}

bool Agent::readyToShot()
{
    return !_reload.isActive();
}

double distanceBetween(Agent *a1, Agent *a2)
{
    return sqrt((a1->x() - a2->x()) * (a1->x() - a2->x()) +
                (a1->y() - a2->y()) * (a1->y() - a2->y()));
}

void Agent::setNeighborsIndex(unsigned neighborsIndex)
{
    _neighborsIndex = neighborsIndex;
}

unsigned Agent::getNeighborsIndex()
{
    return _neighborsIndex;
}

void Agent::setNeighbors(const QVector<Agent*> &neighbors)
{
    _neighbors = neighbors;
}

QVector<Agent*> Agent::getNeighbors() const
{
    return _neighbors;
}
