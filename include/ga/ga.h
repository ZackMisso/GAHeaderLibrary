#pragma once

#include <ga/select.h>

template<typename G, typename S,
         typename std::enable_if<std::is_base_of<Geno, G>::value>::type* = nullptr,
         typename std::enable_if<std::is_base_of<SelectorFunction, S>::value>::type* = nullptr>
class GA
{
protected:
    std::vector<Geno*> bestGenInds;
    Population hallOfFame;
    pcg32 rng;
    S* selector;
    float crossoverChance;
    float mutationChance;
    float selectionPercent;
    int numberOfGenerations;
    int maxPopulationSize;
    int hallOfFameSize;
    int individualSize;
    long globalIdCounter;
    long seed;

public:
    GA(int numGen = 10, int maxPop = 10, int hallSize = 2, int indSize = 20, long seed = 0x30352)
        : numberOfGenerations(numGen),
          maxPopulationSize(maxPop),
          hallOfFameSize(hallSize),
          individualSize(indSize),
          seed(seed)
    {
        hallOfFame = Population();
        bestGenInds = std::vector<Geno*>();
        globalIdCounter = 0;
        selector = new S();

        crossoverChance = 0.2f;
        mutationChance = 0.05f;
        selectionPercent = 0.25f;

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

    virtual Population initializeInitialPopulation()
    {
        Population inds = Population();

        for (int i = 0; i < maxPopulationSize; ++i)
        {
            G* newGeno = new G(individualSize);
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

    virtual Population generateNewGeneration(Population& pop, bool killOld=true)
    {
        Population newPop = Population();

        if (pop.size() > 1)
        {
            Population selected = selector->select(pop,
                                                   rng,
                                                   (int)(selectionPercent * maxPopulationSize));

            while (newPop.size() < maxPopulationSize - hallOfFameSize)
            {
                int selectedOne = int(rng.nextFloat() * selected.size());
                int selectedTwo = selectedOne;

                while (selectedOne == selectedTwo)
                {
                    selectedTwo = int(rng.nextFloat() * selected.size());
                }

                Geno* one = selected[selectedOne]->getGeno();
                Geno* two = selected[selectedTwo]->getGeno();

                Individual* newInd = new Individual(one->crossover(two, rng, crossoverChance),
                                                    globalIdCounter++);

                newPop.push_back(newInd);
            }
        }

        for (int i = 0; i < hallOfFame.size(); ++i)
        {
            newPop.push_back(hallOfFame[i]->copy());
        }

        for (int i = 0; i < newPop.size(); ++i)
        {
            newPop[i]->getGeno()->mutate(rng, mutationChance);
        }

        if (killOld)
        {
            for (int i = 0; i < pop.size(); ++i)
            {
                delete pop[i];
            }
        }

        return newPop;
    }

    virtual void updateHallOfFame(const Population& pop)
    {
        Population newHallOfFame = Population();

        int i = 0;
        int j = 0;

        if (hallOfFame.size() == 0)
        {
            for (int i = 0; i < hallOfFameSize; ++i)
            {
                newHallOfFame.push_back(pop[i]->copy());
            }
        }
        else
        {
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
        }

        for (int k = 0; k < hallOfFame.size(); ++k) delete hallOfFame[k];

        hallOfFame = newHallOfFame;

        bestGenInds.push_back(hallOfFame[0]->getGeno()->copy());
    }

    virtual void evolve()
    {
        Population pop = initializeInitialPopulation();

        for (int i = 0; i < numberOfGenerations; ++i)
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

    void setCrossoverChance(float param) { crossoverChance = param; }
    void setMutationChance(float param) { mutationChance = param; }
    void setSelectionPercent(float param) { selectionPercent = param; }

    std::vector<Geno*> getBestGenInds() const { return bestGenInds; }
};
