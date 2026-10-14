#pragma once
#include <random>

using Generator = std::mt19937;

using Distribution = double(*)(double, double, Generator);

//std::uniform_real_distribution
/*template<typename TDistributionFunction>
using Distribution =*/ 