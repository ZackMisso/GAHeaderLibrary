#pragma once

#include <ga/ind.h>
#include <vector>

typedef std::vector<Individual*> Population;

class SelectorFunction
{
public:
    virtual Population select(Population& pop,
                              pcg32& rng,
                              int count) const = 0;

    float totalFitness(const Population& pop) const
    {
        float total = 0.0;

        for (int i = 0; i < pop.size(); ++i)
        {
            total += pop[i]->getFitness();
        }

        return total;
    }
};

// stochastic universal sampling
class SUS : public SelectorFunction
{
public:
    virtual Population select(Population& pop,
                              pcg32& rng,
                              int count) const
    {
        Population selected = Population();

        float totalFit = totalFitness(pop);

        float step = totalFit / float(count);
        float start = rng.nextFloat() * step;

        float accumulatedFitness = 0.f;
        float currentLocation = start;

        for (int i = 0; i < pop.size(); ++i)
        {
            accumulatedFitness += pop[i]->getFitness();

            if (accumulatedFitness > currentLocation)
            {
                currentLocation += step;
                accumulatedFitness -= pop[i]->getFitness();
                selected.push_back(pop[i]);
                i--;
            }
        }

        return selected;
    }
};
