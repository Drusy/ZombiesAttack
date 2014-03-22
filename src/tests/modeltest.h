#ifndef MODELTEST_H
#define MODELTEST_H

#include "autotest.h"

#include <QObject>

class ModelTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void addRemoveTest();
    void cleanupTestCase();
};

DECLARE_TEST(ModelTest)

#endif // MODELTEST_H
