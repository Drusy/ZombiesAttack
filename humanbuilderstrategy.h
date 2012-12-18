#ifndef HUMANBUILDERSTRATEGY_H
#define HUMANBUILDERSTRATEGY_H

#include "humanstrategy.h"

class HumanBuilderStrategy : public HumanStrategy
{
protected:
    HumanBuilderStrategy();
    static HumanBuilderStrategy* _instance;
public:
    static HumanBuilderStrategy* instance();
    void contactBlock(Agent *agent);
    Agent* collidingBlock(Agent *inAgent);
    void execute(Agent *agent);
    void buildBlock(Agent *agent);
};

#endif // HUMANBUILDERSTRATEGY_H
