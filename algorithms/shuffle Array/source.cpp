#include <iostream>
#include <cstdlib>
#include <ctime> 
using namespace std;

int randomInteger(int a, int b)
{
	return rand() % (b-a+1) + a;
}
template<typename T>
void shuffleArray(T a[], int N)
{
	for (int i = 1; i < N; i++)
	{
		swap(a[0], a[randomInteger(i, N - 1)]);
	}
}


int main()
{
	srand(time(0));
	int arr[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
	shuffleArray<int>(arr, 20);
	for (int val : arr)
	{
		cout << val << ' ';
	}
}
