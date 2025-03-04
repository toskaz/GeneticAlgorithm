#pragma once
#include  <iostream>
#include "Individual.h"
#include "GroupingEvaluator.h"
#include <utility>
#include <random>

using namespace NGroupingChallenge;

class GeneticAlgorithm
{
private:
	CGroupingEvaluator& evaluator; //referencja jest duzo szybsza od smart pointera, nie trzeba robic delete jak przy ptr
	int popSize;
	int genotypeSize;
	int groupCount;

	double crossProb;
	double mutProb;
	std::vector<Individual> population;

	std::random_device random; 
	std::mt19937 gen; 

	BestIndividual Best; 

	void generateFirstPopulation();
	void runIteration();
	const Individual& findParent() ;

public:
	GeneticAlgorithm(CGroupingEvaluator& evaluator, int popSize, int genotypeSize, int groupCount, double crossProb, double mutProb);
	void runAll(int maxIterations);
	const BestIndividual& getBestSolution() const {  return Best; }
};



