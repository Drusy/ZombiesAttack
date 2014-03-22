#ifndef POOLAGENT_H
#define POOLAGENT_H

#include <QList>

#include "agent.h"

class PoolAgent
{
private:
    QList<Agent*> _listAgent;
    static PoolAgent* _instance;
    PoolAgent(int nombre);

public:
    /**
       * Static constructor for unique instance
       */
    static PoolAgent* instance(int nombre = 100);
    void deleteAgent(Agent* a);
    Agent *newAgent(StrategyEnum str);
    ~PoolAgent();
};

#endif // POOLAGENT_H
