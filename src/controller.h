#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QVector>
#include "model/model.h"
#include "view.h"
#include "strategy/strategy.h"

#define POOL_SIZE 90

/**
  * @class Controller
  *
  * Controller of the MVC
  */
class Controller : public QObject
{
    Q_OBJECT
public:
    /**
      * Constructor
      */
    explicit Controller();
    /**
      * Destructor
      */
    ~Controller();
    
signals:
    /**
      * SIGNAL
      * Emit this signal when the new position of each agent has been calculated
      */
    void turnOver();
    
public slots:
    /**
      * SLOT
      * On next turn, update each agent
      */
    void onNextTurn();
    /**
      * SLOT
      * On new simulation, create agents
      *
      * @param humans Number of humans
      * @param zombies Number of zombies
      * @param hunter The number of hunters
      */
    void onStart(unsigned humans, unsigned zombies, unsigned hunters);
    /**
      * Clear all the variables and get ready for a new simulation
      */
    void onStop();
    /**
      * Tells to the model to delete an agent
      *
      * @param agent Agent to delete
      */
    void onDeadAgent(Agent *agent);
    /**
      * Next turn with multiple cells
      *
      * @param cell Number of column used
      */
    void nextTurnCells(int cell);
    /**
      * Next turn with only one cell
      */
    void nextTurnOneCell();
    /**
      * Tells to the Model to create a new agent
      *
      * @param number The number of entity to create
      * @param strategy The strategy of each agent
      */
    void create(unsigned number, StrategyEnum strategy, int x = -1, int y = -1);

private:
    /// Model of MVC
    Model *_model;
    /// View of MVC
    View *_view;
    /// The agents divided in a grid (performance)
    QVector<QVector<Agent*> > _agentGrid;
};

#endif // CONTROLLER_H
