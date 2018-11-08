#pragma once

// Implementation of a Generic PhenoType. This is required to be extended by programs which use this project

class Pheno
{
public:
    virtual ~Pheno() { }
    virtual double evaluateFitness() const = 0;
};

// the following pheno types are used for testing purposes

// a simple test which returns the number of "on" bits as the fitness
class BitPhenoDummy : public Pheno
{
protected:
    std::vector<bool> bitstring;

public:
    virtual double evaluateFitness() const
    {
        double fitness = 0.0;

        for (int i = 0; i < bitstring.size(); ++i)
        {
            if (bitstring[i]) fitness += 1.0;
        }

        return fitness;
    }

    void setBitstring(const std::vector<bool>& param)
    {
        bitstring = param;
    }
};
