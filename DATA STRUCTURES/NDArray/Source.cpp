#include <iostream>
#include <numeric>
using namespace std;

template<typename T>
class NDArray
{
	T* data;
	int noOfDimensions;
	int* sizeOfDimensions;
	int* startingIndex;
	int getRowMajorIndexMapping(const initializer_list<int>&) const;
public:
	NDArray(const initializer_list<int> = {}, const initializer_list<int> = {});
	NDArray(const NDArray<T>&);
	NDArray<T>& operator=(const NDArray<T>&);
	const T* begin();
	const T* end();
	int size();
	int getNumberOfDimentions() const;
	int getDimensionSize(const int) const;
	int getDimensionLowerIndex(const int) const;
	int getDimensionHigherIndex(const int) const;
	bool isIndexBoundsValid(const initializer_list<int>&) const;
	T& operator()(const initializer_list<int>&);
	const T& operator()(const initializer_list<int>&) const;
	~NDArray();
};

template<typename T>
int NDArray<T>::getRowMajorIndexMapping(const initializer_list<int>& set) const
{
	int product = 1;
	int totalSum = 0;
	auto val = set.begin();
	for (int i = 0; i < noOfDimensions; i++)
	{
		product = 1;
		for (int j = i + 1; j < noOfDimensions; j++)
		{
			product *= getDimensionSize(j);
		}
		totalSum += (*val - getDimensionLowerIndex(i)) * product;
		val++;
	}
	return totalSum;
}

template<typename T>
NDArray<T>::NDArray(const initializer_list<int> l1, const initializer_list<int> l2)
{
	noOfDimensions = l1.size();
	if (noOfDimensions == 0)
	{
		startingIndex = sizeOfDimensions = nullptr;
		data = nullptr;
		return;
	}
	sizeOfDimensions = new int[noOfDimensions];
	int i = 0;
	for (int val : l1)
	{
		sizeOfDimensions[i++] = val;
	}
	startingIndex = new int[noOfDimensions];
	auto val = l2.begin();
	for (int j = 0; j < noOfDimensions; j++)
	{
		if (val < l2.end())
		{
			startingIndex[j] = *val;
		}
		else
		{
			startingIndex[j] = 0;
		}
		val++;
	}

	data = new T[size()];
}

template<typename T>
NDArray<T>::NDArray(const NDArray<T>& arr)
{
	noOfDimensions = arr.noOfDimensions;
	if (noOfDimensions == 0)
	{
		sizeOfDimensions = startingIndex = nullptr;
		data = nullptr;
		return;
	}
	sizeOfDimensions = new int[noOfDimensions];
	for (int i =0; i < noOfDimensions;i++)
	{
		sizeOfDimensions[i] = arr.sizeOfDimensions[i];
	}
	startingIndex = new int[noOfDimensions];
	for (int i = 0; i < noOfDimensions; i++)
	{
		startingIndex[i] = arr.startingIndex[i];
	}
	data = new T[size()];
	for (int i = 0; i < size(); i++)
	{
		data[i] = arr.data[i];
	}
}

template<typename T>
NDArray<T>& NDArray<T>::operator=(const NDArray<T>& arr)
{
	if (this == &arr)
	{
		return *this;
	}
	
	this->~NDArray();
	
	noOfDimensions = arr.noOfDimensions;
	if (noOfDimensions == 0)
	{
		return *this;
	}
	sizeOfDimensions = new int[noOfDimensions];
	for (int i = 0; i < noOfDimensions; i++)
	{
		sizeOfDimensions[i] = arr.sizeOfDimensions[i];
	}
	startingIndex = new int[noOfDimensions];
	for (int i = 0; i < noOfDimensions; i++)
	{
		startingIndex[i] = arr.startingIndex[i];
	}
	data = new T[size()];
	for (int i = 0; i < size(); i++)
	{
		data[i] = arr.data[i];
	}
}

template<typename T>
const T* NDArray<T>::begin()
{
	return data;
}

template<typename T>
const T* NDArray<T>::end()
{
	return data + size();
}

template<typename T>
int NDArray<T>::size()
{
	return std::accumulate(sizeOfDimensions, sizeOfDimensions + noOfDimensions, 1, multiplies<int>());
}

template<typename T>
int NDArray<T>::getNumberOfDimentions() const
{
	return noOfDimensions;
}

template<typename T>
int NDArray<T>::getDimensionSize(const int i) const
{
	if (i >= noOfDimensions || i < 0)
	{
		return -1;
	}
	return sizeOfDimensions[i];
}

template<typename T>
int NDArray<T>::getDimensionLowerIndex(const int i) const
{
	if (i >= noOfDimensions || i < 0)
	{
		return -1;
	}
	return startingIndex[i];
}

template<typename T>
int NDArray<T>::getDimensionHigherIndex(const int i) const
{
	if (i >= noOfDimensions || i < 0)
	{
		return -1;
	}
	return startingIndex[i] + getDimensionSize(i) - 1;
}

template<typename T>
bool NDArray<T>::isIndexBoundsValid(const initializer_list<int>& indexSet) const
{
	auto val = indexSet.begin();
	for (int i = 0; i < noOfDimensions; i++)
	{
		if (*val < getDimensionLowerIndex(i) || *val > getDimensionHigherIndex(i))
		{
			return false;
		}
		val++;
	}
	return true;
}

template<typename T>
T& NDArray<T>::operator()(const initializer_list<int>& list)
{
	if (!isIndexBoundsValid(list))
	{
		exit(0);
	}
	return data[getRowMajorIndexMapping(list)];
}

template<typename T>
const T& NDArray<T>::operator()(const initializer_list<int>& list) const
{
	if (!isIndexBoundsValid(list))
	{
		exit(0);
	}
	return data[getRowMajorIndexMapping(list)];
}

template<typename T>
NDArray<T>::~NDArray()
{
	if (data != nullptr)
	{
		noOfDimensions = 0;
		delete[] data;
		delete[] sizeOfDimensions;
		delete[] startingIndex;
		data = nullptr;
		sizeOfDimensions = startingIndex = nullptr;
	}
}

int main()
{
	NDArray<double> arr({ 3,3 });
}