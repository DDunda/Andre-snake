#pragma once

template<class type>
struct WeightedArray {
	struct Pair {
		type item;
		size_t weight;
	};
	Pair* data;
	size_t size;
	size_t max_weight;

	WeightedArray(size_t size, size_t max_weight) : data(new Pair[size]), size(size), max_weight(max_weight) {}

	~WeightedArray() { delete[] data; }

	type& operator[](size_t weight) {
		for (int i = 0; i < size; i++)
			if (weight < data[i].weight)
				return data[i].item;
	}

	type& PickRandom() {
		size_t rand_weight = rand() % max_weight;
		return (*this)[rand_weight];
	}
	
	void FillRandom(type* arr, size_t n) {
		for (size_t i = 0; i < n; i++)
			arr[i] = PickRandom();
	}
};