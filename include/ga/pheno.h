#pragma once

// Implementation of a Generic PhenoType. This is required to be extended by programs which use this project

#include <ga/geno.h>

class Pheno
{
public:
    virtual double evaluateFitness() = 0;
};

// #include <ga/geno.h>
//
// template <typename G>
// class Pheno
// {
// private:
// public:
//     Pheno() { }
//
//     virtual void generatePheno(G geno) = 0;
//     virtual double evaluateFitness() = 0;
// };
