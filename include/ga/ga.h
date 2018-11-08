#pragma once

#include <ga/pop.h>
#include <ga/hall.h>
#include <ga/select.h>
#include <pcg32.h>
#include <vector>

template<typename G, typename S,
         typename std::enable_if<std::is_base_of<Geno, G>::value>::type* = nullptr,
         typename std::enable_if<std::is_base_of<SelectorFunction, S>::value>::type* = nullptr>
class GA
{
private:
    std::vector<G*> bestGenInds;
    Population hallOfFame;
    pcg32 rng;
    S* selector;
    double crossoverChance;
    double mutationChance;
    int numberOfGenerations;
    int maxPopulationSize;
    int hallOfFameSize;
    long globalIdCounter;
    long seed;

public:
    GA(int numGen = 10, int maxPop = 10, int hallSize = 2, long seed = 0x30352)
        : numberOfGenerations(numGen),
          maxPopulationSize(maxPop),
          hallOfFameSize(hallSize),
          seed(seed)
    {
        hallOfFame = Population();
        bestGenInds = std::vector<G*>();
        globalIdCounter = 0;
        selector = new S();

        // set up rng
        srand(seed);
        uint64_t r1 = rand();
        uint64_t r2 = rand();
        rng = pcg32(r1, r2);
    }

    ~GA()
    {
        for (int i = 0; i < hallOfFame.size(); ++i) delete hallOfFame[i];
        for (int i = 0; i < bestGenInds.size(); ++i) delete bestGenInds[i];
        delete selector;
    }

    virtual Population initializeInitialPopulation() const
    {
        Population inds = Population();

        for (int i = 0; i < maxPopulationSize; ++i)
        {
            G* newGeno = new G();
            newGeno->initializeRandom(rng);
            inds.push_back(new Individual(newGeno, globalIdCounter++));
        }

        return inds;
    }

    virtual void evaluateFitnesses(const Population& inds) const
    {
        for (int i = 0; i < inds.size(); ++i)
        {
            inds[i]->evaluateFitness();
        }
    }

    virtual Population generateNewGeneration(const Population& pop) const
    {
        Population newPop = Population();

        if (pop.size() > 1)
        {
            Population selectedForBreeding = selector->select(pop);

            while (newPop.size() < maxPopulationSize)
            {
                G* one = pop[int(rng.nextFloat() * pop.size())];
                G* two = one;

                while (one == two) two = pop[int(rng.nextFloat() * pop.size())];

                newPop.push_back(one->crossover(two, rng, crossoverChance));
            }
        }

        for (int i = 0; i < newPop.size(); ++i)
        {
            newPop[i]->getGeno()->mutate(rng, mutationChance);
        }

        for (int i = 0; i < pop.size(); ++i)
        {
            delete pop[i];
        }

        return newPop;
    }

    virtual void updateHallOfFame(const Population& pop)
    {
        Population newHallOfFame = Population();

        int i = 0;
        int j = 0;

        while (i + j < hallOfFameSize)
        {
            if (pop[i]->getFitness() < hallOfFame[j]->getFitness())
            {
                newHallOfFame.push_back(hallOfFame[j]->copy());
                ++j;
            }
            else
            {
                newHallOfFame.push_back(pop[i]->copy());
                ++i;
            }
        }

        for (int k = 0; k < hallOfFame.size(); ++k) delete hallOfFame[k];

        hallOfFame = newHallOfFame;

        bestGenInds.push_back(hallOfFame[0]->copy());
    }

    virtual void evolve()
    {
        Population pop = initializeInitialPopulation();

        for (int i = 0; i < maxPopulationSize; ++i)
        {
            evaluateFitnesses(pop);
            std::sort(pop.begin(), pop.end(), IndividualComparator());
            updateHallOfFame(pop);

            if (i != maxPopulationSize - 1)
            {
                pop = generateNewGeneration(pop);
            }
        }
    }
};
