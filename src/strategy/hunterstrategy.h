#ifndef HUNTERSTRATEGY_H
#define HUNTERSTRATEGY_H

#include <QTimer>

#include "strategy.h"
#include "../agent.h"

/**
  * @class HunterStrategy
  *
  * Strategy for 'defense' hunter
  * Kind of singleton
  */
class HunterStrategy : public Strategy
{
    Q_OBJECT
public:
    ~HunterStrategy();
    /**
      * Static constructor for unique instance
      */
     static HunterStrategy* instance();
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
       * Search the nearest zombie seen
       *
       * @param agent The hunter
       * @param The nearest zombie
       */
     Agent* nearestZombie(Agent *agent);
     /**
       * Search the nearest far hunter seen
       *
       * @param agent The hunter
       * @param The nearest far hunter
       */
     Agent* nearestFarhunter(Agent *agent);
     /**
       * Check if the agent collides (see) with some zombie
       *
       * @param agent The hunter
       * @return True if the hunter see zombies, false else
       */
     void seeZombies(Agent *inAgent);
     /**
       * Check if some agent collides with another
       *
       * @param agent First agent
       * @param other Second agent
       * @return True if the two items are colliding , false else
       */
     bool collidesWithItem(const Agent *agent, const Agent *other, unsigned range) const;
     /**
       * Check if the agent collides (see) with some zombie
       *
       * @param agent The Zombie
       */
     void zombiesCollisions(Agent *agent);
     /**
       * Shot a human
       *
       * @param hunter Hunter who's shooting
       * @param zombie Zombie shot
       */
     void shot(Agent *hunter, Agent *zombie);
     /**
       * Random movement on hunter
       *
       * @param agent Agent executing the strategy
       */
     void randomMovement(Agent *agent);
     /**
       * @return The name of the strategy
       */
     virtual QString toString();


protected:
     /**
       * Constructor
       */
    HunterStrategy();

    /// Instance of the singleton
    static HunterStrategy *_instance;
    /// The nearestZombie seen
    Agent *_nearestZombie;
    /// List of zombies seen
    QVector<Agent*> _zombies;
    /// List of others hunters far from this
    QVector<Agent*> _huntersFar;
    /// List of others hunters near from this
    QVector<Agent*> _huntersNear;

signals:
    /**
      * Tells to the controller who's aim by the hunter's shot
      *
       * @param hunter Hunter who's shooting
       * @param zombie Zombie shot
      */
    void zombieShot(Agent *hunter, Agent *zombie);
};


#endif // HUNTERSTRATEGY_H
