#pragma once

// Implementation of a Generic Population
// Probably will delete this class

#include "ind.h"
#include <iostream>
#include <vector>

using namespace std;

template <typename G, typename P>
class Pop
{
private:
    vector< Ind<G, P>* > population;
    int maxPopulationSize;

public:
    Pop()
    {
        // TODO
    }

    Pop(int initialSize)
    {
        // TODO
    }

    void initializePopulation()
    {
        // TODO
    }

    void createNextGeneration()
    {
        // TODO
    }
};
