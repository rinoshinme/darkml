
adopt scikit-learn style estimator objects

ģ��ṹ

core
	�������ݽṹ
		array, matrix, common
	�������ݽṹ
		graph, heap, 
	��ѧ����������
		math, random, geometry
	ϵͳ����������
		throw_assert

dataset - ����coreģ��
	���ݼ�IO

stat - ����coreģ��
	ͳ��ר�ź���

preprocessing
	����Ԥ������
		dim_reduction
		...

models - ����core��statģ��
	ģ�͸�������
		distance functions
		weight initialization 
		activation functions

	����ģ��
		linear models
		clustering
		classification

	�Ż�����
	
visualization - ����coreģ��
	���ݳ־û�
	ͼ����ʾ

tests
	ģ�����

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
		C4.5 -> ѡ��������ھ�ֵ���������������������ԡ�
		gini index
		CART
		pruning
			pre-pruning
			post-pruning
		continuous feature: bi-partition
			ͬһ�������������Խ��ж�λ��֡�
	neural networks -> back prop...

1. point cloud classification using grid responses of rbf kernels with respect 
to all points.
