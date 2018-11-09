#pragma once

#include <ga/pheno.h>
#include <pcg32.h>

class Geno
{
protected:
    int size;

public:
    Geno(int size) : size(size) { }
    virtual ~Geno() { }

    float evaluateFitness() const
    {
        Pheno* pheno = generatePhenotype();
        float fitness = pheno->evaluateFitness();
        delete pheno;
        return fitness;
    }

    virtual void initializeRandom(pcg32& rng) = 0;
    virtual Pheno* generatePhenotype() const = 0;
    virtual Geno* copy() const = 0;
    virtual void print() const = 0;

    // mutation and crossover are drastically dependent on the genotype
    // implementation so those are left as extensions
    virtual void mutate(pcg32& rng, float mutateChance) = 0;
    virtual Geno* crossover(const Geno* other,
                            pcg32& rng,
                            float crossoverChance) const = 0;
};

class FloatGeno : public Geno
{
protected:
    std::vector<float> floatstring;
    float minVal;
    float maxVal;

public:
    FloatGeno(int size) : Geno(size)
    {
        floatstring = std::vector<float>();
        minVal = 0.f;
        maxVal = 1.f;
    }

    virtual void initializeRandom(pcg32& rng)
    {
        for (int i = 0; i < size; ++i)
        {
            float val = rng.nextFloat() * (maxVal - minVal) + minVal;
            floatstring.push_back(val);
        }
    }

    virtual Pheno* generatePhenotype() const
    {
        FloatPhenoDummy* pheno = new FloatPhenoDummy();
        pheno->setFloatstring(floatstring);
        return pheno;
    }

    virtual Geno* copy() const
    {
        FloatGeno* newGeno = new FloatGeno(size);

        for (int i = 0; i < floatstring.size(); ++i)
        {
            newGeno->floatstring.push_back(floatstring[i]);
        }

        newGeno->minVal = minVal;
        newGeno->maxVal = maxVal;

        return newGeno;
    }

    virtual void mutate(pcg32& rng, float mutateChance)
    {
        for (int i = 0; i < size; ++i)
        {
            floatstring[i] += rng.nextFloat() - 0.5f;
        }
    }

    virtual Geno* crossover(const Geno* other,
                            pcg32& rng,
                            float crossoverChance) const
    {
        FloatGeno* newGeno = new FloatGeno(size);

        for (int i = 0; i < size; ++i)
        {
            if (rng.nextFloat() < crossoverChance)
            {
                float val = (floatstring[i] + ((FloatGeno*)other)->floatstring[i]) / 2.f;
                newGeno->floatstring.push_back(val);
            }
            else
            {
                newGeno->floatstring.push_back(floatstring[i]);
            }
        }

        return newGeno;
    }

    virtual void print() const
    {
        for (int i = 0; i < floatstring.size(); ++i)
        {
            std::cout << floatstring[i] << " ";
        }

        std::cout << std::endl;
    }
};

class BitGeno : public Geno
{
protected:
    std::vector<bool> bitstring;

public:
    BitGeno(int size) : Geno(size)
    {
        bitstring = std::vector<bool>();
    }

    virtual void initializeRandom(pcg32& rng)
    {
        for (int i = 0; i < size; ++i)
        {
            if (rng.nextFloat() > 0.5) bitstring.push_back(true);
            else bitstring.push_back(false);
        }
    }

    // this method must be extended for custom phenotypes
    virtual Pheno* generatePhenotype() const
    {
        BitPhenoDummy* pheno = new BitPhenoDummy();
        pheno->setBitstring(bitstring);
        return pheno;
    }

    virtual Geno* copy() const
    {
        BitGeno* newGeno = new BitGeno(size);

        for (int i = 0; i < bitstring.size(); ++i)
        {
            newGeno->bitstring.push_back(bitstring[i]);
        }

        return newGeno;
    }

    virtual void mutate(pcg32& rng, float mutateChance)
    {
        for (int i = 0; i < size; ++i)
        {
            if (rng.nextFloat() < mutateChance)
            {
                bitstring[i] = !bitstring[i];
            }
        }
    }

    virtual Geno* crossover(const Geno* other,
                            pcg32& rng,
                            float crossoverChance) const
    {
        BitGeno* newGeno = new BitGeno(size);

        for (int i = 0; i < size; ++i)
        {
            if (rng.nextFloat() < crossoverChance)
            {
                newGeno->bitstring.push_back(bitstring[i]);
            }
            else
            {
                newGeno->bitstring.push_back(((BitGeno*)other)->bitstring[i]);
            }
        }

        return newGeno;
    }

    virtual void print() const
    {
        for (int i = 0; i < bitstring.size(); ++i)
        {
            if (bitstring[i]) std::cout << "1";
            else std::cout << "0";
        }

        std::cout << std::endl;
    }
};
