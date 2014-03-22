#include "humanbuilderstrategy.h"

#include <QStyleOption>
#include <cmath>

#include "../controller.h"


HumanBuilderStrategy* HumanBuilderStrategy::_instance = 0;

HumanBuilderStrategy::HumanBuilderStrategy()
{
    _color = Qt::darkYellow;
}

HumanBuilderStrategy* HumanBuilderStrategy::instance()
{
    return _instance ? _instance : (_instance = new HumanBuilderStrategy());
}

void HumanBuilderStrategy::contactBlock(Agent *agent)
{
    Agent* block = collidingBlock(agent);

    if(block != NULL)
    {
        agent->setRotation(agent->rotation() + 90);
        buildBlock(agent);
    }
}

Agent* HumanBuilderStrategy::collidingBlock(Agent *inAgent)
{
    foreach (Agent *agent, inAgent->getNeighbors())
    {
        if (agent != inAgent && agent->isBlock())
        {
            if(collidesWithItem(inAgent, agent, 8))
                return agent;
        }
    }

    return NULL;
}

void HumanBuilderStrategy::execute(Agent *agent)
{
    contactBlock(agent);
    // Random
    qreal speed = agent->addSpeed((-50 + qrand() % 100) / 100.0);
    qreal angle = agent->addAngle((qrand() % 100) / 500.0);
    qreal dx = ::sin(angle) * 10;

    agent->setRotation(agent->rotation() + dx);
    agent->setMovement(QPointF(0, -(0 + sin(speed) * 1)));

    // 1 chance sur 1000
    if(qrand() % 1000 == 42)
    {
        buildBlock(agent);
    }

}

void HumanBuilderStrategy::buildBlock(Agent *agent)
{
    agent->createAgent(1, block, agent->getPosition().x(), agent->getPosition().y());
    agent->changeStrategy(HumanStrategy::instance());
    agent->resetCollision();
}

QString HumanBuilderStrategy::toString()
{
    return "HumanBuilderStrategy";
}
