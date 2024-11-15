#include <iostream>
using namespace std;

//Insertion Sort
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
			index--;
		}

		arr[index] = element;
	}
}