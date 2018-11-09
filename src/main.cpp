// This file is only used for setting up and running tests

#include <iostream>
#include <vector>
#include <ga/ga.h>

using namespace std;

int main(int argc, char* argv[])
{
    // beginning bitgeno test
    cout << "evolving bit ga" << endl;
    GA<BitGeno, SUS> ga = GA<BitGeno, SUS>(30, 25, 3);
    ga.evolve();

    vector<Geno*> best = ga.getBestGenInds();
    cout << "Best Individual:" << endl;
    best[best.size()-1]->print();
    cout << "best fitness: 20" << endl;
    cout << "fitness: " << best[best.size()-1]->evaluateFitness() << endl;

    cout << endl;
    cout << endl;
    cout << endl;

    // beginning float geno test
    cout << "evolving real ga" << endl;
    GA<FloatGeno, SUS> ga2 = GA<FloatGeno, SUS>(30, 25, 3);
    ga2.evolve();

    vector<Geno*> best2 = ga2.getBestGenInds();
    cout << "Best Individual:" << endl;
    best2[best2.size()-1]->print();
    cout << "best fitness: 1.0" << endl;
    cout << "fitness: " << best2[best2.size()-1]->evaluateFitness() << endl;
}
