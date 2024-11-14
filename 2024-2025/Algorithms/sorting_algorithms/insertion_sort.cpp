#include <iostream>
#include <utility>
using namespace std;

//Binary Search - iterative
template <class T>
int binarySearch(const T* arr, unsigned len, const T& searched)
{
	int left = 0;
	int right = len - 1;

	while (left <= right)
	{
		int mid = left + (right - left) / 2;

		if (arr[mid] == searched)
			return mid;

		if (arr[mid] > searched)
			right = mid - 1;
		else
			left = mid + 1;
	}

	return -1;
}

//iterative for  Iterator
template <typename Iterator, typename T>
Iterator binarySearch(Iterator begin, Iterator end, const T& value)
{
	Iterator left = begin;
	Iterator right = end;

	while (left < right)
	{
		Iterator mid = left + std::distance(left, right) / 2;

		if (*mid == value)
			return mid;

		if (*mid > value)
			right = mid - 1;
		else
			left = mid + 1;
	}

	return end;
}

//BS recursive
template <class T>
int binarySearch(const T* arr, unsigned len, const T& searched)
{
	if (len == 0)
		return -1;

	int mid = len / 2;

	if (arr[mid] == searched)
		return mid;

	if (arr[mid] < searched)
	{
		int result = binarySearch(arr + mid + 1, len - mid - 1, searched);
		return (result == -1) ? -1 : result + mid + 1;
	}
	else
		return binarySearch(arr, mid, searched);
}

//BS recursive for Iterator
template <typename Iterator, typename T>
int binarySearch(Iterator left, Iterator right, const T& value)
{
	if (left >= right)
		return right;

	Iterator mid = left + std::distance(left, right) / 2;

	if (*mid == value)
		return mid;

	if (*mid > value)
		return binarySearch(left, mid, value);
	else
		return binarySearch(mid + 1, right, value);
}

//bubbleSort
template <class T>
void bubbleSort(T* arr, unsigned len)
{
	unsigned end = len - 1;

	for (size_t i = 0; i < len - 1; i++)
	{
		unsigned lastSwappedIndex = 0;

		for (size_t j = 0; j < end; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
				lastSwappedIndex = j;
			}
		}

		if (lastSwappedIndex == 0)
			return;
		end = lastSwappedIndex;
	}
}

//insertion sort
template <class T>
void insertionSort(T* arr, unsigned len)
{
	for (size_t i = 0; i < len; i++)
	{
		T element = arr[i];
		unsigned index = i - 1;

		while (index >= 0 && arr[index] > element)
		{
			arr[index + 1] = arr[index];
			--index;
		}

		arr[index] = element;
	}
}