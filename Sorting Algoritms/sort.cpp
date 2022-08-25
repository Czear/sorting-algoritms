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

	void Insertion(int* const arr_to_sort, const std::size_t arr_to_sort_size) {
		for (std::size_t sorted_boundary{ 1 }; sorted_boundary < arr_to_sort_size; sorted_boundary++) {

			for (std::size_t scanner_index{ sorted_boundary }; scanner_index; scanner_index--) {

				if (arr_to_sort[scanner_index] > arr_to_sort[scanner_index - 1]) {
					break;
				}

				std::swap(arr_to_sort[scanner_index - 1], arr_to_sort[scanner_index]);
			}
		}
	}

	void Merge(int* const arr_to_sort, const std::size_t arr_to_sort_size) {
		if (arr_to_sort_size == 1) {
			return;
		}

		/* Create subarrays */
		const std::size_t lower_part_size = arr_to_sort_size / 2;
		const std::size_t upper_part_size = arr_to_sort_size - lower_part_size;


		int* lower_part = new int[lower_part_size];
		int* upper_part = new int[upper_part_size];

		/* Fill subarrays with data */
		for (std::size_t i{}; i < arr_to_sort_size; i++) {
			bool use_lower_part_arr = (i < lower_part_size);
			int* array_to_fill = use_lower_part_arr ? lower_part : upper_part;
			std::size_t index_to_update = use_lower_part_arr ? i : i - lower_part_size;

			int* address_to_override = array_to_fill + index_to_update;

			*address_to_override = arr_to_sort[i];
		}

		/* Sort sub arrays */
		Merge(lower_part, lower_part_size);
		Merge(upper_part, upper_part_size);

		/* Update input array with sorted data */
		std::size_t lower_part_index{};
		std::size_t upper_part_index{};

		while (lower_part_index < lower_part_size && upper_part_index < upper_part_size) {
			bool get_next_value_from_lower_part_vector = lower_part[lower_part_index] <= upper_part[upper_part_index];

			arr_to_sort[lower_part_index + upper_part_index] = get_next_value_from_lower_part_vector ? lower_part[lower_part_index] : upper_part[upper_part_index];

			(get_next_value_from_lower_part_vector ? lower_part_index : upper_part_index)++;
		}

		/* Use unfinished array */
		bool is_lower_vector_unfinished = lower_part_index != lower_part_size;
		int* unfinished_vector = is_lower_vector_unfinished ? lower_part : upper_part;
		const std::size_t* unfinished_vector_size = is_lower_vector_unfinished ? &lower_part_size : &upper_part_size;
		std::size_t* unfinished_counter = is_lower_vector_unfinished ? &lower_part_index : &upper_part_index;

		while ((*unfinished_counter) < (*unfinished_vector_size)) {
			arr_to_sort[lower_part_index + upper_part_index] = unfinished_vector[*unfinished_counter];
			(*unfinished_counter)++;
		}

		/* Clear sub arrays from memory */
		delete[] lower_part;
		delete[] upper_part;
	}

}