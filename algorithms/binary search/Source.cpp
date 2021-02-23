#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;

template <class T>
void randomizeArray(T a[], int size) 
{
	//srand(time(0));
	for (int i = 0; i < size; i++)
	{
		a[i] = rand() % 1001;
	}
}

template <class T>
void display(T a[], int size)
{
	for (int i = 0; i < size; i++)
		cout << a[i] << endl;
}

template <class T>
bool binarySearch(T* a, int start, int end, T key)
{
	if (start > end)
	{
		return false;
	}
	int mid = (start + end) / 2;
	if (a[mid] == key)
	{
		return true;
	}
	else if (a[mid] < key)
	{
		return binarySearch(a, mid + 1, end, key);
	}
	else
	{
		return binarySearch(a, start, mid - 1, key);
	}
}

int main()
{
	const int N = 100;
	int a[N];
	
	randomizeArray<int>(a, N);
	
	sort<int*>(a, a + N);

	display<int>(a, N);

	cout << binarySearch<int>(a, 0, N, 952);
}