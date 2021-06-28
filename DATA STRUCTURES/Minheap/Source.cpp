#include <iostream>
using namespace std;

template<typename T>
class MinHeap
{
public:
	T* data;
	int nodesCount = 0;
	int maxHeight;
	int capacity;
	MinHeap(int h = 5);
	void insert(T val);
	T removeMin();
	T getMin();
	bool empty();
};

int main()
{
	MinHeap<int> h;
	h.insert(6);
	h.insert(4);
	h.insert(8);
	h.insert(3);
	h.insert(9);
	h.insert(13);
	h.insert(2);
	h.insert(5);
	h.insert(10);
	h.insert(11);
	h.insert(14);
	h.insert(1);
	h.insert(12);
	int n = 0;
	while (!h.empty())
		cout << h.removeMin() << endl;
}

template<typename T>
MinHeap<T>::MinHeap(int h)
{
	maxHeight = h;
	capacity = pow(2, maxHeight) - 1;
	data = new T[capacity];
}

template<typename T>
void MinHeap<T>::insert(T val)
{
	if (nodesCount == capacity)
	{
		return;
	}
	data[nodesCount] = val;
	int i = nodesCount;
	while (i > 0 && (data[i] < data[(i - 1) / 2]))
	{
		swap(data[i], data[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
	nodesCount++;
}

template<typename T>
T MinHeap<T>::removeMin()
{
	if (nodesCount == 0)
	{
		exit(0);
	}
	T retVal = data[0];
	data[0] = data[nodesCount - 1];
	int i = 0;
	while ((i < ((nodesCount - 1) / 2)) && (data[i] > data[2 * i + 1] || data[i] > data[2 * i + 2]))
	{
		if ((data[i] > data[2 * i + 1]) && (data[i] > data[2 * i + 2]))
		{
			swap(data[i], (data[2 * i + 1] <= data[2 * i + 2] ? data[2 * i + 1] : data[2 * i + 2]));
			i = (data[2 * i + 1] <= data[2 * i + 2] ? (2 * i + 1) : (2 * i + 2));
		}
		else if (data[i] > data[2 * i + 1])
		{
			swap(data[i], data[2 * i + 1]);
			i = i * 2 + 1;
		}
		else //if (data[i] > data[2 * i + 2])
		{
			swap(data[i], data[2 * i + 2]);
			i = i * 2 + 2;
		}
	}
	nodesCount--;
	return retVal;
}

template<typename T>
T MinHeap<T>::getMin()
{
	if (nodesCount == 0)
	{
		exit(0);
	}
	return data[0];
}

template<typename T>
inline bool MinHeap<T>::empty()
{
	return nodesCount == 0 ? true : false;
}
