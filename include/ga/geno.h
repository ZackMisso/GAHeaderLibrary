#pragma once

#include <ga/pheno.h>

class Geno
{
public:
    virtual void initializeRandom() = 0;
    virtual Pheno generatePhenotype() const = 0;
    virtual double evaluateFitness() const = 0;

    // mutate
    virtual Geno operator~(const Geno& other) const = 0;
    // crossover
    virtual Geno operator/(const Geno& one, const Geno& two) const = 0;
};
