#include <iostream>
using namespace std;

template <class T>
void Merge(T* firstArr, size_t firstSize, T* secondArr, size_t secondSize, T* resultArr)
{
	size_t resultIter = 0;
	size_t firstIter = 0;
	size_t 
}

template <class T>
void MergeSortStep(T* pArr, size_t Size, T* pBuffer)
{
	if (Size <= 1)
		return;

	size_t middle = Size / 2;

	MergeSortStep(pArr, middle, pBuffer);

}

template <class T>
void MergeSort(T* pArr, size_t Size)
{
	if (!pArr || size == 0)
		return;

	T* pBuffer = new T[Size];

	MergeSortStep(pArr, Size, pBuffer);

	delete[] pBuffer;
}