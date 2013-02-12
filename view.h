#ifndef VIEW_H
#define VIEW_H

#include <QtWidgets/QMainWindow>
#include <QVector>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsItem>
#include <QTimer>

#include "model.h"
#include "graphicsagent.h"
#include "graphicsshot.h"

namespace Ui {
class View;
}

/**
  * @class View
  *
  * View of the MVC
  */
class View : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit View(Model *model);
    /**
      * Destructor
      */
    ~View();

    /**
      * @overload QMainWindow
      */
    void resizeEvent (QResizeEvent * event);

    /**
      * Create a new graphical agent and add it to the scene
      *
      * @param agent Model agent linked to the graphical agent
      */
    void createAgent(Agent *agent);
    /**
      * Create a new graphical agent and add it to the scene
      *
      * @param agent Model agent linked to the graphical agent
      * @param x position x
      * @param y position y
      */
    void createAgent(Agent *agent, int x, int y);

    /**
      * Clear all the graphicals agents and clear the scene
      */
    void clear();
    /**
      * Remove corresponding agent from the view
      *
      * @param agent Agent to search
      * @param removeAgent Tells if the view have to remove the agent from the scene or not
      */
    void removeAgent(Agent *agent, bool removeAgent = true);

public slots:
    /**
      * SLOT
      * On turn over, refresh the view
      */
    void onTurnOver();
    /**
      * SLOT
      * On Timer out, tells to the controller to update agents
      */
    void onTimerOut();
    /**
      * SLOT
      * Population changed, update the labels on the view
      */
    void onPopChanged();
    /**
      * SLOT
      * Zombie shot, draw a new shot
      */
    void onZombieShot(Agent *hunter, Agent *zombie);
    /**
      * SLOT
      * Agent contaminated by a zombie hunter
      */
    void onAgentContaminated(Agent *agent);

signals:
    /**
      * SIGNALS
      * Tells to the controller to update the agents
      */
    void nextTurn();
    /**
      * SIGNALS
      * Start new simulation
      */
    void start(unsigned, unsigned, unsigned);
    /**
      * SIGNALS
      * Stop simulation
      */
    void stop();
    
private slots:
    /**
      * SLOT
      * Start button clicked
      */
    void on_startButton_clicked();
    /**
      * SLOT
      * Stop button clicked
      */
    void on_stopButton_clicked();
    /**
      * SLOT
      * Pause button clicked
      * Stop the timers
      */
    void on_pauseButton_clicked();
    /**
      * SLOT
      * Restart button clicked
      * Restart the timers
      */
    void on_restartButton_clicked();

private:
    /// GUI
    Ui::View *ui;
    /// Model of the MVC
    Model *_model;
    /// Scene linked on the view
    QGraphicsScene _scene;
    /// List of graphical agents
    QVector<GraphicsAgent*> _agents;
    /// List of graphicals shots
    QList<GraphicsShot*> _shots;
    /// Timer (fps)
    QTimer _timer;
};

#endif // VIEW_H
