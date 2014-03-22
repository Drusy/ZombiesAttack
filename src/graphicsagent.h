#ifndef QGRAPHICSAGENT_H
#define QGRAPHICSAGENT_H

#include <QGraphicsItem>
#include <QSize>

#include "model/agent.h"
#include "graphicsshot.h"

/**
  * @class GraphicsAgent
  *
  * Represent an Agent on a QGraphicsView
  */
class GraphicsAgent : public QGraphicsItem, public QObject
{
public:
    /**
      * Constructor
      *
      * @param scene The QGraphicsScene on which will be inserted agents
      * @param agent Agent correcponding to the QGraphicsitem
      */
    GraphicsAgent(QGraphicsScene *scene, Agent *agent);

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
      * @overload QGraphicsItem::paint(...);
      */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    /**
      * Getter : _agent
      *
      * @return Corresponding agent
      */
    Agent* agent();
    /**
      * Setter : _shot
      */
    void setShot(GraphicsShot *shot);
    /**
      * Getter : _shot
      */
    GraphicsShot *getShot() const;

protected:
    /// Scene of the view
    QGraphicsScene *_scene;
    /// Model agent
    Agent *_agent;
    /// The agent shot
    GraphicsShot *_shot;

};

#endif // QGRAPHICSAGENT_H
