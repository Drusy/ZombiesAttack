#ifndef MODELTEST_H
#define MODELTEST_H

#include "autotest.h"

#include <QObject>

class AgentTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void strategyTest();
    void contaminationTest();
    void deathTest();
    void reloadTest();
    void cleanupTestCase();
};

DECLARE_TEST(AgentTest)

#endif // MODELTEST_H
