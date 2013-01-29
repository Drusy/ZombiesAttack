#ifndef STRATEGY_H
#define STRATEGY_H

#include <QRectF>
#include <QPainterPath>
#include <QColor>

#define PI 3,14159265

/**
  * @enum StrategyEnum
  *
  * Defines a strategy
  */
enum StrategyEnum
{
    human,
    hunter,
    zombie,
    hunterZombie,
    humanBuilder,
    block
};

class Agent;

/**
  * @class Strategy
  *
  * Virtual class defines a strategy
  */
class Strategy : public QObject
{
    Q_OBJECT
public:
    Strategy();
    /**
      * Destructor
      */
    virtual ~Strategy();
    /**
      * Execute the strategy of the agent (movements, collisions...)
      *
      * @param agent Agent executing the strategy
      */
    virtual void execute(Agent *agent) = 0;
    /**
      * The bounding rectangle of the item (Needed by the view the view)
      *
      * @return The bounding rectangle
      */
    virtual QRectF boundingRect() const = 0;
    /**
      * The shape for the agent to be drawn
      */
    virtual QPainterPath shape() const = 0;
    /**
      * Getter : _color
      *
      * @return The color of the agent
      */
    virtual QColor color() const = 0;
    /**
      * Increments the number of persons in the strategy
      */
    void addOne();
    /**
      * Decrements the number of persons in the strategy
      */
    void removeOne();
    /**
      * Getter : _count
      *
      * @return The number of persons in the strategy
      */
    unsigned count();

    /**
      * @return The name of the strategy
      */
    virtual QString toString() = 0;

protected:
    /// Color of the agent
    QColor _color;
    /// Number of elements in the strategy
    unsigned _count;

signals:
    /**
      * SIGNAL
      * Tells to the view that the population of the strategy changed
      */
    void popChanged();
};

#endif // STRATEGY_H
