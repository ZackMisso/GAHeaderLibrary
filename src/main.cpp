// This file is only used for setting up and running tests

#include <iostream>
#include <vector>
#include <ga/ga.h>

using namespace std;

int main(int argc, char* argv[])
{
    // cout << "HELLO WORLD" << endl;

    cout << "evolving ga" << endl;
    GA<BitGeno, SUS> ga = GA<BitGeno, SUS>(30, 25, 3);
    ga.setCrossoverChance(0.2f);
    ga.setMutationChance(0.05f);
    ga.setSelectionPercent(0.25f);
    ga.evolve();

    vector<BitGeno*> best = ga.getBestGenInds();
    cout << "Best Individual:" << endl;
    best[best.size()-1]->print();
    cout << "fitness: " << best[best.size()-1]->evaluateFitness() << endl;

    // TODO
    // need to write conformance tests
}
