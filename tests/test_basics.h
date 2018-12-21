#ifndef DARKML_TEST_BASICS_H
#define DARKML_TEST_BASICS_H

namespace darkml
{
	struct Add1 : public PointFunction1 < float >
	{
		virtual float operator()(float val) { return val + 1.0f; }
	};

	inline void test_array_apply()
	{
		Array<float> arr(3, 3);
		constantInit(arr, 0.1f);
		std::cout << arr << std::endl;
		arr = arr.apply(Add1());
		std::cout << arr << std::endl;
	}

	inline void test_array()
	{
		Array<float> arr(5, 5);
		for (int r = 0; r < 5; ++r)
		{
			for (int c = 0; c < 5; ++c)
			{
				arr(r, c) = float((r + 1) * (c + 1));
			}
		}

		Array<float> row1 = arr.row(1);
		for (int i = 0; i < 5; ++i)
			std::cout << row1[i] << ", ";
		std::cout << std::endl;

		Array<float> col1 = arr.col(2);
		for (int i = 0; i < 5; ++i)
			std::cout << col1[i] << ", ";
		std::cout << std::endl;

		Array<int> intArr = arr.convert<int>();
		for (int i = 0; i < 5; ++i)
			std::cout << intArr(i, i) << ", ";

		intArr.makePrivate();
	}

	inline void test_dataset()
	{
		Dataset<float> dataset = generateSampleRegression(10);
		// print data
		for (int r = 0; r < dataset.data.rows; ++r)
		{
			for (int c = 0; c < dataset.data.cols; ++c)
				std::cout << dataset.data(r, c) << ", ";
			std::cout << std::endl;
		}
		std::cout << "-----------------------------------------------------\n";
		// print targets
		for (int r = 0; r < dataset.target.rows; ++r)
		{
			for (int c = 0; c < dataset.target.cols; ++c)
				std::cout << dataset.target(r, c) << ", ";
			std::cout << std::endl;
		}
	}
}

#endif
