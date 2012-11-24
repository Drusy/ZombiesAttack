#include "hunterzombiestrategy.h"

#include <cmath>
#include <QDebug>

HunterZombieStrategy* HunterZombieStrategy::_instance = 0;

HunterZombieStrategy::HunterZombieStrategy()
{
    _color = Qt::red;
}

HunterZombieStrategy::~HunterZombieStrategy()
{

}

HunterZombieStrategy* HunterZombieStrategy::instance()
{
    return _instance ? _instance : (_instance = new HunterZombieStrategy());
}

void HunterZombieStrategy::seeHumans(Agent *inAgent)
{
    _humansSeen.clear();

    foreach (Agent *agent, inAgent->getNeighbors())
    {
        if (agent != inAgent)
        {
            if (!agent->isZombie() && collidesWithItem(inAgent, agent, 60))
                _humansSeen.push_back(agent);
        }
    }
}

void HunterZombieStrategy::humanCollisions(Agent *agent)
{
    seeHumans(agent);
    _nearestHuman = nearestHuman(agent);

    if (!_humansSeen.empty())
        zombieShot(agent, _nearestHuman);
}

Agent* HunterZombieStrategy::nearestHuman(Agent *agent)
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

void HunterZombieStrategy::zombieShot(Agent *hunterZombie, Agent *human)
{
    if (hunterZombie->readyToShot() && !human->isAboutToBeContaminated())
    {
        emit humanShot(hunterZombie, human);
        human->contaminateByShot();
        hunterZombie->reload();
    }
}

void HunterZombieStrategy::execute(Agent *agent)
{
    humanCollisions(agent);

    if (_humansSeen.isEmpty())
    {
        randomMovement(agent);
    }
    else
    {
        // Run
        double angle = atan2(agent->y() - _nearestHuman->y(), agent->x() - _nearestHuman->x()) * 180 / M_PI;

        agent->setRotation(angle + 90);
        agent->setMovement(QPointF(0, 0.5));
    }
}
