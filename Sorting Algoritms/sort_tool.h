#pragma once

#include <cstddef>
#include <algorithm>

void ArrToMaxHeap(int* const arr_to_parse, const std::size_t arr_size);
void BinaryTreeGoOneNodeIndexUp(std::size_t& index);
int GetDigitAtIndex(int input_num, int digit_index);
void CountingSortWidthDigitAtIndex(int* const arr_to_sort, const std::size_t arr_to_sort_size, const signed int index_to_sort_by = -1);