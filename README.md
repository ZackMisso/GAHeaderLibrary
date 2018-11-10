# GAHeaderLibrary

A small header library for quick integration of genetic algorithms into other
C++ projects.

## Currently Supported GenoType Representations
* Bitstring representation (BitGeno)
* real valued representation (FloatGeno)

## Currently Supported Selection Techniques
* Stochastic Universal Sampling

## How To Integrate

### Implement your GenoType

```
class YourClass : public Geno
{
    void initializeRandom(pcg32&) {}
    Pheno* generatePhenotype() {}
    Geno* copy() {}
    void mutate(pcg32&, float) {}
    Geno* crossover(Geno*, pcg32&, float) {}
};
```

### Implement your PhenoType
```
class YourPheno : public Pheno
{
    double evaluateFitness() {}
};
```

### Run the GA
```
GA<YourGeno, SUS> ga = GA<YourGeno, SUS>();
ga.evolve();
Geno* best = ga.getBestGenInds()[0];

cout << "Best Individual: " << endl;
best->print();
cout << "Best Fitness: " << best->evaluateFitness() << endl;
```

## Authors

* **Zack Misso**
