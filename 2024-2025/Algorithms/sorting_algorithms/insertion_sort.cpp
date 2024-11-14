#include <iostream>
using namespace std;

//Insertion Sort
template <class T>
void insertionSort(T* arr, int len)
{
	for (int i = 1; i < len; i++)
	{
		T element = arr[i];
		int index = i - 1;

		while (index >= 0 && arr[index] > element)
		{
			arr[index + 1] = arr[index];
			index--;
		}

		arr[index + 1] = element;
	}
}

int main()
{
    int arr[] = { 7, 6, 5, 4, 3, 2, 1 };
	int len = sizeof(arr) / sizeof(arr[0]);

    // Using Insertion Sort
	insertionSort<int>(arr, len);

    cout << "Sorted using Insertion Sort: ";
    for (int i = 0; i < len; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}