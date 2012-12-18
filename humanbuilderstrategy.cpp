#include "humanbuilderstrategy.h"

#include <QStyleOption>

HumanBuilderStrategy* HumanBuilderStrategy::_instance = 0;

HumanBuilderStrategy::HumanBuilderStrategy()
{
    _color = Qt::darkYellow;
}

HumanBuilderStrategy* HumanBuilderStrategy::instance()
{
    return _instance ? _instance : (_instance = new HumanBuilderStrategy());
}

