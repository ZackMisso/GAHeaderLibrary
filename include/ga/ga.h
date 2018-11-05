#pragma once

#include <ga/pop.h>
#include <ga/hall.h>
#include <vector>

using namespace std;

// Implementation of a Generic GA

template <typename G, typename P>
class GA
{
private:
    // Pop* population;
    vector< Ind<G, P>* > population;
    HallOfFame<G, P>* hallOfFame;
    int numberOfGenerations;
    int maxPopulationSize;
    void* mutatorFunction;
    void* selectorFunction;
    void* crossoverFunction;
    void* fitnessFunction;
    void* gaEvaluateFunction; // probably will not use

public:
    GA()
    {
        hallOfFame = 0x0;
        numberOfGenerations = 100;
        maxPopulationSize = 10;
        mutatorFunction = 0x0;
        selectorFunction = 0x0;
        crossoverFunction = 0x0;
        fitnessFunction = 0x0;
        gaEvaluateFunction = 0x0;
        // initialize population... TODO
    }

    GA(int numGen, int maxPop)
    {
        hallOfFame = 0x0;
        numberOfGenerations = numGen;
        maxPopulationSize = maxPop;
        mutatorFunction = 0x0;
        selectorFunction = 0x0;
        crossoverFunction = 0x0;
        fitnessFunction = 0x0;
        gaEvaluateFunction = 0x0;
        // initialize population... TODO
    }

    GA(int numGen, int maxPop, void* mutFunc, void* selFunc, void* crosFunc, void* fitFunc, void* gaFunc)
    {
        hallOfFame = 0x0;
        numberOfGenerations = numGen;
        maxPopulationSize = maxPop;
        mutatorFunction = mutFunc;
        selectorFunction = selFunc;
        crossoverFunction = crosFunc;
        fitnessFunction = fitFunc;
        gaEvaluateFunction = gaFunc;
        // initialize population... TODO
    }

    ~GA()
    {
        if(hallOfFame) delete hallOfFame;
        // delete population TODO
    }

    void createHallOfFame(int size)
    {
        hallOfFame = new HallOfFame<G, P>(size);
    }

    void initializeInitialPopulation()
    {
        // TODO
    }

    void evaluateFitnesses()
    {
        // TODO
    }

    void sortByFitness(vector< Ind<G, P>* >& vec) const
    {
        // TODO
    }

    void selectIndividualsToBreed(vector< Ind<G, P>* >& vec) const
    {
        // TODO
    }

    void generateNextGeneration(const vector< Ind<G, P>* >& selInds, vector< Ind<G, P>* >& pop) const
    {
        // TODO
    }

    void cleanPopulation(int numSaved)
    {
        // TODO
    }

    void fillPopulation(const vector< Ind<G, P>* >& newPop)
    {
        // TODO
    }

    void evaluateSimple()
    {
        initializeInitialPopulation();

        for (int i = 0; i < numberOfGenerations; i++)
        {
            // Replace these with function pointers ... TODO

            vector< Ind<G, P>* > sortedIndividuals;
            vector< Ind<G, P>* > selectedIndividuals;
            vector< Ind<G, P>* > newPopulation;
            int numSaved;

            evaluateFitnesses();
            sortByFitness(sortedIndividuals);
            updateHallOfFame(sortedIndividuals, numSaved);
            selectIndividualsToBreed(sortedIndividuals, selectedIndividuals);
            generateNextGeneration(selectedIndividuals, newPopulation);
            cleanPopulation(numSaved);
            fillPopulation(newPopulation);
        }

        evaluateFitnesses();
        sortByFitness(population);

        // Add Logging... TODO
    }

    // getter methods
    HallOfFame<G, P>* getHallOfFame() { return hallOfFame; }
    int getNumberOfGenerations() { return numberOfGenerations; }
    int getMaxPopulationSize() { return maxPopulationSize; }

    // setter methods
    void setNumberOfGenerations(int param) { numberOfGenerations = param; }
    void setMaxPopulationSize(int param) { maxPopulationSize = param; }
    void setMutatorFunction(void* param) { mutatorFunction = param; }
    void setSelectorFunction(void* param) { selectorFunction = param; }
    void setCrossoverFunction(void* param) { crossoverFunction = param; }
    void setFitnessFunction(void* param) { fitnessFunction = param; }
    void setGAEvaluateFunction(void* param) { gaEvaluateFunction = param; }
};
