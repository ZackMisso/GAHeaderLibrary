#pragma once

#include "ind.h"

template <typename G, typename P>
class HallOfFame
{
private:
    vector< Ind<G, P>* > hallOfFame;
    int maxSize;

public:
    HallOfFame()
    {
        // TODO
    }

    HallOfFame(int size)
    {
        // TODO
    }
    
    void recalculateHallOfFame(const vector< Ind<G, P>* >& pop)
    {
        // TODO
    }

    void replacePopWithHall(vector< Ind<G, P>* >& pop)
    {
        // TODO
    }
};
