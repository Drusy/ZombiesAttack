#ifndef HUMANSTRATEGY_H
#define HUMANSTRATEGY_H

#include "strategy.h"
#include "agent.h"

/**
  * @class HumanStrategy
  *
  * Strategy for 'passive' human
  * Kind of singleton
  */
class HumanStrategy : public Strategy
{
public:
    /**
      * Destructor
      */
    ~HumanStrategy();
    /**
      * Static constructor for unique instance
      */
     static HumanStrategy* instance();
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
       * Check if the agent collides (see) with some zombie
       *
       * @param agent The human
       * @return True if the human see zombies, false else
       */
     bool zombiesCollisions(Agent *agent);
     /**
       * Check if some agent collides with another
       *
       * @param agent First agent
       * @param other Second agent
       * @return True if the two items are colliding , false else
       */
     bool collidesWithItem(Agent *agent, const Agent *other, int rayonCollision = 25);
     /**
       * Check if the agent collides (see) with some zombie
       *
       * @param agent The human
       * @return The list of zombies seen
       */
     QVector<Agent*> seeZombies(Agent *inAgent);
     /**
       * Check if the agent collides with some other agents
       *
       * @param agent The human
       */
     void contactHuman(Agent *agent);
     /**
       * Check if the agent collides with some humans
       *
       * @param agent The human
       * @return True if the zombie see humans, false else
       */
     QVector<Agent*> collidingHumans(Agent *inAgent);


protected:
     /**
       * Constructor
       */
    HumanStrategy();
    /// Instance of the singleton
    static HumanStrategy *_instance;
};

#endif // HUMANSTRATEGY_H
