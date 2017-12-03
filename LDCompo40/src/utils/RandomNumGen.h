#pragma once

#include <random>

class RandomNumGen
{
public:
	static RandomNumGen& getInstance()
	{
		static RandomNumGen instance;
		//instance.m_generator.seed(1337);
		return instance;
	}

	void init(int seed);
	int generateInteger(int min, int max);
	float generateFloat(float min, float max);

private:
	std::mt19937 m_generator;
	std::uniform_int_distribution<int> m_intDistributor;
	int m_seed;
};

