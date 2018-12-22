#ifndef DARKML_DECISION_TREE_H
#define DARLML_DECISION_TREE_H

#include "estimator.h"
#include <set>

namespace darkml
{
	enum class DTNodeType
	{
		CONTINUOUS,
		DISCRETE,
		UNKNOWN,
	};

	struct DTNode
	{
		DTNodeType type;
		// for training
		std::vector<int> feature_indices;
		std::vector<int> sample_indices;
		// index of feature for decision, -1 for leaf nodes.
		int index;
	};

	struct DTNodeContinous : public DTNode
	{
		// binary thresholding for continuous features
		float threshold;
	};

	struct DTNodeDiscrete : public DTNode
	{
		// multi-part separation for discrete features
	};

	// simple decision tree implementation
	class DecisionTree : public Estimator<float>
	{
	private:
		DTNode* root;
		std::vector<bool> discrete_flags;

	public:
		DecisionTree() {}
		DecisionTree(const std::vector<bool>& flags) : discrete_flags(flags) {}
		void setDiscreteFlags(const std::vector<bool>& flags) { discrete_flags = flags; }

		void train(const Dataset<float>& dataset);
	private:
		// -1 for no decision
		int findBestIndex(const Dataset<float>& dataset, const std::vector<int>& sample_indices, const std::vector<int>& feature_indices);

	};
}

#endif
