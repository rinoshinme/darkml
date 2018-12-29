#ifndef DARKML_TEST_LINEAR_REGRESSION_H
#define DARKML_TEST_LINEAR_REGRESSION_H

#include "../models/linear_regression.h"
#include "../dataset/samples.h"
#include <iostream>

namespace darkml
{
	inline void testLinearRegression()
	{
		Dataset<float> train = generateSampleRegression(100);
		Dataset<float> test = generateSampleRegression(40);
		train.setBatchNum(100); // single batch training

		LinearRegression lr(20);

		float l_before = lr.loss(test);
		std::cout << "------- before -------------\n";
		std::cout << "weight: \n";
		std::cout << lr.weight << std::endl;
		std::cout << "bias: \n";
		std::cout << lr.bias << std::endl;
		std::cout << "loss: \n";
		std::cout << l_before << std::endl;

		lr.train(train);

		float l_after = lr.loss(test);
		std::cout << "------- after -------------\n";
		std::cout << "weight: \n";
		std::cout << lr.weight << std::endl;
		std::cout << "bias: \n";
		std::cout << lr.bias << std::endl;
		std::cout << "loss: \n";
		std::cout << l_after << std::endl;
	}
}

#endif
