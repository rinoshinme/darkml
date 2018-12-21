/*
 * implementation of various machine learning algorithms
 */
#include <iostream>
#include "darkml.h"
using namespace darkml;

int main()
{
	// test_array();
	// test_dataset();
	// testLinearRegression();
	// testHeap();
	test_knn();

	std::shared_ptr<int> ptr;
	std::cout << ((ptr == nullptr) ? "true" : "false") << std::endl;

	std::cout << "finished...\n";
	std::getchar();
}
