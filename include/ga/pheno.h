#pragma once

// Implementation of a Generic PhenoType. This is required to be extended by programs which use this project

class Pheno
{
public:
    virtual ~Pheno() { }
    virtual double evaluateFitness() const = 0;
};

// the following pheno types are used for testing purposes

// a simple test which returns the difference between the avg and 0.5
class FloatPhenoDummy : public Pheno
{
protected:
    std::vector<float> floatstring;

public:
    virtual double evaluateFitness() const
    {
        double fitness = 0.0;

        for (int i = 0; i < floatstring.size(); ++i)
        {
            fitness += floatstring[i];
        }

        fitness /= double(floatstring.size());
        fitness -= 0.5;

        if (fitness < 0.0) return 1.f + fitness;
        return 1.f - fitness;
    }

    void setFloatstring(const std::vector<float>& param)
    {
        floatstring = param;
    }
};

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
