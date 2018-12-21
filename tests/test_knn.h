#ifndef DARKML_TEST_KNN_H
#define DARKML_TEST_KNN_H

#include "../models/knn.h"
#include "../core/datasets/samples.h"

namespace darkml
{
	inline void test_knn()
	{
		std::vector<std::pair<float, float> > means;
		std::vector<float> sigmas;
		std::vector<int> nums_train;
		std::vector<int> nums_test;

		means.push_back(std::make_pair(0.0f, 0.0f));
		means.push_back(std::make_pair(5.0f, 5.0f));
		sigmas.push_back(2.0f);
		sigmas.push_back(2.0f);
		nums_train.push_back(200);
		nums_train.push_back(200);
		nums_test.push_back(30);
		nums_test.push_back(30);
		Dataset<float> train_set = generateGaussianMixture(means, sigmas, nums_train);
		Dataset<float> test_set = generateGaussianMixture(means, sigmas, nums_test);

		std::string save_dir("F:/data/");
		std::string train_data_file = save_dir + "train_data.txt";
		std::string train_target_file = save_dir + "train_target.txt";
		train_set.data.toTextFile(train_data_file);
		train_set.target.toTextFile(train_target_file);

		KNNClassifier<EuclidDistance<float> > knn(2, 5);

		knn.train(train_set);
		Array<float> pred = knn.predict(test_set.data);

		std::string test_data_file = save_dir + "test_data.txt";
		std::string test_target_file = save_dir + "test_target.txt";
		std::string test_pred_file = save_dir + "test_pred.txt";
		test_set.data.toTextFile(test_data_file);
		test_set.target.toTextFile(test_target_file);
		pred.toTextFile(test_pred_file);

		float accuracy = knn.loss(test_set);
		std::cout << "accuracy = " << accuracy << std::endl;
	}
}

#endif
