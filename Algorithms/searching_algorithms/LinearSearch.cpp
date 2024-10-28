#include <iostream>
using namespace std;

int linearSearch(const int* arr, int len, int searched)
{
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == searched)
            return i;//returns the index of the searched number
    }

    return -1;// returns -1 if the searched number is not found
}

int main()
{
    int arr[] = { 1, 2, 3, 4, 5, 6, 7 };

    cout << linearSearch(arr, 7, 10);
}
