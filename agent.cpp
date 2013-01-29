#include "agent.h"
#include "model.h"
#include "zombiestrategy.h"
#include "humanstrategy.h"
#include "zombiestrategy.h"
#include "hunterstrategy.h"
#include "hunterzombiestrategy.h"
#include "humanbuilderstrategy.h"
#include "block.h"

#include <QDebug>
#include <cmath>

unsigned Agent::Index = 0;

Agent::Agent(StrategyEnum strategy):
    _pos(QPoint(0, 0)),
    _rotation(0),
    _angle(0),
    _speed(0),
    _collision(0)
{
    _index = Index++;
    setStrategy(strategy);
    _strategy->addOne();

    _deathTimer.setSingleShot(true);
    connect(&_deathTimer, SIGNAL(timeout()), this, SLOT(onDeathTime()));

    _contaminationTimer.setSingleShot(true);
    connect(&_contaminationTimer, SIGNAL(timeout()), this, SLOT(onContaminationTime()));

    _reload.setSingleShot(true);

    _buildTimer.setSingleShot(true);
    connect(&_buildTimer, SIGNAL(timeout()), this, SLOT(onBuildTime()));

    _eclosionTimer.setSingleShot(true);
    connect(&_eclosionTimer, SIGNAL(timeout()), this, SLOT(onEclosionTime()));

    if(strategy == block)
    {
        _pv = PV_BLOCK;
        _eclosionTimer.start(TIME_BEFORE_ECLOSION);
    }
    else
        _pv = 1;
}

Agent::~Agent()
{
    _strategy->removeOne();
    _deathTimer.stop();
    _contaminationTimer.stop();
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
    case hunterZombie:
        _strategy = HunterZombieStrategy::instance();
        break;
    case humanBuilder:
        _strategy = HumanBuilderStrategy::instance();
        break;
    case block:
        _strategy = BlockStrategy::instance();
        break;
    }
}

void Agent::onDeathTime()
{
    emit deadAgent(this);
}

void Agent::onContaminationTime()
{
    //    qDebug() << "contaminé";
    emit agentContaminated(this);
    contamination();
}

void Agent::contamination()
{
    //    qDebug() << _strategy->toString();
    if (_strategy == HunterStrategy::instance())
        changeStrategy(HunterZombieStrategy::instance());
    if (_strategy == HumanStrategy::instance() || _strategy == HumanBuilderStrategy::instance())
        changeStrategy(ZombieStrategy::instance());
    if(_strategy == BlockStrategy::instance())
    {
        //        qDebug()<< "pv = " << _pv;
        if(--_pv <= 0)
        {
            changeStrategy(ZombieStrategy::instance());
        }
    }
}

bool Agent::isAlive()
{
    return !_deathTimer.isActive();
}

bool Agent::isAboutToBeContaminated()
{
    return _contaminationTimer.isActive();
}

void Agent::kill()
{
    if (!_deathTimer.isActive())
        _deathTimer.start(500);
}

void Agent::contaminateByShot()
{
    if (!_contaminationTimer.isActive())
        _contaminationTimer.start(500);
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

bool Agent::isZombie() const
{
    return (_strategy == ZombieStrategy::instance()
            || _strategy == HunterZombieStrategy::instance());
}

bool Agent::isHunter() const
{
    return (_strategy == HunterStrategy::instance());
}

bool Agent::isHuman() const
{
    return (_strategy == HumanStrategy::instance() || _strategy == HumanBuilderStrategy::instance());
}

void Agent::reload()
{
    _reload.start(600);
}

bool Agent::readyToShot()
{
    return !_reload.isActive();
}

double distanceBetween(Agent *a1, Agent *a2)
{
    /*DEBUG_MSVC*/
//    return sqrt((double)((a1->x() - a2->x()) * (a1->x() - a2->x())) +
//                (double)((a1->y() - a2->y()) * (a1->y() - a2->y())));
    return sqrt(((a1->x() - a2->x()) * (a1->x() - a2->x())) +
                ((a1->y() - a2->y()) * (a1->y() - a2->y())));
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

void Agent::addCollision()
{
    ++_collision;

    if(_collision == NB_COLLISION_BUILDER)
        _buildTimer.start(TIME_TO_BUILD);
}

void Agent::resetCollision()
{
    _collision = 0;
}

bool Agent::isBuilder()
{
    return (_collision >= NB_COLLISION_BUILDER);
}

void Agent::onBuildTime()
{
    changeStrategy(HumanBuilderStrategy::instance());
}

bool Agent::isBlock()
{
    return (_strategy == BlockStrategy::instance());
}

QPointF Agent::getPosition()
{
    return _pos;
}

void Agent::onEclosionTime()
{
    emit createAgentSig(CHILDREN_PER_ECLOSION - 1, human, getPosition().x(), getPosition().y());

    changeStrategy(HunterStrategy::instance());
}

void Agent::createAgent(unsigned number, StrategyEnum strategy, int x , int y )
{
    emit createAgentSig(number, strategy, x, y);
}

