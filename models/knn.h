#ifndef DARKML_KNN_H
#define DARKML_KNN_H

#include "estimator.h"
#include "distance.h"
#include "../core/common.h"
#include "../core/heap.h"

namespace darkml
{
	template<typename DistanceMetric = EuclidDistance<float> >
	class KNNClassifier : public Estimator<float>
	{
	private:
		// for topK finding
		struct IndexDistancePair
		{
			int index;
			float dist;
		};

		struct IndexDistancePairGreater
		{
			bool operator()(IndexDistancePair& p1, IndexDistancePair& p2)
			{
				return (p1.dist > p2.dist);
			}
		};

	private:
		Array<float> data;
		// targets are represented by floats 0.0f, 1.0f, ...
		Array<float> target; // shape [n, 1]
		int num_classes;
		DistanceMetric metric; // default construction
		int k;

	public:
		KNNClassifier(int nclasses, int k = 1) : num_classes(nclasses), k(k) { }

		void train(const Dataset<float>& dataset);

		Array<float> predict(const Array<float>& x);

		// not clear what is loss for knn, calculate accuracy instead
		float loss(const Dataset<float>& dataset);

	private:
		// return class label of a single vector
		int findKNearestLabel(const Array<float>& vec);

		int findNumClasses(const Array<float>& target);
	};

	template<typename DistanceMetric>
	void KNNClassifier<DistanceMetric>::train(const Dataset<float>& dataset)
	{
		data = dataset.data;
		throw_assert(data.rows > k, "number of samples should be larget than k");

		target = dataset.target;
		num_classes = findNumClasses(target);
	}

	template<typename DistanceMetric>
	Array<float> KNNClassifier<DistanceMetric>::predict(const Array<float>& x)
	{
		int num_samples = x.rows;
		Array<float> result(num_samples, 1);
		for (int i = 0; i < num_samples; ++i)
		{
			int label = findKNearestLabel(x.row(i));
			result[i] = static_cast<float>(label);
		}
		return result;
	}

	template<typename DistanceMetric>
	float KNNClassifier<DistanceMetric>::loss(const Dataset<float>& dataset)
	{
		int num_samples = dataset.data.rows;
		if (num_samples == 0)
			return 0.0f;

		Array<float> target_pred = predict(dataset.data);
		int num_correct = 0;
		for (int i = 0; i < num_samples; ++i)
		{
			int truth = int(dataset.target[i]);
			int pred = int(target_pred[i]);
			if (truth == pred)
				num_correct += 1;
		}
		return num_correct * 1.0f / num_samples;
	}

	template<typename DistanceMetric>
	int KNNClassifier<DistanceMetric>::findNumClasses(const Array<float>& target)
	{
		// calculate number of classes
		throw_assert(target.cols == 1, "Classification target should have length 1, representing the class label");
		int num_samples = target.rows;
		int max_label = 0;
		for (int i = 0; i < num_samples; ++i)
		{
			int v = static_cast<int>(target[i]);
			if (v > max_label)
				max_label = v;
		}
		return max_label + 1;
	}

	template<typename DistanceMetric>
	int KNNClassifier<DistanceMetric>::findKNearestLabel(const Array<float>& vec)
	{
		throw_assert(vec.rows == 1, "input should be single vector sample");
		int num_training = data.rows;
		std::vector<IndexDistancePair> dists(num_training);
		for (int i = 0; i < num_training; ++i)
		{
			dists[i].index = i;
			dists[i].dist = metric(vec, data.row(i));
		}

		// sort using heap sort
		Heap<IndexDistancePair, IndexDistancePairGreater> heap(dists);
		std::vector<IndexDistancePair> topK = heap.getTopK(k);

		// get index with max frequency
		std::vector<int> hist(num_classes);
		for (size_t k = 0; k < topK.size(); ++k)
		{
			int index = int(target[topK[k].index]);
			hist[index] += 1;
		}

		int max_index = 0;
		int max_val = 0;
		for (size_t k = 0; k < num_classes; ++k)
		{
			if (hist[k] > max_val)
			{
				max_index = int(k);
				max_val = hist[k];
			}
		}

		return max_index;
	}

}

#endif
