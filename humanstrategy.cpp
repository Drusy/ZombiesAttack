#include "humanstrategy.h"

#include <QStyleOption>
#include <QDebug>
#include <cmath>

HumanStrategy* HumanStrategy::_instance = 0;

HumanStrategy::HumanStrategy()
{
    _color = Qt::blue;
}

HumanStrategy::~HumanStrategy()
{
}

HumanStrategy* HumanStrategy::instance()
{
    return _instance ? _instance : (_instance = new HumanStrategy());
}

QRectF HumanStrategy::boundingRect() const
 {
     return QRectF(QPoint(-5, -5), QPoint(5, 5));
 }

QPainterPath HumanStrategy::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(QPoint(-5, -5), QPoint(5, 5)));
    return path;
}

QVector<Agent*> HumanStrategy::seeZombies(Agent *inAgent)
{
    QVector<Agent*> zombies;
    foreach (Agent *agent, inAgent->getNeighbors())
    {
        if (agent != inAgent && agent->isZombie() && collidesWithItem(inAgent, agent))
            zombies.push_back(agent);
    }

    return zombies;
}

bool HumanStrategy::collidesWithItem(Agent *agent, const Agent *other)
{
    double a = 25 * 2;
    double dx = agent->x() - other->x();
    double dy = agent->y() - other->y();
    return ((a * a) > (dx * dx + dy * dy));
}

bool HumanStrategy::zombiesCollisions(Agent *agent)
{
    QVector<Agent*> zombiesSeen = seeZombies(agent);

    return (!zombiesSeen.empty());
}

QColor HumanStrategy::color() const
{
    return _color;
}

void HumanStrategy::execute(Agent *agent)
{
    contactHuman(agent);
    // Random
    qreal speed = agent->addSpeed((-50 + qrand() % 100) / 100.0);
    qreal angle = agent->addAngle((qrand() % 100) / 500.0);
    qreal dx = ::sin(angle) * 10;

    agent->setRotation(agent->rotation() + dx);
    agent->setMovement(QPointF(0, -(0 + sin(speed) * 1)));

}

void HumanStrategy::contactHuman(Agent *agent)
{
    QVector<Agent*> humans = collidingHumans(agent);

    foreach (Agent *human, humans)
    {
        if(human->isHuman())
        {
            agent->addCollision();
        }

    }
}

QVector<Agent*> HumanStrategy::collidingHumans(Agent *inAgent)
{
    QVector<Agent*> humans;

    foreach (Agent *agent, inAgent->getNeighbors())
    {
        if (agent != inAgent && agent->isHuman())
        {
            if(collidesWithItem(inAgent, agent))
                humans.push_back(agent);
        }
    }

    return humans;
}
