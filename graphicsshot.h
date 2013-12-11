#ifndef GRAPHICSSHOT_H
#define GRAPHICSSHOT_H

#include <QGraphicsItem>
#include <QTimer>

#include "agent.h"

class GraphicsAgent;

/**
  * @class GraphicsShot
  *
  * Represent an shot on a QGraphicsView
  */
class GraphicsShot : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    /**
      * Constructor
      *
      * @param scene The QGraphicsScene on which will be inserted shots
      * @param _startItem Hunter who's shooting
      * @param _endItem Zombie shot
      */
    GraphicsShot(QGraphicsScene *scene, GraphicsAgent *_startItem, GraphicsAgent *_endItem);

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

protected:
    QGraphicsScene *_scene;
    /// Hunter who's shooting
    GraphicsAgent *_startItem;
    /// Zombie shot
    GraphicsAgent *_endItem;

    friend class View;
};

#endif // GRAPHICSSHOT_H
