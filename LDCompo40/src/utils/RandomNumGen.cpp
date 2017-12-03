#include "RandomNumGen.h"

void RandomNumGen::init(int seed)
{
	m_generator.seed(m_seed);
}

int RandomNumGen::generateInteger(int min, int max)
{
	std::uniform_int_distribution<int> rand(min, max);
	return rand(m_generator);
}

float RandomNumGen::generateFloat(float min, float max)
{
	std::uniform_real_distribution<float> rand(min, max);
	return rand(m_generator);
}
