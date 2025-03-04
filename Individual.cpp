#include "Individual.h"
#include "GeneticAlgorithm.h"
#include <random>
#include <vector>
using namespace NGroupingChallenge;

// jak wszystkie typy pol spelniaja rule of 5 to kompilator wygeneruje destruktor i copy i reszte 
Individual::Individual(std::mt19937& gen, int groupCount, int genotypeSize) : genotypeSize(genotypeSize), groupCount(groupCount) {
	std::uniform_int_distribution<> distribution(1, groupCount);
	genotype.reserve(genotypeSize);
	for (int i = 0; i < genotypeSize; i++) {
		genotype.push_back( distribution(gen));
	}
}

Individual::Individual(int genotypeSize, int groupCount) : genotypeSize(genotypeSize), groupCount(groupCount) {
	genotype.reserve(genotypeSize);
	for (int i = 0; i < genotypeSize; i++) {
		genotype.push_back(1);
	}
}

const vector<int>& Individual::genotypeGet() const{
	return genotype;
}

double Individual::individualFitness(CGroupingEvaluator& evaluator) const {
	return evaluator.dEvaluate(genotype);
}

pair< Individual, Individual > Individual::crossInidividual(std::mt19937& gen, const Individual& other, double crossProb) const {
	std::uniform_real_distribution<> distribution(0,1);
	double thisProb = distribution(gen);
	if (thisProb < crossProb) {
		std::uniform_int_distribution<> groupCountGen(1, genotypeSize -1);
		int typeOfCrossing = groupCountGen(gen);
		Individual child1 = *this; 
		Individual child2 = other;
		std::swap_ranges(child1.genotype.begin(), child1.genotype.begin() + typeOfCrossing, child2.genotype.begin());
		return { child1, child2 };
	}else{
		return { *this, other };
	}
};

void Individual::mutate(std::mt19937& gen, double mutProb){

	std::uniform_real_distribution<> distribution(0, 1);
	std::uniform_int_distribution<> mutationDistribution(1, groupCount);
	for (int i = 0; i < genotypeSize; i++) {
		double thisProb = distribution(gen);
		if (thisProb < mutProb) {
			genotype[i] = mutationDistribution(gen);
		}
	}
}