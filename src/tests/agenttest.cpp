#include "agenttest.h"
#include "../strategy/humanstrategy.h"
#include "../strategy/zombiestrategy.h"
#include "../strategy/hunterzombiestrategy.h"
#include "../strategy/hunterstrategy.h"
#include "../model/agent.h"

void AgentTest::initTestCase()
{

}

void AgentTest::strategyTest()
{
    Agent agent(hunter);
    Agent agent2(human);

    agent2.setStrategy(zombie);

    QCOMPARE(agent.getStrategy(), HunterStrategy::instance());
    QCOMPARE(agent2.getStrategy(), ZombieStrategy::instance());
}

void AgentTest::contaminationTest()
{
    Agent agentHunter(hunter);
    Agent agentHuman(human);
    Agent agentBlock(block);
    int oldPV;
    int newPV;

    agentHunter.contamination();
    agentHuman.contamination();

    oldPV = agentBlock.getPV();
    agentBlock.contamination();
    newPV = agentBlock.getPV();

    QCOMPARE(agentHunter.getStrategy(), HunterZombieStrategy::instance());
    QCOMPARE(agentHuman.getStrategy(), ZombieStrategy::instance());
    QCOMPARE(oldPV - 1, newPV);
}

void AgentTest::deathTest()
{
    Agent agent(human);

    QCOMPARE(agent.isAlive(), true);
    agent.kill();
    QCOMPARE(agent.isAlive(), false);
}

void AgentTest::reloadTest()
{
    Agent agent(hunter);

    QCOMPARE(agent.readyToShot(), true);
    agent.reload();
    QCOMPARE(agent.readyToShot(), false);
}

void AgentTest::cleanupTestCase()
{

}
