#pragma once

// Implementation of a Generic Individual

#include "geno.h"
#include "pheno.h"

template<typename G, typename P>
class Ind
{
private:
    long id;
    G* genotype;
    P* phenotype;
    double fitness;

public:
    Ind()
    {
        // TODO
    }
};
