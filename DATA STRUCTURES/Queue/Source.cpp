#include <iostream>

template <typename T>
class Queue
{
	int rear;
	int front;
	int capacity;
	int noOfElements;
	T* data;
	void reSize(int);
public:
	Queue();
	Queue(const Queue<T>&);
	Queue<T>& operator = (const Queue<T>&);
	~Queue();
	void enQueue(T);
	T deQueue();
	T getElementAtFront() const;
	bool isEmpty() const;
	bool isFull() const;
	int getNoOfElements() const;
	int getCapacity() const;
};

template<typename T>
void Queue<T>::reSize(int newSize)
{
	T* temp = new T[newSize];
	int j = 0;
	for (int i = front; j < noOfElements; i++, j++)
	{
		i = i % capacity;
		temp[j] = data[i];
	}
	this->~Queue();
	rear = j;
	noOfElements = j;
	data = temp; 
	capacity = newSize;
}

template<typename T>
Queue<T>::Queue()
{
	rear = front = capacity = noOfElements = 0;
	data = nullptr;
}

template<typename T>
Queue<T>::Queue(const Queue<T>& ref) : Queue()
{
	*this = ref;
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& rval)
{
	if (this == &rval)
	{
		return *this;
	}
	this->~Queue();
	if (rval.data == nullptr)
	{
		return *this;
	}
	capacity = rval.capacity;
	rear = rval.rear;
	front = rval.front;
	noOfElements = rval.noOfElements;
	data = new T[capacity];
	for (int i = front; i < rear; i++)
	{
		i = i % capacity;
		data[i] = rval.data[i];
	}
	return *this;
}

template<typename T>
Queue<T>::~Queue()
{
	if (data)
	{
		delete[] data;
		rear = front = capacity = noOfElements = 0;
		data = nullptr;
	}
}

template<typename T>
void Queue<T>::enQueue(T obj)
{
	if (isFull())
	{
		reSize(capacity == 0 ? 1 : capacity * 2);
	}
	data[rear++] = obj;
	rear = rear % capacity;
	noOfElements++;
}

template<typename T>
T Queue<T>::deQueue()
{
	if (isEmpty())
	{
		exit(0);
	}
	T val = data[front++];
	noOfElements--;
	front = front % capacity;
	if (noOfElements > 0 && noOfElements == capacity / 4)
	{
		reSize(capacity / 2);
	}
	return val;
}

template<typename T>
T Queue<T>::getElementAtFront() const
{
	if (isEmpty())
	{
		exit(0);
	}
	return data[front];
}

template<typename T>
bool Queue<T>::isEmpty() const
{
	return (noOfElements == 0 ? true : false);
}

template<typename T>
bool Queue<T>::isFull() const
{
	return (noOfElements == capacity ? true : false);
}

template<typename T>
int Queue<T>::getNoOfElements() const
{
	return noOfElements;
}

template<typename T>
int Queue<T>::getCapacity() const
{
	return capacity;
}

