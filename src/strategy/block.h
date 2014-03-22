#ifndef BLOCK_H
#define BLOCK_H

#include "strategy.h"

class BlockStrategy : public Strategy
{
protected:
    static BlockStrategy* _instance;
    BlockStrategy();
public:
    static BlockStrategy* instance();
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

    void execute(Agent*);
    QColor color() const;
    virtual QString toString();
};

#endif // BLOCK_H
