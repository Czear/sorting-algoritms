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

	void Quick(int* const arr_to_sort, const std::size_t arr_to_sort_size) {
		if (arr_to_sort_size <= 1) {
			return;
		}

		const std::size_t array_mid_point = arr_to_sort_size / 2;

		/*
			Sorting setup (useing first mid and last values):
			lower value placed at index 0
			mid value places at last index
			highest values places at mid index

			mid and highest indexes will be swaped at the end
		*/

		if (arr_to_sort[array_mid_point] < arr_to_sort[0]) {
			std::swap(arr_to_sort[array_mid_point], arr_to_sort[0]);
		}

		if (arr_to_sort[arr_to_sort_size - 1] < arr_to_sort[0]) {
			std::swap(arr_to_sort[arr_to_sort_size - 1], arr_to_sort[0]);
		}

		if (arr_to_sort[array_mid_point] < arr_to_sort[arr_to_sort_size - 1]) {
			std::swap(arr_to_sort[array_mid_point], arr_to_sort[arr_to_sort_size - 1]);
		}

		/* Sorting time */
		int const pivot_value = arr_to_sort[arr_to_sort_size - 1];
		signed int lower_value_search_index{ static_cast<signed int>(arr_to_sort_size) - 2 };
		signed int higher_value_search_index{};

		while (true) {

			/* Search for highest value from left */
			while (higher_value_search_index < (arr_to_sort_size - 1)) {

				if (arr_to_sort[higher_value_search_index] > pivot_value) {
					break;
				}

				higher_value_search_index++;
			}

			/* Search for lowest value from right */
			while (lower_value_search_index) {

				if (arr_to_sort[lower_value_search_index] < pivot_value) {
					break;
				}



				lower_value_search_index--;
			}

			/* Swap if found */
			if (higher_value_search_index < lower_value_search_index) {
				std::swap(arr_to_sort[higher_value_search_index], arr_to_sort[lower_value_search_index]);
				continue;
			}

			break;
		}


		if (higher_value_search_index == arr_to_sort_size) {
			return /* Already sorted */;
		}

		/* Swap back pivot */
		int* const higher_value_search_address = arr_to_sort + higher_value_search_index;
		std::swap(arr_to_sort[higher_value_search_index], arr_to_sort[arr_to_sort_size - 1]);

		/* Sort unsorted things recursively */
		Quick(arr_to_sort, higher_value_search_index);
		Quick(arr_to_sort + higher_value_search_index + 1, arr_to_sort_size - higher_value_search_index - 1);

	}

	void Radix(int* const arr_to_sort, const std::size_t arr_to_sort_size) {
		std::size_t largest_digit_amount{};

		for (std::size_t i{}; i < arr_to_sort_size; i++) {
			std::size_t current_num_digits_amount{};

			while (true) {
				int digit_count_divider = static_cast<int>(pow(10.0, static_cast<double>(current_num_digits_amount)));

				if (floor((arr_to_sort[i] / digit_count_divider)) == 0.0) {
					break;
				}

				current_num_digits_amount++;
			}

			if (current_num_digits_amount <= largest_digit_amount) {
				continue;
			}

			largest_digit_amount = current_num_digits_amount;
		}

		for (std::size_t i{}; i < largest_digit_amount; i++) {
			CountingSortWidthDigitAtIndex(arr_to_sort, arr_to_sort_size, static_cast<int>(i));
		}
	}

	void Selection(int* const arr_to_sort, const std::size_t arr_to_sort_size) {
		for (std::size_t array_index{}; array_index < arr_to_sort_size - 1; array_index++) {
			std::size_t lowest_value_index = array_index;

			for (std::size_t search_index{ array_index + 1 }; search_index < arr_to_sort_size; search_index++) {

				if (arr_to_sort[lowest_value_index] > arr_to_sort[search_index]) {
					lowest_value_index = search_index;
				}


			}

			if (lowest_value_index == array_index) {
				continue;
			}

			std::swap(arr_to_sort[array_index], arr_to_sort[lowest_value_index]);
		}
	}

}