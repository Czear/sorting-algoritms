#include "sort.h"
#include "sort_tool.h"

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

	void Counting(int* const arr_to_sort, const std::size_t arr_to_sort_size) {
		CountingSortWidthDigitAtIndex(arr_to_sort, arr_to_sort_size);
	}

	void Heap(int* const arr_to_sort, const std::size_t arr_to_sort_size) {
		ArrToMaxHeap(arr_to_sort, arr_to_sort_size);

		for (std::size_t i{}; i < arr_to_sort_size - 1; i++) {
			std::size_t arr_iteration_boundary = arr_to_sort_size - i - 1;

			int left_child_index, right_child_index, current_node_index;
			current_node_index = 0;
			left_child_index = 1;
			right_child_index = 2;



			while (true) {
				/* There is at least one child node to check */
				if (left_child_index > arr_iteration_boundary) {
					break;
				}

				/* Is right child needed to be cheacked to? */
				bool is_right_child_valid = right_child_index <= arr_iteration_boundary;

				/* Is any of children nodes value greater than parrent? */
				if (arr_to_sort[current_node_index] > arr_to_sort[left_child_index] && (!is_right_child_valid || arr_to_sort[current_node_index] > arr_to_sort[right_child_index])) {
					break;
				}

				int index_to_swap_with{};
				if (!is_right_child_valid || (arr_to_sort[left_child_index] > arr_to_sort[right_child_index])) {
					index_to_swap_with = left_child_index;
				}
				else {
					index_to_swap_with = right_child_index;

				}

				std::swap(arr_to_sort[current_node_index], arr_to_sort[index_to_swap_with]);

				current_node_index = index_to_swap_with;
				left_child_index = 2 * current_node_index + 1;
				right_child_index = left_child_index + 1;
			}

			std::swap(arr_to_sort[0], arr_to_sort[arr_iteration_boundary]);
		}

	}

}