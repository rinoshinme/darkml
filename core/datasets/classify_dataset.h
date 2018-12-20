#ifndef DARKML_CLASSIFY_DATASET_H
#define DARKML_CLASSIFY_DATASET_H

#include "dataset.h"

namespace darkml
{
	template<typename T>
	class ClassifyDataset : public Dataset<T>
	{
	private:
		int num_classes;

	public:
		ClassifyDataset(int nclasses = -1)
			: Dataset()
		{
			num_classes = nclasses;
		}

		Array<T> getOnehotTarget()
		{
			throw_assert(target.cols == 1, "Classification target should have length 1, representing the class label");
			int num_samples = target.rows;
			if (num_classes == -1)
			{
				// calculate max label
				int max_label = 0;
				for (int i = 0; i < num_samples; ++i)
				{
					int v = static_cast<int>(target[i]);
					if (v > max_label)
						max_label = v;
				}
				num_classes = max_label + 1;
			}

			Array<T> one_hot_target(num_samples, num_classes);
			// constantInit(one_hot_target, 0.0);
			for (int i = 0; i < num_samples; ++i)
			{
				int v = static_cast<int>(target[i]);
				one_hot_target(i, v) = 1;
			}
			return one_hot_target;
		}



	};
}

#endif
