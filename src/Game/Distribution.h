#pragma once
#include <random>

using Generator = std::mt19937;

//using Distribution = double(*)(double, double, Generator);
//
//double uniform_distribution(double a, double b, Generator generator) 
//{
//	std::uniform_real_distribution<double> dis;
//}

namespace distribution
{
	//std::random_device rd;
	//Generator default_generator{rd()};
	//std::uniform_real_distribution<double> dis_uniform;
	//std::normal_distribution<double> dis_normal;
	inline std::random_device rd = std::random_device();

	inline double uniform(double a, double b, Generator generator = Generator()) 
	{
		//std::random_device rd;
		generator.seed(rd());
		std::uniform_real_distribution<double> dis_uniform(a,b);
		return dis_uniform(generator);
	}


	inline double normal(double mean, double stddev, Generator generator = Generator())
	{
		//std::random_device rd;
		generator.seed(rd());
		std::normal_distribution<double> dis_normal(mean,stddev);
		return dis_normal(generator);
	}
};

//std::uniform_real_distribution
/*template<typename TDistributionFunction>
using Distribution =*/ 