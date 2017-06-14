#pragma once

#include "pop.h"
#include "hall.h"
#include <vector>

using namespace std;

// Implementation of a Generic GA

template <typename G, typename P>
class GA
{
private:
    // Pop* population;
    vector< Ind<G, P>* > population; 
    HallOfFame* hallOfFame;
    int numberOfGenerations;
    int maxPopulationSize;
    void* mutatorFunction;
    void* selectorFunction;
    void* crossoverFunction;
    void* fitnessFunction;
    void* gaEvaluateFunction;

public:
    GA()
    {
        // TODO
	hallOfFame = 0x0;
    }

    GA(int numGen, int maxPop)
    {
        // TODO
	hallOfFame = 0x0;
    }

    GA(int numGen, int maxPop, void* mutFunc, void* selFunc, void* crosFunc, void* fitFunc, void* gaFunc)
    {
        // TODO
	hallOfFame = 0x0;
    }

    ~GA()
    {
        if(hallOfFame) delete hallOfFame;
	// TODO
    }

    void createHallOfFame(int size)
    {
        hallOfFame = new HallOfFame(size);
    }

    void evaluateSimple()
    {
        // TODO
    }

    // getter methods
    HallOfFame* getHallOfFame() { return hallOfFame; }
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
