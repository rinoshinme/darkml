
adopt scikit-learn style estimator objects

模块结构

core
	基本数据结构
		array, matrix, common
	辅助数据结构
		graph, heap, 
	数学辅助函数库
		math, random, geometry
	系统辅助函数库
		throw_assert

dataset - 依赖core模块
	数据集IO

stat - 依赖core模块
	统计专门函数

preprocessing
	数据预处理函数
		dim_reduction
		...

models - 依赖core和stat模块
	模型辅助功能
		distance functions
		weight initialization 
		activation functions

	各种模型
		linear models
		clustering
		classification

	优化方法
	
visualization - 依赖core模块
	数据持久化
	图像显示

tests
	模块测试

1. basic structures
	array -> 1d data
	matrix -> 2d data
	dataset -> a pair of matrix
	Tensor -> general data
		- consider NA values in data

2. models
	linear regression
	ridge regression
	decision tree
		entropy, entropy gain
		gain ratio
		ID3
		C4.5 -> 选择增益大于均值的属性中增益率最大的属性。
		gini index
		CART
		pruning
			pre-pruning
			post-pruning
		continuous feature: bi-partition
			同一个连续特征可以进行多次划分。
	neural networks -> back prop...

1. point cloud classification using grid responses of rbf kernels with respect 
to all points.
