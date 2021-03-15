#include <iostream>
using namespace std;

template <typename T>
int binarySearch(T* arr, int size, T height)
{
	int start = 0, end = size - 1;
	int mid;
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (arr[mid] == height)
		{
			return mid;
		}
		else if (arr[mid] < height)
		{
			start = mid + 1;
		}
		else
		{
			end = mid - 1;
		}
	}
	return -1;

}
int main()
{
	int arr1[30];
	int i = 0;
	for (int& val : arr1)
	{
		val = i++;
	}
	while (i >= 0)
	{
		cout << binarySearch<int>(arr1, 30, i--) << endl;
	}
}