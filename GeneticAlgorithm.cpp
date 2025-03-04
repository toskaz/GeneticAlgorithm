#include "GeneticAlgorithm.h"
#include <random>
#include <iostream>
#include <algorithm>

using namespace NGroupingChallenge;

GeneticAlgorithm::GeneticAlgorithm(CGroupingEvaluator& evaluator, int popSize, int genotypeSize, int groupCount, double crossProb, double mutProb)
	: evaluator(evaluator), popSize(popSize), genotypeSize(genotypeSize), groupCount(groupCount), crossProb(crossProb), mutProb(mutProb),
	gen(random()) {
}

void GeneticAlgorithm::runAll(int maxIterations) {
	generateFirstPopulation();

	for (int i = 0; i < maxIterations; i++) {
		runIteration();
		//std::cout << Best.fitnessGet() << std::endl;
	}
}

void GeneticAlgorithm::generateFirstPopulation() {
	population.reserve(popSize);
	for (int i = 0; i < popSize; i++) {
		population.push_back(Individual(gen, groupCount, genotypeSize));
		double fitness = population[i].individualFitness(evaluator);
		Best.assignBestSolution(population[i], fitness);
	}
}

void GeneticAlgorithm::runIteration() {
	std::vector<Individual> nextPopulation;
	nextPopulation.reserve(popSize);

	for (int i = 0; i < ((popSize+1) / 2); i++) {
		const Individual& parent1 = findParent(); 
		const Individual& parent2 = findParent();

		pair<Individual, Individual> children = parent1.crossInidividual(gen, parent2, crossProb);
		nextPopulation.push_back(std::move(children.first));
		if(i != ((popSize+1) / 2 + 1))
			nextPopulation.push_back(std::move(children.second));
	}

	population = std::move(nextPopulation);
	for (int i = 0; i < popSize; i++) {
		population[i].mutate(gen, mutProb);
		double fitness = population[i].individualFitness(evaluator);
		Best.assignBestSolution(population[i], fitness);
	}
}

const Individual& GeneticAlgorithm::findParent() {

	std::uniform_int_distribution<> distribution(0, popSize-1);
	const Individual& i1 = population[distribution(gen)];
	const Individual& i2 = population[distribution(gen)];

	if (i1.individualFitness(evaluator) >= i2.individualFitness(evaluator)) { return i1; }
	else { return i2; }
};

