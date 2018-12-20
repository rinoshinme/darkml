#ifndef DARKML_DATASET_H
#define DARKML_DATASET_H

#include "../array.h"
#include "../random.h"

namespace darkml
{
	enum class DatasetType
	{
		ALL,
		TRAIN,
		TEST,
	};

	// base class for datasets
	template<typename T>
	struct Dataset
	{
	public:
		Array<T> data;
		Array<T> target;
		int batch_size;
		int pos;

	public:
		Dataset()
		{
			batch_size = 1;
			pos = 0;
		}

		void setBatchNum(int batch_number)
		{
			int num_samples = data.rows;
			batch_size = num_samples / batch_number;
		}

		void setBatchSize(int batch_size)
		{
			this->batch_size = batch_size;
		}

		bool getBatch(Array<T>& x, Array<T>& y);
		// bool getBatchData(Array<T>& x);
		// bool getBatchTarget(Array<T>& y);
		void reset() { pos = 0; }

	private:
		void shuffle();
	};

	template<typename T>
	bool Dataset<T>::getBatch(Array<T>& x, Array<T>& y)
	{
		if (pos + batch_size > data.rows)
			shuffle();

		x = data.batch(pos, batch_size);
		y = target.batch(pos, batch_size);
		pos += batch_size;
		return true;
	}

	template<typename T>
	void Dataset<T>::shuffle()
	{
		Random rng;
		std::vector<int> indices = rng.randomPermute(0, data.rows);
		data.shuffle(indices);
		target.shuffle(indices);
	}
}

#endif
