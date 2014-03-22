#include "controller.h"
#include "agent.h"
#include "humanstrategy.h"
#include "zombiestrategy.h"
#include "hunterstrategy.h"
#include "hunterzombiestrategy.h"
#include "poolagent.h"

#include <QDebug>
#include <cmath>

Controller::Controller()
{
    _model = new Model();
    _view = new View(_model);

    QObject::connect(this,  SIGNAL(turnOver()), _view, SLOT(onTurnOver()));
    QObject::connect(_view, SIGNAL(nextTurn()), this, SLOT(onNextTurn()));
    QObject::connect(_view, SIGNAL(start(unsigned, unsigned, unsigned)), this, SLOT(onStart(unsigned, unsigned, unsigned)));
    QObject::connect(_view, SIGNAL(stop()), this, SLOT(onStop()));
    QObject::connect(HunterStrategy::instance(), SIGNAL(zombieShot(Agent*,Agent*)), _view, SLOT(onZombieShot(Agent*,Agent*)));
    QObject::connect(HunterZombieStrategy::instance(), SIGNAL(humanShot(Agent*,Agent*)), _view, SLOT(onZombieShot(Agent*,Agent*)));
}

void Controller::onStart(unsigned humans, unsigned zombies, unsigned hunters)
{
    Agent::resetIndex();
//    create(300, hunter);
//    create(2, hunterZombie);
//    create(50, zombie);
//    create(10, block);
    create(humans, human);
    create(zombies, zombie);
    create(hunters, hunter);
}

void Controller::create(unsigned number, StrategyEnum strategy, int x, int y)
{
    Agent *agent;

    for (unsigned i = 0; i < number; ++i)
    {
        //agent = new Agent(strategy);
        agent = PoolAgent::instance(POOL_SIZE)->newAgent(strategy);

        connect(agent, SIGNAL(deadAgent(Agent*)), this, SLOT(onDeadAgent(Agent*)));
        connect(agent, SIGNAL(agentContaminated(Agent*)), _view, SLOT(onAgentContaminated(Agent*)));
        connect(agent, SIGNAL(createAgentSig(uint,StrategyEnum,int,int)), this, SLOT(create(uint,StrategyEnum,int,int)));

        _model->addAgent(agent);
        _view->createAgent(agent, x, y);
    }
}

void Controller::onDeadAgent(Agent *agent)
{
    _view->removeAgent(agent);
    _model->removeAgent(agent);
}

void Controller::onStop()
{
    Agent::resetIndex();
    _model->clear();
}

Controller::~Controller()
{
    delete _view;
    delete _model;
}

void Controller::onNextTurn()
{
    int cell = 1;

    if (cell == 1)
        nextTurnOneCell();
    else
        nextTurnCells(cell);

    emit turnOver();
}

void Controller::nextTurnCells(int cell)
{
    QRect rect = _model->getRect();
    int cell_2 = cell * cell;
    int x, y, neighborIndex;

    _agentGrid.clear();
    for (int i = 0; i < cell_2; ++i)
        _agentGrid.push_back(QVector<Agent*>());

    foreach (Agent *agent, _model->getAgents())
    {
        x = 1;
        y = 1;

        while (agent->x() > ((rect.width() / cell) * x)) ++x;
        while (agent->y() > ((rect.height() / cell) * y)) ++y;

        neighborIndex = qMin(((y - 1) * cell) + x - 1, cell_2 - 1);
        _agentGrid[neighborIndex].push_back(agent);
        agent->setNeighborsIndex(neighborIndex);
    }

    foreach (Agent *agent, _model->getAgents())
    {
        agent->setNeighbors(_agentGrid[agent->getNeighborsIndex()]);
        agent->update();
    }
}

void Controller::nextTurnOneCell()
{
    foreach (Agent *agent, _model->getAgents())
    {
        QList<Agent*> tmp = _model->getAgents();
        tmp.removeOne(agent);
        agent->setNeighbors(tmp.toVector());
        agent->update();
    }

}
