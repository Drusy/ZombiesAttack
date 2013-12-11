#include "view.h"
#include "ui_view.h"
#include "humanstrategy.h"
#include "zombiestrategy.h"
#include "hunterstrategy.h"
#include "hunterzombiestrategy.h"
#include "humanbuilderstrategy.h"

#include <QGraphicsRectItem>
#include <QDebug>
#include <QResizeEvent>

View::View(Model *model) :
    ui(new Ui::View),
    _model(model)
{
    ui->setupUi(this);
    ui->mainToolBar->setVisible(false);
    ui->load->setVisible(false);
    ui->stopButton->setVisible(false);
    ui->pauseButton->setVisible(false);
    ui->restartButton->setVisible(false);

    _scene.setItemIndexMethod(QGraphicsScene::NoIndex);
//    ui->board->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    ui->board->setScene(&_scene);

    show();
    resizeEvent(0);

    QObject::connect(HumanStrategy::instance(), SIGNAL(popChanged()), this, SLOT(onPopChanged()));
    QObject::connect(ZombieStrategy::instance(), SIGNAL(popChanged()), this, SLOT(onPopChanged()));
    QObject::connect(HunterStrategy::instance(), SIGNAL(popChanged()), this, SLOT(onPopChanged()));
    QObject::connect(HunterZombieStrategy::instance(), SIGNAL(popChanged()), this, SLOT(onPopChanged()));

    _timer.setSingleShot(true);
    QObject::connect(&_timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}

void View::onPopChanged()
{
    ui->humansNumber->setText(QString::number(HumanStrategy::instance()->count()
                                              + HumanBuilderStrategy::instance()->count()));
    ui->zombiesNumber->setText(QString::number(ZombieStrategy::instance()->count()
                                               + HunterZombieStrategy::instance()->count()));
    ui->huntersNumber->setText(QString::number(HunterStrategy::instance()->count()));
}

void View::resizeEvent (QResizeEvent * event)
{
    QRect r = ui->board->rect();
    r.adjust(0, 0, -4, -4);
    _model->setRect(r);
    _scene.setSceneRect(r);

    if (event)
    {
        QSize offset = event->size() - event->oldSize();
        QPointF pos, tmpPos;
        foreach(GraphicsAgent *item, _agents)
        {
            tmpPos = item->agent()->pos() + QPoint(offset.width() / 2, offset.height() / 2);
            pos.setX(qMin(qMax(tmpPos.x(), r.left() + 10.0), r.right() - 10.0));
            pos.setY(qMin(qMax(tmpPos.y(), r.top() + 10.0), r.bottom() - 10.0));

            item->setPos(pos);
            item->agent()->setPos(pos);
        }
    }
}

void View::onTimerOut()
{
    emit nextTurn();
}

void View::onTurnOver()
{
    _scene.update();
    _timer.start(1000 / ui->fps->value());
}

View::~View()
{
    clear();

    delete ui;
}

void View::createAgent(Agent *agent, int x, int y)
{
    GraphicsAgent *graphicsAgent = new GraphicsAgent(&_scene, agent);

    if(x == -1)
        x = qrand() % (unsigned)_scene.sceneRect().width();
    if(y == -1)
        y = qrand() % (unsigned)_scene.sceneRect().height();

    graphicsAgent->setPos(x, y);
    agent->setPos(x, y);

    _scene.addItem(graphicsAgent);
    _agents.push_back(graphicsAgent);
}

void View::on_startButton_clicked()
{
    ui->load->setVisible(true);
    ui->startButton->setVisible(false);
    ui->stopButton->setVisible(true);
    ui->pauseButton->setVisible(true);

    emit start(ui->humansBasePop->value(),
               ui->zombiesBasePop->value(),
               ui->huntersBasePop->value());
    _timer.start(1000 / ui->fps->value());
}

void View::on_stopButton_clicked()
{
    ui->load->setVisible(false);
    ui->startButton->setVisible(true);
    ui->stopButton->setVisible(false);
    ui->pauseButton->setVisible(false);
    ui->restartButton->setVisible(false);

    clear();

    emit stop();
}

void View::clear()
{
    _timer.stop();
    foreach(GraphicsAgent *agent, _agents)
    {
        if (agent->scene())
            _scene.removeItem(agent);
        delete agent;
    }
    _agents.clear();
    foreach(GraphicsShot *shot, _shots)
    {
        if (shot->scene())
            _scene.removeItem(shot);
        delete shot;
    }
    _shots.clear();
    _scene.update();
}

void View::on_pauseButton_clicked()
{
    _timer.stop();
    ui->pauseButton->setVisible(false);
    ui->restartButton->setVisible(true);
}

void View::on_restartButton_clicked()
{
    _timer.start(1000 / ui->fps->value());
    ui->pauseButton->setVisible(true);
    ui->restartButton->setVisible(false);
}

void View::onAgentContaminated(Agent *agent)
{
    removeAgent(agent, false);
}

void View::removeAgent(Agent *agent, bool removeAgent)
{
    GraphicsAgent *graphicsAgent;
    GraphicsShot *startShot;

    foreach(GraphicsShot *shot, _shots)
    {
        graphicsAgent = shot->_endItem;
        if (graphicsAgent && graphicsAgent->agent() == agent)
        {
            if (removeAgent)
            {
                if (graphicsAgent->scene() == &_scene)
                    _scene.removeItem(graphicsAgent);

                startShot = graphicsAgent->getShot();
                if (startShot != 0)
                {
                    if (startShot->scene() == &_scene)
                        _scene.removeItem(startShot);
                    _shots.removeOne(startShot);
                    delete startShot;
                }
            }

            shot->_startItem->setShot(0);

            if (shot->scene() == &_scene)
                _scene.removeItem(shot);
            _shots.removeOne(shot);
            delete shot;

            break;
        }
    }
}

void View::onZombieShot(Agent *hunter, Agent *zombie)
{
    GraphicsShot *shot = new GraphicsShot(&_scene, _agents[hunter->index()], _agents[zombie->index()]);
    _agents[hunter->index()]->setShot(shot);

    _shots.push_back(shot);
    _scene.addItem(shot);
}
