This is a small header library for a generic genetic algorithm implementation.

Currently supported genotype representations:
    bitstring representation (BitGeno)
    real valued representation (FloatGeno)

Currently supported selection methods:
    Stochastic Universal Sampling (SUS)

How to use this library:

'''
GA<BitGeno, SUS> ga = GA<BitGeno, SUS>(30, 25, 3);
ga.evolve();
Geno* best = ga.getBestGenInds()[0];
cout << "Best Fitness: " << best->evaluateFitness() << endl;
'''

Dummy phenotype implementations are included in this repo for unit testing,
however, to fully utilize this library you must extend the PhenoType class and
GenoType class.

Required genotype methods to extend:
'''
void initializeRandom(pcg32&)
Pheno* generatePhenotype()
Geno* copy()
void mutate(pcg32&, float)
Geno* crossover(Geno*, pcg32&, float)
'''

Required phenotype methods to extend:
'''
double evaluateFitness()
'''
