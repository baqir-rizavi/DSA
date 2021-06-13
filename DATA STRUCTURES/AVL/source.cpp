#include <iostream>
using namespace std;

template<typename T>
struct AVLNode
{
	T info;
	AVLNode<T>* left = nullptr;
	AVLNode<T>* right = nullptr;
	int height = 1;
	AVLNode() {};
	AVLNode(T val) : info(val) {};
};

template<typename T>
class AVL
{
protected:
	AVLNode<T>* root;
private:
	enum class RotationType
	{
		LL, LR, RL, RR
	};
	void remove(AVLNode<T>* ptr);
	void LVR(const AVLNode<T>* ptr) const;
	int getBalanceFactor(AVLNode<T>* ptr);
	RotationType getRotationType(AVLNode<T>* ptr);
	int getHeight(AVLNode<T>* ptr);
public:
	AVL() : root(nullptr) {};
	~AVL();
	void insert(T val);
	void inOrder() const;
	void remove(T);
	bool search(T) const;
};

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

template <typename KEY, typename VALUE>
struct Pair 
{
	KEY key;
	VALUE val;
	Pair()
	{}
	Pair(KEY k, VALUE v) : key(k), val(v)
	{}
	bool operator==(const Pair& x) const
	{
		return key == x.key;
	}
	bool operator > (const Pair& x) const
	{
		return key > x.key;
	}
	bool operator < (const Pair& x) const
	{
		return key < x.key;
	}
};

template <typename KEY, typename VALUE> 
ostream& operator << (ostream& out, const Pair<KEY, VALUE>& p)
{
	cout << "(" << p.key << ":" << p.val << ")";
	return out;
}

template <typename KEY, typename VALUE>
class Dictionary : public AVL<Pair<KEY, VALUE>>
{
public:
	void insert(KEY key, VALUE val);
	void remove(KEY key);
	bool search(KEY key) const;
	VALUE& operator[] (KEY key);
};

int main()
{
	Dictionary<string, int> dict;
	dict.insert("apples", 14);
	dict.insert("oranges", 5);
	dict.insert("bananas", 20);
	dict.insert("grapes", 50);
	dict.insert("cherry", 30);
	dict["grapes"] = 456;
	dict.remove("oranges");
	dict.inOrder();
}

template<typename KEY, typename VALUE>
void Dictionary<KEY, VALUE>::insert(KEY key, VALUE val)
{
	AVL<Pair<KEY, VALUE>>::insert(Pair<KEY, VALUE>(key, val));
}

template<typename KEY, typename VALUE>
void Dictionary<KEY, VALUE>::remove(KEY key)
{
	AVL<Pair<KEY, VALUE>>::remove(Pair<KEY, VALUE>(key, VALUE()));
}

template<typename KEY, typename VALUE>
bool Dictionary<KEY, VALUE>::search(KEY key) const
{
	return AVL<Pair<KEY, VALUE>>::search(Pair<KEY, VALUE>(key, VALUE()));
}

template<typename KEY, typename VALUE>
VALUE& Dictionary<KEY, VALUE>::operator[](KEY key)
{
	AVLNode<Pair<KEY, VALUE>>* ptr = Dictionary<KEY, VALUE>::root;
	while (ptr)
	{
		if (ptr->info.key == key)
		{
			return ptr->info.val;
		}
		ptr = (key < ptr->info.key ? ptr->left : ptr->right);
	}
	exit(0);	
}

template<typename T>
void AVL<T>::remove(AVLNode<T>* ptr)
{
	if (!ptr)
	{
		return;
	}
	remove(ptr->left);
	remove(ptr->right);
	delete ptr;
}

template<typename T>
void AVL<T>::LVR(const AVLNode<T>* ptr) const
{
	if (!ptr)
		return;
	LVR(ptr->left);
	cout << "(" << ptr->info << ", " << ptr->height << ")|";
	LVR(ptr->right);
}

template<typename T>
int AVL<T>::getBalanceFactor(AVLNode<T>* ptr)
{
	if (!ptr->right && !ptr->left)
		return 0;
	else if (!ptr->left)
		return -(ptr->right->height);
	else if (!ptr->right)
		return ptr->left->height;
	else 
		return (ptr->left->height - ptr->right->height);
}

template<typename T>
typename AVL<T>::RotationType AVL<T>::getRotationType(AVLNode<T>* ptr)
{
	if (getBalanceFactor(ptr) > 0) // left
	{
		return (getBalanceFactor(ptr->left) > 0 ? RotationType::LL : RotationType::LR);
	}
	else // right
	{
		return (getBalanceFactor(ptr->right) > 0 ? RotationType::RL : RotationType::RR);
	}
}

template<typename T>
int AVL<T>::getHeight(AVLNode<T>* ptr)
{
	if (ptr->left && ptr->right)
		return 1 + (ptr->left->height > ptr->right->height ? ptr->left->height : ptr->right->height);
	else if (ptr->left || ptr->right)
		return 1 + (ptr->right ? ptr->right->height : ptr->left->height);
	else
		return 1;
}

template<typename T>
AVL<T>::~AVL()
{
	if (root)
	{
		remove(root);
		root = nullptr;
	}
}

template<typename T>
void AVL<T>::insert(T val)
{
	if (!root)
	{
		root = new AVLNode<T>(val);
		return;
	}
	AVLNode<T>* ptr = root;
	Stack<AVLNode<T>*> ancestorPath;
	while (ptr)
	{
		ancestorPath.push(ptr);
		ptr = (val < ptr->info ? ptr->left : ptr->right);
	}
	ptr = ancestorPath.pop();
	(val < ptr->info ? ptr->left : ptr->right) = new AVLNode<T>(val);
	ptr->height = getHeight(ptr);

	// new node inserted ^^^

	while (!ancestorPath.isEmpty())
	{
		ptr = ancestorPath.pop();
		int bf = getBalanceFactor(ptr);
		if (bf > 1 || bf < -1) // rotation is to be done
		{
			RotationType rotation = getRotationType(ptr);
			AVLNode<T>* parent = nullptr;
			if (!ancestorPath.isEmpty())
				parent = ancestorPath.pop();
			AVLNode<T>* temp;
			switch (rotation)		// "ptr" here is piviot
			{
			case RotationType::LL:

				if (ptr == root)
				{
					temp = root->left->right;
					root->left->right = root;
					root = root->left;
					root->right->left = temp;
					root->right->height = getHeight(root->right);
					//root->left->height = getHeight(root->left);
					root->height = getHeight(root);
					return;
				}
				if (ptr == parent->left)
				{
					temp = ptr->left->right;
					parent->left = ptr->left;
					parent->left->right = ptr;
					ptr->left = temp;
					ptr->height = getHeight(ptr);
				}
				else // if (ptr == parent->right)
				{
					temp = ptr->left->right;
					parent->right = ptr->left;
					parent->right->right = ptr;
					ptr->left = temp;
					ptr->height = getHeight(ptr);
				}
				ancestorPath.push(parent);
				break;
			case RotationType::LR:

				if (ptr == root)
				{
					temp = root->left->right;
					root->left->right = temp->left;
					temp->left = root->left;
					auto save = temp->right;
					temp->right = root;
					root = temp;
					if (root->right)
						root->right->left = save;
					root->right->height = getHeight(root->right);
					root->left->height = getHeight(root->left);
					root->height = getHeight(root);
					return;
				}
				temp = ptr->left->right;
				ptr->left->right = temp->left;
				temp->left = ptr->left;
				ptr->left = temp->right;
				temp->right = ptr;
				if (ptr == parent->left)
				{
					parent->left = temp;
				}
				else // if (ptr == parent->right)
				{
					parent->right = temp;
				}
				temp->right->height = getHeight(temp->right);
				temp->left->height = getHeight(temp->left);
				temp->height = getHeight(temp);
				break;
			case RotationType::RL:
				
				if (ptr == root)
				{
					temp = root->right->left;
					root->right->left = temp->right;
					temp->right = root->right;
					auto save = temp->left;
					temp->left = root;
					root = temp;
					if (root->left)
						root->left->right = save;
					root->right->height = getHeight(root->right);
					root->left->height = getHeight(root->left);
					root->height = getHeight(root);
					return;
				}
				temp = ptr->right->left;
				ptr->right->left = temp->right;
				temp->right = ptr->right;
				ptr->right = temp->left;
				temp->left = ptr;
				if (ptr == parent->left)
				{
					parent->left = temp;
				}
				else // if (ptr == parent->right)
				{
					parent->right = temp;
				}
				temp->right->height = getHeight(temp->right);
				temp->left->height = getHeight(temp->left);
				temp->height = getHeight(temp);
				break;
			case RotationType::RR:
				if (ptr == root)
				{
					temp = root->right->left;
					root->right->left = root;
					root = root->right;
					root->left->right = temp;
					//root->right->height = getHeight(root->right);
					root->left->height = getHeight(root->left);
					root->height = getHeight(root);

					return;
				}
				if (ptr == parent->left)
				{
					temp = ptr->right->left;
					parent->left = ptr->right;
					parent->left->left = ptr;
					ptr->right = temp;
					ptr->height = getHeight(ptr);
				}
				else // if (ptr == parent->right)
				{
					temp = ptr->right->left;
					parent->right = ptr->right;
					parent->right->left = ptr;
					ptr->right = temp;
					ptr->height = getHeight(ptr);
				}
				ancestorPath.push(parent);
				break;
			}
		}
		ptr->height = getHeight(ptr);
	}
	
}

template<typename T>
void AVL<T>::inOrder() const
{
	LVR(root);
}

template<typename T>
void AVL<T>::remove(T key)
{
	AVLNode<T>* ptr = root, * prev = root;
	Stack<AVLNode<T>*> ancestorPath;
	while (ptr)
	{
		ancestorPath.push(ptr);
		if (ptr->info == key)
		{
			if (!ptr->left && !ptr->right) // degree 0
			{
				if (ptr == root)
				{
					delete root;
					root = nullptr;
					return;
				}
				if (prev->right == ptr)
				{
					delete prev->right;
					prev->right = nullptr;
					ptr = nullptr;
				}
				else // if (prev->left == ptr)
				{
					delete prev->left;
					prev->left = nullptr;
					ptr = nullptr;
				}
			}
			else if ((bool)ptr->left != (bool)ptr->right) // degree 1
			{
				if (ptr == root)
				{
					root = (ptr->right ? ptr->right : ptr->left);
					delete ptr;
					ptr = nullptr;
					return;
				}
				if (prev->right == ptr)
				{
					prev->right = (ptr->right ? ptr->right : ptr->left);
					delete ptr;
					ptr = nullptr;
				}
				else // if (prev->left == ptr)
				{
					prev->left = ptr->right ? ptr->right : ptr->left;
					delete ptr;
					ptr = nullptr;
				}
			}
			else // if (ptr->right && ptr->left) // degree 2
			{
				AVLNode<T>* tempPtr = ptr;
				// going to its inorder successor
				tempPtr  = tempPtr->right;
				ancestorPath.push(tempPtr);
				while (tempPtr->left->left)
				{
					tempPtr = tempPtr->left;
					ancestorPath.push(tempPtr);
				}
				ptr->info = tempPtr->left->info;
				delete tempPtr->left;
				tempPtr->left = nullptr;
				ancestorPath.push(tempPtr->left);
				break;
			}
		}
		else if (key < ptr->info)
		{
			prev = ptr;
			ptr = ptr->left;
		}
		else // if (key >= ptr->info)
		{
			prev = ptr;
			ptr = ptr->right;
		}
	}
	ancestorPath.pop(); // deallocated memory address
	
	// node removed ^^^

	while (!ancestorPath.isEmpty())
	{
		ptr = ancestorPath.pop();
		int bf = getBalanceFactor(ptr);
		if (bf > 1 || bf < -1) // rotation is to be done
		{
			RotationType rotation = getRotationType(ptr);
			AVLNode<T>* parent = nullptr;
			if (!ancestorPath.isEmpty())
				parent = ancestorPath.pop();
			AVLNode<T>* temp;
			switch (rotation)		// "ptr" here is piviot
			{
			case RotationType::LL:

				if (ptr == root)
				{
					temp = root->left->right;
					root->left->right = root;
					root = root->left;
					root->right->left = temp;
					root->right->height = getHeight(root->right);
					//root->left->height = getHeight(root->left);
					root->height = getHeight(root);
					return;
				}
				if (ptr == parent->left)
				{
					temp = ptr->left->right;
					parent->left = ptr->left;
					parent->left->right = ptr;
					ptr->left = temp;
					ptr->height = getHeight(ptr);
				}
				else // if (ptr == parent->right)
				{
					temp = ptr->left->right;
					parent->right = ptr->left;
					parent->right->right = ptr;
					ptr->left = temp;
					ptr->height = getHeight(ptr);
				}
				ancestorPath.push(parent);
				break;
			case RotationType::LR:

				if (ptr == root)
				{
					temp = root->left->right;
					root->left->right = temp->left;
					temp->left = root->left;
					auto save = temp->right;
					temp->right = root;
					root = temp;
					if (root->right)
						root->right->left = save;
					root->right->height = getHeight(root->right);
					root->left->height = getHeight(root->left);
					root->height = getHeight(root);
					return;
				}
				temp = ptr->left->right;
				ptr->left->right = temp->left;
				temp->left = ptr->left;
				ptr->left = temp->right;
				temp->right = ptr;
				if (ptr == parent->left)
				{
					parent->left = temp;
				}
				else // if (ptr == parent->right)
				{
					parent->right = temp;
				}
				temp->right->height = getHeight(temp->right);
				temp->left->height = getHeight(temp->left);
				temp->height = getHeight(temp);
				break;
			case RotationType::RL:

				if (ptr == root)
				{
					temp = root->right->left;
					root->right->left = temp->right;
					temp->right = root->right;
					auto save = temp->left;
					temp->left = root;
					root = temp;
					if (root->left)
						root->left->right = save;
					root->right->height = getHeight(root->right);
					root->left->height = getHeight(root->left);
					root->height = getHeight(root);
					return;
				}
				temp = ptr->right->left;
				ptr->right->left = temp->right;
				temp->right = ptr->right;
				ptr->right = temp->left;
				temp->left = ptr;
				if (ptr == parent->left)
				{
					parent->left = temp;
				}
				else // if (ptr == parent->right)
				{
					parent->right = temp;
				}
				temp->right->height = getHeight(temp->right);
				temp->left->height = getHeight(temp->left);
				temp->height = getHeight(temp);
				break;
			case RotationType::RR:
				if (ptr == root)
				{
					temp = root->right->left;
					root->right->left = root;
					root = root->right;
					root->left->right = temp;
					//root->right->height = getHeight(root->right);
					root->left->height = getHeight(root->left);
					root->height = getHeight(root);

					return;
				}
				if (ptr == parent->left)
				{
					temp = ptr->right->left;
					parent->left = ptr->right;
					parent->left->left = ptr;
					ptr->right = temp;
					ptr->height = getHeight(ptr);
				}
				else // if (ptr == parent->right)
				{
					temp = ptr->right->left;
					parent->right = ptr->right;
					parent->right->left = ptr;
					ptr->right = temp;
					ptr->height = getHeight(ptr);
				}
				ancestorPath.push(parent);
				break;
			}
		}
		ptr->height = getHeight(ptr);
	}
}

template<typename T>
bool AVL<T>::search(T key) const
{
	AVLNode<T>* ptr = root;
	while (ptr)
	{
		if (ptr->info == key)
		{
			return true;
		}
		ptr = (key < ptr->info ? ptr->left : ptr->right);
	}
	return false;
}

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
