#pragma once

#include <cstddef>
#include <algorithm>

namespace sort {
	void Bubble(int* const arr_to_sort, const std::size_t arr_to_sort_size);
	void Counting(int* const arr_to_sort, const std::size_t arr_to_sort_size);
	void Heap(int* const arr_to_sort, const std::size_t arr_to_sort_size);
}