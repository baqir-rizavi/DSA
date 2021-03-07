#pragma once
#include <iostream>

template<typename T>
class Node
{
private:
	Node<T>* next;
	T data;
	
	Node(T d) : data(d), next(nullptr) 
	{}
	

	template<typename R> friend class LinkedList;
};


template <typename T>
class LinkedList
{
private:

	Node<T>* head;
	int length;

	Node<T>& get_nth_node(int n);

public:


	LinkedList();
	LinkedList(const LinkedList<T>& list);
	const LinkedList<T>& operator=(const LinkedList<T>& list);
	~LinkedList();
	
	void append(const T&);
	int search(T);
	void remove(int);
	void insert(T, int);
	void display();
	T operator[] (int);
	//const T& operator[](const int&) const;
	T end();
};


template<typename T>
LinkedList<T>::LinkedList() : length(0), head(nullptr)
{}

template<typename T>
T LinkedList<T>::end() 
{ 

}

template<typename T>
Node<T>& LinkedList<T>::get_nth_node(int n)
{
	if (n <= 0 || n > length)
	{
		std::cout << "[error]: accessing wrong location";
		exit(0);
	}
	
	Node<T>* temp = head;
	for (int i = 1; i < n; i++)
	{
		temp = temp->next;
	}
	return *temp;
}


template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{

}

template<typename T>
const LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list)
{
	
}


template<typename T>
LinkedList<T>::~LinkedList()
{
	
}

template<typename T>
void LinkedList<T>::append(const T& obj)
{
	if (length == 0)
	{
		head = new Node<T>(obj);
		head->data = obj;
		length++;
	}
	else
	{
		Node<T>*& p = get_nth_node(length++).next = new Node<T>(obj);
		p->data = obj;
	}
}

template<typename T>
int LinkedList<T>::search(T)
{
	return 0;
}

template<typename T>
void LinkedList<T>::remove(int)
{
}

template<typename T>
void LinkedList<T>::insert(T, int)
{
}

template<typename T>
void LinkedList<T>::display()
{

}

template<typename T>
T LinkedList<T>::operator[](int n)
{
	return get_nth_node(++n).data;
}


