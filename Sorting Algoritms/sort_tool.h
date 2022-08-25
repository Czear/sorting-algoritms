#pragma once

#include <cstddef>
#include <algorithm>

int GetDigitAtIndex(int input_num, int digit_index);
void CountingSortWidthDigitAtIndex(int* const arr_to_sort, const std::size_t arr_to_sort_size, const signed int index_to_sort_by = -1);