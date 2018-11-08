#pragma once

#include <ga/pheno.h>
#include <pcg32.h>

class Geno
{
public:
    virtual ~Geno() { }

    virtual void initializeRandom(pcg32& rng) = 0;
    virtual Pheno* generatePhenotype() const = 0;
    virtual Geno* copy() const = 0;

    // mutation and crossover are drastically dependent on the genotype
    // implementation so those are left as extensions
    virtual void mutate(pcg32& rng, float mutateChance) = 0;
    virtual Geno* crossover(const Geno* other,
                            pcg32& rng,
                            float crossoverChance) const = 0;
};

class BitGeno : public Geno
{
protected:
    std::vector<bool> bitstring;
    int size;

public:
    BitGeno(int size) : size(size)
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
                bitstring[i] = false;
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
};
