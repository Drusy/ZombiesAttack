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
};

#endif // HUMANBUILDERSTRATEGY_H
