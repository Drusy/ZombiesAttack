#include <QApplication>
#include <QDebug>

#include "tests/autotest.h"
#include "controller.h"

#define RUN_TESTS

int main(int argc, char *argv[])
{
#ifdef RUN_TESTS
    int failures = AutoTest::run(argc, argv);

    if (failures == 0)
        qDebug() << "ALL TESTS PASSED";
    else
    {
        qDebug() << failures << " TESTS FAILED!";
        return -1;
    }
#endif

    QApplication a(argc, argv);
    Controller c;
    
    return a.exec();
}
