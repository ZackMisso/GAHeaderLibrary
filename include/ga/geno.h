#pragma once

#include <ga/pheno.h>
#include <pcg32.h>

class Geno
{
public:
    virtual ~Geno() { }

    virtual void initializeRandom(pcg32& rng) = 0;
    virtual Pheno generatePhenotype() const = 0;
    virtual double evaluateFitness() const = 0;
    virtual Geno* copy() const = 0;

    // mutation and crossover are drastically dependent on the genotype
    // implementation so those are left as extensions
    virtual Geno* mutate(pcg32& rng, float mutateChance) const = 0;
    virtual Geno* crossover(const Geno* other,
                            pcg32& rng,
                            float crossoverChance) const = 0;
};
