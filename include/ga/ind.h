#pragma once

// the individual class is an abstraction on top of the genotype implementation
// to add an interface layer for the GA algorithm to store information without
// requiring the genotype extensions to keep track of this information.

#include <ga/geno.h>
#include <ga/pheno.h>

class Individual
{
private:
    Geno* geno;
    long id;
    double fitness;

public:
    Individual(Geno* geno, long id)
        : geno(geno), id(id), fitness(0.0) { }

    Individual* copy() const
    {
        Individual* newInd = new Individual(geno->copy(), id);
        newInd->fitness = fitness;
        return newInd;
    }

    ~Individual()
    {
        delete geno;
    }

    void evaluateFitness()
    {
        fitness = geno->evaluateFitness();
    }

    void updateID(long param) { id = param; }

    // getter methods
    Geno* getGeno() const { return geno; }
    double getFitness() const { return fitness; }
    long getId() const { return id; }
};

struct IndividualComparator {
    bool operator()(const Individual* indOne, const Individual* indTwo) const {
        return indOne->getFitness() > indTwo->getFitness();
    }
};
