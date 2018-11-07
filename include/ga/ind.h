#pragma once

#include <ga/geno.h>
#include <ga/pheno.h>

class Individual
{
private:
    long id;
    Geno geno;
    double fitness;

    void evaluateFitness();
};

// Implementation of a Generic Individual

// #include <ga/geno.h>
// #include <ga/pheno.h>
//
// template<typename G, typename P>
// class Ind
// {
// private:
//     long id;
//     G* genotype;
//     P* phenotype;
//     double fitness;
//
// public:
//     Ind()
//     {
//         // TODO
//     }
// };
