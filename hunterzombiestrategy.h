#ifndef HUNTERZOMBIESTRATEGY_H
#define HUNTERZOMBIESTRATEGY_H

#include "hunterstrategy.h"


class HunterZombieStrategy : public HunterStrategy
{
public:
    ~HunterZombieStrategy();
protected:
    HunterZombieStrategy();

    /// Instance of the singleton
    static HunterZombieStrategy *_instance;
};

#endif // HUNTERZOMBIESTRATEGY_H
