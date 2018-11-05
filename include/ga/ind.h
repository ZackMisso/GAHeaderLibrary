#pragma once

// Implementation of a Generic Individual

#include <ga/geno.h>
#include <ga/pheno.h>

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
