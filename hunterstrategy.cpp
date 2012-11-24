#include "hunterstrategy.h"

#include <QStyleOption>
#include <QDebug>
#include <cmath>

HunterStrategy* HunterStrategy::_instance = 0;

HunterStrategy::HunterStrategy()
{
    _color = Qt::darkGray;
}

HunterStrategy::~HunterStrategy()
{
}

HunterStrategy* HunterStrategy::instance()
{
    return _instance ? _instance : (_instance = new HunterStrategy());
}

QRectF HunterStrategy::boundingRect() const
 {
     return QRectF(QPoint(-5, -5), QPoint(5, 5));
 }

QPainterPath HunterStrategy::shape() const
{
    QPainterPath path;
    path.addEllipse(QPointF(0, 0), 5, 7);
    return path;
}

void HunterStrategy::seeZombies(Agent *inAgent)
{
    _zombies.clear();
    _huntersFar.clear();
    _huntersNear.clear();

    foreach (Agent *agent, inAgent->getNeighbors())
    {
        if (agent != inAgent)
        {
            if (agent->isZombie() && collidesWithItem(inAgent, agent, 80))
                _zombies.push_back(agent);
            else
                if (agent->isHunter())
                {
                    if (!collidesWithItem(inAgent, agent, 50))
                        _huntersFar.push_back(agent);
                    else
                        _huntersNear.push_back(agent);
                }
        }
    }
}

bool HunterStrategy::collidesWithItem(const Agent *agent, const Agent *other, unsigned range) const
{
    double a = range;
    double dx = agent->x() - other->x();
    double dy = agent->y() - other->y();
    return ((a * a) > (dx * dx + dy * dy));
}

void HunterStrategy::zombiesCollisions(Agent *agent)
{
    seeZombies(agent);
    _nearestZombie = nearestZombie(agent);

    if (!_zombies.empty())
        shot(agent, _nearestZombie /*_zombies.at(qrand() % _zombies.size())*/);
}

QColor HunterStrategy::color() const
{
    return _color;
}

void HunterStrategy::shot(Agent *hunter, Agent *zombie)
{
    if (hunter->readyToShot() && zombie->isAlive())
    {
        emit zombieShot(hunter, zombie);
        zombie->kill();
        hunter->reload();
    }
}

Agent* HunterStrategy::nearestZombie(Agent *agent)
{
    Agent *toFollow = 0;
    double distance = INT_MAX, tmp;
    foreach (Agent *zombie, _zombies)
    {
        tmp = distanceBetween(agent, zombie);
        if (tmp < distance)
        {
            distance = tmp;
            toFollow = zombie;
        }
    }

    return toFollow;
}

Agent* HunterStrategy::nearestFarhunter(Agent *agent)
{
    Agent *toFollow = 0;
    double distance = INT_MAX, tmp;
    foreach (Agent *hunter, _huntersFar)
    {
        tmp = distanceBetween(agent, hunter);
        if (tmp < distance)
        {
            distance = tmp;
            toFollow = hunter;
        }
    }

    return toFollow;
}

void HunterStrategy::randomMovement(Agent *agent)
{
    qreal speed = agent->addSpeed((-50 + qrand() % 100) / 100.0);
    qreal angle = agent->addAngle((qrand() % 100) / 500.0);
    qreal dx = ::sin(angle) * 10;

    agent->setRotation(agent->rotation() + dx);
    agent->setMovement(QPointF(0, -(0 + sin(speed) * 1)));
}

void HunterStrategy::execute(Agent *agent)
{
    zombiesCollisions(agent);

    if (_zombies.isEmpty())
    {
        if (!_huntersNear.isEmpty())
        {
            randomMovement(agent);
        }
        else
        {
            Agent *toFollow = nearestFarhunter(agent);

            if(sqrt((toFollow->pos().x() - agent->pos().x()) * (toFollow->pos().x() - agent->pos().x())
                    + (toFollow->pos().y() - agent->pos().y())*(toFollow->pos().y() - agent->pos().y())) < 200)
            {
                double angle = atan2(agent->y() - toFollow->y(), agent->x() - toFollow->x()) * 180 / M_PI;

                agent->setRotation(angle + 90);
                agent->setMovement(QPointF(0, 1));
            }
            else
                randomMovement(agent);
        }
    }
    else
    {
        // Run
        double angle = atan2(agent->y() - _nearestZombie->y(), agent->x() - _nearestZombie->x()) * 180 / M_PI;

        agent->setRotation(angle + 90);
        agent->setMovement(QPointF(0, -0.5));
    }
}
