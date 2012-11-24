#ifndef AGENT_H
#define AGENT_H

#include <QPoint>
#include <QColor>
#include <QPainterPath>
#include <QGraphicsScene>
#include <QRectF>
#include <QTimer>

#include "strategy.h"

/**
  * @class Agent
  *
  * Agent that contains a Strategy.
  * Can be intellegent or even passive.
  */
class Agent : public QObject
{
    Q_OBJECT
public:
    /**
      * Constructor
      *
      * @param strategy The strategy of the agent
      * @see StrategyEnum
      */
    Agent(StrategyEnum strategy);
    /**
      * Destructor
      */
    ~Agent();

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
      * Update the agent depending of his strategy
      */
    void update();
    /**
      * Set the position of the agent
      *
      * @param x X position
      * @param y Y position
      */
    void setPos(int x, int y);
    /**
      * Set the position of the agent
      *
      * @param pos The position as a point
      */
    void setPos(const QPointF &pos);
    /**
      * Setter : _rotation
      *
      * @param rotation The angle of the rotation (Degree)
      */
    void setRotation(qreal rotation);
    /**
      * Getter : _pos
      *
      * @return The position as a point
      */
    QPointF pos() const;
    /**
      * Getter : _rotation
      *
      * @return The angle (Degree) of the rotation
      */
    qreal rotation();
    /**
      * Getter : X
      *
      * @return The x position
      */
    int x() const;
    /**
      * Getter : Y
      *
      * @return The y position
      */
    int y() const;
    /**
      * Getter : _color
      * Depends on the strategy
      *
      * @return The color of the agent
      */
    QColor color() const;
    /**
      * Kill the agent in a few time
      */
    void kill();
    /**
      * Contaminate by a hunter zombie shot
      */
    void contaminateByShot();
    /**
      * Getter : _notMapped
      *
      * @return The relative movement of the next step
      */
    QPointF getMovement() const;
    /**
      * Setter : _notMapped
      *
      * @param movement The relative movement of the next step
      */
    void setMovement(const QPointF &movement);
    /**
      * Add some angle to the agent
      *
      * @param value The value of the angle to add
      * @return The new value of the angle (old + value)
      */
    qreal addAngle(qreal value);
    /**
      * Add some speed to the agent
      *
      * @param value The value of the speed to add
      * @return The new value of the speed (old + value)
      */
    qreal addSpeed(qreal value);
    /**
      * Change the strategy of the agent
      *
      * @param strategy The new strategy
      */
    void changeStrategy(Strategy *strategy);
    /**
      * Tell if the agent follow a zombie strategy
      *
      * @return True if the agent is a Zombie, false else
      */
    bool isZombie();
    /**
      * If the agent is a hunter, it reloads it's weapon
      */
    void reload();
    /**
      * Tells if the hunter is reloading
      *
      * @return True if the agent is reloading, false else
      */
    bool readyToShot();
    /**
      * Tells if the agent is still alive
      *
      * @return True if the agent is alive, false if he's about to die
      */
    bool isAlive();
    /**
      * Tells if the agent is about to be contaminated
      *
      * @return True if the agent is contaminated, false otherwise
      */
    bool isAboutToBeContaminated();
    /**
      * Getter : _index
      *
      * @return The index(id) of the agent
      */
    unsigned index();
    /**
      * Change the strategy of the agent
      *
      * @param strategy The new strategy
      */
    void setStrategy(StrategyEnum strategy);
    /**
      * Set the index of the Agent class to 0
      */
    static void resetIndex();
    /**
      * Tells if the agent is a hunter
      *
      * @return True if the agent is a hunter, false else
      */
    bool isHunter();
    /**
      * Setter : _neighborsIndex
      *
      * @param neighborsIndex The index of the controller's neighbors vector
      */
    void setNeighborsIndex(unsigned neighborsIndex);
    /**
      * Getter : _neighborsIndex
      *
      * @param The index of the controller's neighbors vector
      */
    unsigned getNeighborsIndex();
    /**
      * Setter : _neighbors
      *
      * @param neighbors The agent's neighbors vector
      */
    void setNeighbors(const QVector<Agent*> &neighbors);
    /**
      * Getter : _neighbors
      *
      * @return The agent's neighbors vector
      */
    QVector<Agent*> getNeighbors() const;
    /**
      * Agent contaminated by zombie
      */
    void contamination();

private:
    /// The agent's neighbors vector
    QVector<Agent*> _neighbors;
    /// The index of the controller's neighbors vector
    unsigned _neighborsIndex;
    /// Position of the agent
    QPointF _pos;
    /// The relative movement
    QPointF _notMapped;
    /// The rotation of the agent
    qreal _rotation;
    /// Agent's strategy
    Strategy *_strategy;
    /// Current angle
    qreal _angle;
    /// Timer for the agent death
    QTimer _deathTimer;
    /// Timer for the contamination by shot
    QTimer _contaminationTimer;
    /// Current speed
    qreal _speed;
    /// Index of the agent
    unsigned _index;
    /// Class member for Index auto count
    static unsigned Index;
    /// Timer for the weapon reload
    QTimer _reload;

signals:
    /**
      * SIGNAL
      * Tells to the controller that the agent is dead
      * @param agent The dead agent
      */
    void deadAgent(Agent *agent);
    /**
      * SIGNAL
      * Tells to the controller that the agent is contaminated (by shot)
      * @param agent The contaminated agent
      */
    void agentContaminated(Agent *agent);

private slots:
    /**
      * SLOT
      * On death timer out
      */
    void onDeathTime();
    /**
      * SLOT
      * On contamination timer out
      */
    void onContaminationTime();
};

/**
  * Distance between two agents
  *
  * @param a1 First agent
  * @param a2 Second agent
  * @return The distance between a1 & a2
  */
double distanceBetween(Agent *a1, Agent *a2);

#endif // AGENT_H
