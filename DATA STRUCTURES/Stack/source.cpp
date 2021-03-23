#include <iostream>
using namespace std;
template <typename T>
class Stack
{
	int capacity;
	int top;
	void reSize(int);
	T* data;
public:
	Stack();
	Stack(const Stack<T>&);
	Stack<T>& operator=(const Stack<T>&);
	~Stack();
	void push(T);
	T pop();
	T stackTop();
	bool isFull();
	bool isEmpty();
	int getCapacity();
	int getNumberOfElements();
};

template <typename T>
Stack<T>::Stack()
{
	capacity = 0;
	data = nullptr;
	top = 0;
}

template<typename T>
Stack<T>::Stack(const Stack<T>& rval) : top(rval.top), capacity(rval.capacity)
{
	if (rval.data == nullptr)
	{
		this->~Stack();
		return;
	}
	data = new T[capacity];
	for (int i = 0; i < top; i++)
	{
		data[i] = rval.data[i];
	}
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rval)
{
	if (this == &rval)
	{
		return *this;
	}
	if (rval.data == nullptr)
	{
		this->~Stack();
		return *this;
	}
	capacity = rval.capacity;
	top = rval.top;
	data = new T[capacity];
	for (int i = 0; i < top; i++)
	{
		data[i] = rval.data[i];
	}
	return *this;
}

template<typename T>
void Stack<T>::push(T val)
{
	if (isFull())
	{
		reSize(capacity == 0 ? 1 : capacity * 2);
	}
	data[top++] = val;
}

template <typename T>
T Stack<T>::pop()
{
	if (isEmpty())
	{
		exit(0);
	}
	T val = data[--top];
	if (top > 0 && top == capacity / 4)
	{
		reSize(capacity / 2);
	}
	return val;
}

template <typename T>
T Stack<T>::stackTop()
{
	if (isEmpty())
	{
		exit(0);
	}
	return data[top - 1];

}

template<typename T>
bool Stack<T>::isFull()
{
	if (top == capacity)
	{
		return true;
	}
	return false;
}

template<typename T>
bool Stack<T>::isEmpty()
{
	if (top == 0)
	{
		return true;
	}
	return false;
}

template<typename T>
int Stack<T>::getCapacity()
{
	return capacity;
}

template<typename T>
int Stack<T>::getNumberOfElements()
{
	return top;
}

template <typename T>
Stack<T>::~Stack()
{
	if (!data)
	{
		return;
	}
	delete[] data;
	data = nullptr;
	capacity = 0;
	top = 0;
}

template <typename T>
void Stack<T>::reSize(int newSize)
{
	T* temp = new T[newSize];
	for (int i = 0; i < top; i++)
	{
		temp[i] = data[i];
	}
	int keepTop = top;
	this->~Stack();
	top = keepTop;
	data = temp;
	capacity = newSize;
}

int main()
{
	Stack<int> a;

}
