#include "strategy.h"
#include "agent.h"

Strategy::Strategy():
    _count(0)
{
}

Strategy::~Strategy()
{
}

void Strategy::addOne()
{
    ++_count;
    emit popChanged();
}

void Strategy::removeOne()
{
    --_count;
    emit popChanged();
}

unsigned Strategy::count()
{
    return _count;
}
