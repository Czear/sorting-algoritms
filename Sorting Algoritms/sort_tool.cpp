#include "sort_tool.h"

void ArrToMaxHeap(int* const arr_to_max_heap, const std::size_t arr_to_max_heap_size) {
	for (std::size_t i{}; i < arr_to_max_heap_size; i++) {

		std::size_t current_value_index, parent_node_index;

		current_value_index = parent_node_index = i;

		BinaryTreeGoOneNodeIndexUp(parent_node_index);

		while (arr_to_max_heap[parent_node_index] < arr_to_max_heap[current_value_index]) {
			std::swap(arr_to_max_heap[parent_node_index], arr_to_max_heap[current_value_index]);

			current_value_index = parent_node_index;
			BinaryTreeGoOneNodeIndexUp(parent_node_index);
		}
	}
}

void BinaryTreeGoOneNodeIndexUp(std::size_t& index) {
	if (!index) {
		return;
	}

	index = static_cast<std::size_t>(
		floor(static_cast<double>(index - 1) / 2.0)
	);
}

int GetDigitAtIndex(int input_num, int digit_index) {
	int modulo_divider = static_cast<int>(pow(10.0, 1.0 + digit_index));
	double input_one_digit_fraction = (input_num % modulo_divider) / pow(10.0, digit_index);

	if (input_one_digit_fraction > 0) {
		return static_cast<int>(floor(input_one_digit_fraction));
	}


	return static_cast<int>(ceil(input_one_digit_fraction));
}

void CountingSortWidthDigitAtIndex(int* const arr_to_sort, const std::size_t arr_to_sort_size, const signed int index_to_sort_by) {
	int* const sorted_arr = new int[arr_to_sort_size];
	int lowest_value{};
	int highest_value{};
	bool is_sort_index_valid = index_to_sort_by >= 0;

	auto getArrValueByIndex = [arr_to_sort, index_to_sort_by](std::size_t i) {
		if (index_to_sort_by >= 0) {
			return GetDigitAtIndex(arr_to_sort[i], index_to_sort_by);
		}

		return arr_to_sort[i];
	};

	/* Search for boundries values */
	for (std::size_t i{}; i < arr_to_sort_size; i++) {
		int value_to_check = getArrValueByIndex(i);

		if (value_to_check < lowest_value) {
			lowest_value = value_to_check;
		}

		if (value_to_check > highest_value) {
			highest_value = value_to_check;
		}
	}

	std::size_t count_arr_size = static_cast<std::size_t>(abs(highest_value - lowest_value)) + 1;
	int* count_arr = new int[count_arr_size];
	memset(count_arr, 0, count_arr_size * sizeof(int));

	/* Fill count array */
	for (std::size_t i{}; i < arr_to_sort_size; i++) {
		int index_to_increment = getArrValueByIndex(i) - lowest_value + 1;
		if (index_to_increment == count_arr_size) {
			continue;
		}

		count_arr[index_to_increment]++;
	}

	/* Create value indexes arr at count array */
	for (std::size_t i{}; i < count_arr_size - 1; i++) {
		count_arr[i + 1] += count_arr[i];
	}

	/* Create sorted array */
	for (std::size_t i{}; i < arr_to_sort_size; i++) {
		int element_to_place = arr_to_sort[i];
		int index_to_place_value_at = count_arr[getArrValueByIndex(i) - lowest_value]++;

		sorted_arr[index_to_place_value_at] = element_to_place;
	}

	/* Copy sorted data to input array */
	for (std::size_t i{}; i < arr_to_sort_size; i++) {
		arr_to_sort[i] = sorted_arr[i];
	}

	delete[] sorted_arr;
}