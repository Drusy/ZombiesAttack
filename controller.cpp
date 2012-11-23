#include "controller.h"
#include "agent.h"
#include "humanstrategy.h"
#include "zombiestrategy.h"
#include "hunterstrategy.h"

#include <QDebug>
#include <cmath>

Controller::Controller()
{
    _model = new Model();

    moveToThread(this);
    _model->moveToThread(this);
    HunterStrategy::instance()->moveToThread(this);
    HumanStrategy::instance()->moveToThread(this);
    ZombieStrategy::instance()->moveToThread(this);

    _view = new View(_model);

    QObject::connect(this,  SIGNAL(turnOver()), _view, SLOT(onTurnOver()));
    QObject::connect(_view, SIGNAL(nextTurn()), this, SLOT(onNextTurn()));
    QObject::connect(_view, SIGNAL(start(unsigned, unsigned, unsigned)), this, SLOT(onStart(unsigned, unsigned, unsigned)));
    QObject::connect(_view, SIGNAL(stop()), this, SLOT(onStop()));
    QObject::connect(HunterStrategy::instance(), SIGNAL(zombieShot(Agent*,Agent*)), _view, SLOT(onZombieShot(Agent*,Agent*)));

    start();
}

void Controller::onStart(unsigned humans, unsigned zombies, unsigned hunters)
{
    create(humans, human);
    create(zombies, zombie);
    create(hunters, hunter);
}

void Controller::create(unsigned number, StrategyEnum strategy)
{
    Agent *agent;

    for (unsigned i = 0; i < number; ++i)
    {
        agent = new Agent(strategy);
        connect(agent, SIGNAL(deadAgent(Agent*)), this, SLOT(onDeadAgent(Agent*)));

        _model->addAgent(agent);
        _view->createAgent(agent);
    }
}

void Controller::onDeadAgent(Agent *agent)
{
    _model->removeAgent(agent);
}

void Controller::onStop()
{
    Agent::resetIndex();
    _model->clear();
}

void Controller::run()
{
    exec();
}

Controller::~Controller()
{
    quit();
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
