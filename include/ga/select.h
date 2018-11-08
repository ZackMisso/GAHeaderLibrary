#pragma once

#include <ga/ind.h>
#include <vector>

typedef std::vector<Individual*> Population;

class SelectorFunction
{
    virtual Population select(Population& pop) const = 0;
};
