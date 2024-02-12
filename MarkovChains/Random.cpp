#include "Random.h"
#include <random>

double randomNumberGen(double lowerBound, double upperBound)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> distribution(lowerBound, upperBound);

	return distribution(mt);
}