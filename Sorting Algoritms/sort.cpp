#include "sort.h"

namespace sort {
	void Bubble(int* const arr_to_sort, const std::size_t arr_to_sort_size) {
		for (std::size_t max_index{ arr_to_sort_size - 1 }; max_index; max_index--) {
			for (std::size_t search_index{  }; search_index < max_index; search_index++) {

				if (arr_to_sort[search_index] < arr_to_sort[search_index + 1]) {
					continue;
				}
				
				std::swap(arr_to_sort[search_index], arr_to_sort[search_index + 1]);
			}

		}
	}
}