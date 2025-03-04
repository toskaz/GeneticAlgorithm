#pragma once
#include  <iostream>
#include "GroupingEvaluator.h"
#include "Point.h"
#include <random>
#include <utility>
using namespace NGroupingChallenge;

class Individual
{
private:

	int genotypeSize;
	int groupCount;
	vector<int> genotype;

public:
	// jak wszystkie typy pol spelniaja rule of 5 to komp wygeneruje destruktor i copy i reszte 
	Individual(std::mt19937& gen, int groupCount, int genotypeSize);
	Individual(int genotypeSize, int GroupCount);

	const vector<int>& genotypeGet() const;

	double individualFitness(CGroupingEvaluator& evaluator) const;

	void mutate(std::mt19937& gen, double mutProb);
	pair< Individual, Individual > crossInidividual(std::mt19937& gen, const Individual& other, double CrossProb) const;
};


class BestIndividual {
private:

	double bestFitness;
	Individual bestIndividual;

public: 
	BestIndividual() : bestFitness(DBL_MAX), bestIndividual(Individual(1,1)) {};

	double fitnessGet() const {	return bestFitness; }

	const Individual& bestIndividualGet() const { return bestIndividual; }

	void assignBestSolution(const  Individual& newIndividual, double newFitnessValue) {
		if (bestFitness > newFitnessValue) {
			bestFitness = newFitnessValue;
			bestIndividual = newIndividual;
		}
	}
};

