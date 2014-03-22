#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QList>
#include <QSize>
#include <QGraphicsScene>
#include <QMap>

#include "../graphicsagent.h"
#include "agent.h"

/**
  * @class Model
  *
  * Model of the MVC
  */
class Model : public QObject
{
    Q_OBJECT
public:
    /**
      * Constructor
      */
    explicit Model();
    /**
      * Destructor
      */
    ~Model();

    /**
      * Add some agent to the model
      *
      * @param agent Agent to be added
      */
    void addAgent(Agent *agent);
    /**
      * Getter : _agents
      *
      * @return The list of agent
      */
    QList<Agent *> getAgents() const;
    /**
      * Setter : _border
      *
      * @param rect The new size of the map
      */
    static void setRect(QRect &rect);
    /**
      * Getter : _border
      *
      * @return The size of the map
      */
    static QRect getRect();
    /**
      * Clear all the model
      */
    void clear();
    /**
      * Remove some agent
      *
      * @param agent Agent to be removed
      */
    void removeAgent(Agent *agent);
    
private:
    /// Agent list
    QList<Agent*> _agents;
    /// Size of the map
    static QRect _border;
};

#endif // MODEL_H
