#include <QApplication>
#include "controller.h"
#include "MersenneTwister.h"

int main(int argc, char *argv[])
{
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);

    QApplication a(argc, argv);
    Controller c;
    
    return a.exec();
}
