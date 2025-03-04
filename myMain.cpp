#include "GaussianGroupingEvaluatorFactory.h"
#include "GroupingEvaluator.h"
#include "Optimizer.h"
#include "Individual.h"
#include "GeneticAlgorithm.h"
#include <random>
using namespace NGroupingChallenge;

int main()
{
    const int popSize = 20; 
    const int groupCount = 5;
    const int genotypeSize = 20;
    const double crossProb = 0.8; //0.6
    const double mutProb = 0.1; //0.1


    CGaussianGroupingEvaluatorFactory c_evaluator_factory(groupCount, genotypeSize);

    c_evaluator_factory
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0);

    CGroupingEvaluator* pc_evaluator = c_evaluator_factory.pcCreateEvaluator(0);

    GeneticAlgorithm gen_alg(*pc_evaluator, popSize, genotypeSize, groupCount, crossProb, mutProb);

    gen_alg.runAll(100);

    const BestIndividual& bestSolution = gen_alg.getBestSolution();
    const Individual& bestIndividual = bestSolution.bestIndividualGet();

    std::cout << "Best Genotype: ";
    for (int gene : bestIndividual.genotypeGet()) {
        std::cout << gene;
    }

    std::cout << "\nBest Fitness: ";
    std::cout << bestSolution.fitnessGet() << std::endl;

    std::cout << std::endl;

    delete pc_evaluator;

    return 0;
}