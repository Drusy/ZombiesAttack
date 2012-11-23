#include "model.h"

QRect Model::_border = QRect(0, 0, 0, 0);

Model::Model()
{
}

Model::~Model()
{
    clear();
}

void Model::clear()
{
    foreach(Agent *agent, _agents)
    {
        delete agent;
    }
    _agents.clear();
}

void Model::removeAgent(Agent *agent)
{
    _agents.removeOne(agent);
    delete agent;
    agent = 0;
}

void Model::addAgent(Agent *agent)
{
    _agents.push_back(agent);
}

QList<Agent*> Model::getAgents() const
{
    return _agents;
}

void Model::setRect(QRect &rect)
{
    _border = rect;
}

QRect Model::getRect()
{
    return _border;
}
