#include "zombiestrategy.h"

#include <QStyleOption>
#include <QDebug>
#include <cmath>

ZombieStrategy* ZombieStrategy::_instance = 0;

ZombieStrategy::ZombieStrategy()
{
    _color = Qt::darkRed;
}

ZombieStrategy::~ZombieStrategy()
{
}

ZombieStrategy* ZombieStrategy::instance()
{
    return _instance ? _instance : (_instance = new ZombieStrategy());
}

QRectF ZombieStrategy::boundingRect() const
 {
     return QRectF(QPoint(-5, -5), QPoint(5, 5));
 }

QPainterPath ZombieStrategy::shape() const
{
    QPainterPath path;
    path.addEllipse(QPoint(0, 0), 5, 5);
    return path;
}

QColor ZombieStrategy::color() const
{
    return _color;
}

QVector<Agent*> ZombieStrategy::collidingHumans(Agent *inAgent)
{
    QVector<Agent*> humans;
    _humansSeen.clear();

    foreach (Agent *agent, inAgent->getNeighbors())
    {
        if (agent != inAgent && !agent->isZombie())
        {
            if(collidesWithItem(inAgent, agent))
                humans.push_back(agent);
            else
                _humansSeen.push_back(agent);
        }
    }

    return humans;
}

bool ZombieStrategy::collidesWithItem(const Agent *agent, const Agent *other) const
{
    double a = 8 * 2;

    double dx = agent->x() - other->x();
    double dy = agent->y() - other->y();
    return ((a * a) > (dx * dx + dy * dy));
}

void ZombieStrategy::contaminates(Agent *agent)
{
    QVector<Agent*> humans = collidingHumans(agent);

    foreach (Agent *human, humans)
    {
        human->changeStrategy(this);
    }
}

Agent* ZombieStrategy::nearestHuman(Agent *agent)
{
    Agent *toFollow = 0;
    double distance = INT_MAX, tmp;
    foreach (Agent *human, _humansSeen)
    {
        tmp = distanceBetween(agent, human);
        if (tmp < distance)
        {
            distance = tmp;
            toFollow = human;
        }
    }

    return toFollow;
}

void ZombieStrategy::randomMovement(Agent *agent)
{
    qreal speed = agent->addSpeed((-50 + qrand() % 100) / 100.0);
    qreal angle = agent->addAngle((qrand() % 100) / 500.0);
    qreal dx = ::sin(angle) * 10;

    agent->setRotation(agent->rotation() + dx);
    agent->setMovement(QPointF(0, -(0 + sin(speed) * 1)));
}

void ZombieStrategy::execute(Agent *agent)
{
    contaminates(agent);

    qreal speed = agent->addSpeed((-50 + qrand() % 100) / 100.0);
    if (_humansSeen.isEmpty())
    {
        randomMovement(agent);
    }
    else
    {
        // Follow
        Agent *toFollow = nearestHuman(agent);
        if(sqrt((toFollow->pos().x() - agent->pos().x())*(toFollow->pos().x() - agent->pos().x())
                + (toFollow->pos().y() - agent->pos().y())*(toFollow->pos().y() - agent->pos().y())) < 75)
        {
            double angle = atan2(agent->y() - toFollow->y(), agent->x() - toFollow->x()) * 180 / M_PI;

            agent->setRotation(angle + 90);
            // Choose zombies stupid
//            agent->setMovement(QPointF(0, sin(speed) * sin(speed) + 0.2));
            // or choose zombies warrior
            agent->setMovement(QPointF(0, 1));
        }
        else
            randomMovement(agent);
    }
}
