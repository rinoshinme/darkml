#ifndef DARKML_TEST_LOGISTIC_REGRESSION_H
#define DARKML_TEST_LOGISTIC_REGRESSION_H

#include "../models/logistic_regression.h"
#include "../dataset/samples.h"

namespace darkml
{
	inline void test_logistic()
	{
		std::vector<std::pair<float, float> > means;
		std::vector<float> sigmas;
		std::vector<int> nums_train;
		std::vector<int> nums_test;

		means.push_back(std::make_pair(0.0f, 0.0f));
		means.push_back(std::make_pair(5.0f, 5.0f));
		sigmas.push_back(3.0f);
		sigmas.push_back(3.0f);
		nums_train.push_back(200);
		nums_train.push_back(200);
		nums_test.push_back(30);
		nums_test.push_back(30);
		Dataset<float> train_set = generateGaussianMixture(means, sigmas, nums_train);
		Dataset<float> test_set = generateGaussianMixture(means, sigmas, nums_test);

		test_set.setBatchNum(1);
		train_set.setBatchNum(1);

		LogisticRegression regression(100, 0.1f, 0.1f);

		regression.train(train_set);

		Array<float> pred = regression.predict(test_set.data);

		float accuracy = regression.accuracy(test_set);
		std::cout << "accuracy = " << accuracy << std::endl;
	}
}

#endif
