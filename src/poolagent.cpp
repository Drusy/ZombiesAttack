#include "poolagent.h"
#include "humanstrategy.h"

PoolAgent* PoolAgent::_instance = NULL;

PoolAgent::PoolAgent(int nombre)
{
    for(int i = 0 ; i < nombre ; ++i)
    {
        _listAgent.append(new Agent());
    }
}

void PoolAgent::deleteAgent(Agent *a)
{
    a->changeStrategy(HumanStrategy::instance());
    _listAgent.append(a);
}

Agent* PoolAgent::newAgent(StrategyEnum str)
{
    Agent* a;

    if(_listAgent.isEmpty())
    {
        a = new Agent();
    }
    else
    {
       a = _listAgent.takeLast();
    }

    a->init(str);
    return a;
}

PoolAgent* PoolAgent::instance(int nombre)
{
    if(_instance == NULL)
    {
        _instance = new PoolAgent(nombre);
    }

    return _instance;
}

PoolAgent::~PoolAgent()
{
    foreach(Agent * a , _listAgent)
    {
        delete(a);
    }
}
