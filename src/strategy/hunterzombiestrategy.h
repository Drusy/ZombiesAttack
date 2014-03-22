#ifndef HUNTERZOMBIESTRATEGY_H
#define HUNTERZOMBIESTRATEGY_H

#include "hunterstrategy.h"


class HunterZombieStrategy : public HunterStrategy
{
    Q_OBJECT
public:
    ~HunterZombieStrategy();

    /**
      * Static constructor for unique instance
      */
     static HunterZombieStrategy* instance();

     /**
       * Execute the strategy of the agent (movements, collisions...)
       *
       * @param agent Agent executing the strategy
       */
     void execute(Agent *agent);
     void seeHumans(Agent *inAgent);
     void humanCollisions(Agent *agent);
     void zombieShot(Agent *hunterZombie, Agent *human);
     Agent* nearestHuman(Agent *agent);
     /**
       * @return The name of the strategy
       */
     virtual QString toString();


signals:
     void humanShot(Agent *hunterZombie, Agent *human);

protected:
    HunterZombieStrategy();

    /// Instance of the singleton
    static HunterZombieStrategy *_instance;

    /// Humans seen by the zombie
    QVector<Agent*> _humansSeen;
    Agent *_nearestHuman;
};

#endif // HUNTERZOMBIESTRATEGY_H
