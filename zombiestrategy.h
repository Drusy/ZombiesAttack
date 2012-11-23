#ifndef ZOMBIESTRATEGY_H
#define ZOMBIESTRATEGY_H

#include "strategy.h"
#include "agent.h"

/**
  * @class ZombieStrategy
  *
  * Strategy for 'attack' zombie
  * Kind of singleton
  */
class ZombieStrategy : public Strategy
{
public:
    /**
      * Destructor
      */
    ~ZombieStrategy();
    /**
      * Static constructor for unique instance
      */
     static ZombieStrategy* instance();
     /**
       * Execute the strategy of the agent (movements, collisions...)
       *
       * @param agent Agent executing the strategy
       */
     void execute(Agent *agent);
     /**
       * The bounding rectangle of the item (Needed by the view the view)
       *
       * @return The bounding rectangle
       */
     QRectF boundingRect() const;
     /**
       * The shape for the agent to be drawn
       */
     QPainterPath shape() const;
     /**
       * Getter : _color
       *
       * @return The color of the agent
       */
     QColor color() const;
     /**
       * Check if the agent collides (see) with some humans
       *
       * @param agent The zombie
       * @return True if the zombie see humans, false else
       */
     QVector<Agent*> collidingHumans(Agent *inAgent);
     /**
       * Check if some agent collides with another
       *
       * @param agent First agent
       * @param other Second agent
       * @return True if the two items are colliding , false else
       */
     bool collidesWithItem(const Agent *agent, const Agent *other) const;
     /**
       * Contaminate every colliding human
       *
       * @param agent The zombie
       */
     void contaminates(Agent *agent);
     /**
       * Search the nearest human seen
       *
       * @param agent The hunter
       * @param The nearest human
       */
     Agent* nearestHuman(Agent *agent);

protected:
     /// Humans seen by the zombie
     QVector<Agent*> _humansSeen;
     /**
       * Constructor
       */
    ZombieStrategy();
    /// Instance of the singleton
    static ZombieStrategy *_instance;
};



#endif // ZOMBIESTRATEGY_H
