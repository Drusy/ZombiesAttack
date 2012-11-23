#ifndef GRAPHICSSHOT_H
#define GRAPHICSSHOT_H

#include <QGraphicsItem>
#include <QTimer>

#include "graphicsagent.h"
#include "agent.h"

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
    /// Timer of the shot
    QTimer _shotTimer;

signals:
    /**
      * SIGNAL
      * Tells to the view that the shot is over
      */
    void shotOver(GraphicsShot *, GraphicsAgent *);

public slots:
    /**
      * SLOT
      * Triggered on the shot timer is over
      * Emit shotOver to the view
      */
    void onShotOver();
};

#endif // GRAPHICSSHOT_H
