#include <iostream>
using namespace std;

template <typename T>
struct Node
{
	T info;
	Node<T>* next;
	Node()
	{ next = nullptr; }
	Node(T val)
	{
		info = val;
		next = nullptr;
	}
};

template <typename T>
class LSLL
{
	Node<T>* head;
public:
	LSLL()
	{ head = nullptr; }
	LSLL(const LSLL<T>&);
	void insertAtHead(T val);
	void insertAtTail(T val);
	void insertAfter(T key, T val);
	void insertBefore(T key, T val);
	void remove(T key);
	void removeAtHead();
	void removeAtTail();
	void removeAfter(T key);
	void removeBefore(T key);
	void printList();
	void reverse();
	void delAlternate();
	void swapNodes(int,int);
	bool search(T key);
	LSLL<T> createClone();
	~LSLL();
};

template<typename T>
LSLL<T>::LSLL(const LSLL<T>& right) : LSLL()
{
	if (!right.head)
	{
		return;
	}

	Node<T>* p = right.head, * ptr;
	
	ptr = head = new Node<T>(right.head->info);

	while (p->next)
	{
		ptr->next = new Node<T>(p->next->info);
		p = p->next;
		ptr = ptr->next;
	}
}

template<typename T>
void LSLL<T>::insertAtHead(T val)
{
	Node<T>* p = new Node<T>(val);
	p->next = head;
	head = p;
}

template<typename T>
void LSLL<T>::insertAtTail(T val)
{
	if (!head)
	{
		head = new Node<T>(val);
		return;
	}
	Node<T>* p = head;
	while (p->next != nullptr)
	{
		p = p->next;
	}
	p->next = new Node<T>(val);
}

template<typename T>
void LSLL<T>::insertAfter(T key, T val)
{
	if (!head)
	{
		return;
	}
	Node<T>* p = head;
	while (p != nullptr && p->info != key)
	{
		p = p->next;
	}
	if (p)
	{
		Node<T>* temp = new Node<T>(val);
		temp->next = p->next;
		p->next = temp;
	}
}

template<typename T>
void LSLL<T>::insertBefore(T key, T val)
{
	if (!head)
	{
		return;
	}
	if (head->info == key)
	{
		Node<T>* p = new Node<T>(val);
		p->next = head;
		head = p;
		return;
	}
	Node<T>* p = head;
	while (p->next != nullptr && p->next->info != key)
	{
		p = p->next;
	}
	if (p->next)
	{
		Node<T>* x = new Node<T>(val);
		x->next = p->next;
		p->next = x;
	}
}

template<typename T>
void LSLL<T>::remove(T key)
{
	if (!head)
	{
		return;
	}
	if (head->info == key)
	{
		Node<T>* temp = head;
		head = head->next;
		delete temp;
		return;
	}
	Node<T>* p = head;
	while (p->next != nullptr && p->next->info != key)
	{
		p = p->next;
	}
	if (p->next)
	{
		Node<T>* temp = p->next;
		p->next = p->next->next;
		delete temp;
	}
}

template<typename T>
void LSLL<T>::removeAtHead()
{
	if (!head)
	{
		return;
	}
	Node<T>* temp = head;
	head = head->next;
	delete temp;
}

template<typename T>
void LSLL<T>::removeAtTail()
{
	if (!head)
	{
		return;
	}
	if (!head->next)
	{
		delete head;
		head = nullptr;
		return;
	}
	Node<T>* p = head;
	while (p->next->next != nullptr)
	{
		p = p->next;
	}
	delete p->next;
	p->next = nullptr;
}

template<typename T>
void LSLL<T>::removeAfter(T key)
{
	if (!head)
	{
		return;
	}
	Node<T>* p = head;
	while (p != nullptr && p->info != key)
	{
		p = p->next;
	}
	if (p)
	{
		if (p->next)
		{
			Node<T>* temp = p->next;
			p->next = p->next->next;
			delete temp;
		}
	}
}

template<typename T>
void LSLL<T>::removeBefore(T key)
{
	Node<T>* p = head;
	if (!head || !head->next)
	{
		return;
	}
	if (head->next->info == key)
	{
		Node<T>* temp = head;
		head = head->next;
		delete temp;
		return;
	}
	while (p->next->next != nullptr && p->next->next->info != key)
	{
		p = p->next;
	}
	if (p->next->next)
	{
		Node<T>* temp = p->next;
		p->next = p->next->next;
		delete temp;
	}
}

template<typename T>
void LSLL<T>::printList()
{
	Node<T>* p = head;
	while (p != nullptr)
	{
		cout << p->info << ':';
		//system("pause");
		p = p->next;
	}
}

template<typename T>
void LSLL<T>::reverse()
{
	if (!head)
	{
		return;
	}
	Node<T> *temp, *mid = head->next, *prev = head;
	while (mid)
	{
		temp = mid->next;
		mid->next = prev;
		prev = mid;
		mid = temp;
	}
	head->next = nullptr;
	head = prev;
}

template<typename T>
void LSLL<T>::delAlternate()
{
	if (!head || !head->next)
	{
		return;
	}
	Node<T>* p = head, *temp;
	while (p->next && p->next->next)
	{
		temp = p->next;
		p->next = p->next->next;
		delete temp;
		p = p->next;
	}
	if (p->next)
	{
		delete p->next;
		p->next = nullptr;
	}
}

template<typename T>
void LSLL<T>::swapNodes(int m, int n)
{
	if (m <= 0 || n <= 0 || m == n || !head || !head->next || !head->next->next)
	{
		return;
	}
	int small = m < n ? m : n;
	int large = m > n ? m : n;
	if (small == 1)
	{
		if (large == 2)
		{
			Node<T>* p = head;
			head = head->next;
			p->next = head->next;
			head->next = p;
			return;
		}
		large -= 2;
		Node<T>* ptr2 = head, * afterFirst = head->next, * first = head, * afterSecondNode;
		while (ptr2->next->next && large-- > 0)
		{
			ptr2 = ptr2->next;
		}
		if (!ptr2->next)
		{
			return;
		}
		afterSecondNode = ptr2->next->next;
		head = ptr2->next;
		head->next = afterFirst;
		ptr2->next = first;
		ptr2->next->next = afterSecondNode;
		return;
	}
	small -= 2;
	large -= 2;
	if (large - small == 1)
	{
		Node<T>* ptr1 = head;
		while (ptr1->next->next && small-- > 0)
		{
			ptr1 = ptr1->next;
			large--;
		}
		if (!ptr1->next->next)
		{
			return;
		}
		Node<T>* firstNode = ptr1->next;
		ptr1->next = ptr1->next->next;
		firstNode->next = ptr1->next->next;
		ptr1->next->next = firstNode;
		return;
	}
	Node<T>* ptr1 = head;
	while (ptr1->next->next && small-- > 0)
	{
		ptr1 = ptr1->next;
		large--;
	}
	if (!ptr1->next)
	{
		return;
	}
	Node<T>* ptr2 = ptr1;
	while (ptr2->next->next && large-- > 0)
	{
		ptr2 = ptr2->next;
	}
	if (!ptr2->next)
	{
		return;
	}
	Node<T>* nextToFirstNode = ptr1->next->next, * nextToSecondNode = ptr2->next->next, * FirstNodePtr = ptr1->next;
	ptr1->next = ptr2->next;
	ptr1->next->next = nextToFirstNode;
	ptr2->next = FirstNodePtr;
	ptr2->next->next = nextToSecondNode;
}

template<typename T>
bool LSLL<T>::search(T key)
{
	if (!head)
	{
		return false;
	}
	Node<T>* p = head;
	while (p != nullptr && p->info != key)
	{
		p = p->next;
	}
	if (p)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
LSLL<T> LSLL<T>::createClone()
{
	return LSLL<T>(*this);
}

template<typename T>
LSLL<T>::~LSLL()
{
	if (head)
	{
		Node<T>* p = head;
		Node<T>* temp = head;
		while (p != nullptr)
		{
			temp = temp->next;
			//cout << "deleting " << p->info << '\n';
			delete p;
			p = temp;
		}
	}
}

int main()
{
	LSLL<int> l1;
	for (int i = 1; i <= 20; i++)
	{
		l1.insertAtTail(i);
	}

	l1.swapNodes(1, 2);

	l1.printList();
	
	

	//l1.delAlternate();
	//l1.reverse();
	//l1.insertBefore(21, 0);
	//l1.insertAfter(10, 0);
	//l1.insertAfter(12, 0);
	//l1.removeBefore(7);
	//l1.removeAfter(1);
	//l1.removeAtTail();
	//l1.removeAtHead();
	//cout << l1.search(11);
}