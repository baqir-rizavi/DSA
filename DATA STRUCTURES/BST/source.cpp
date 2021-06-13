#include <iostream>
using namespace std;

template <typename T>
struct BSTNode
{
	T info;
	BSTNode<T>* left = nullptr;
	BSTNode<T>* right = nullptr;
	bool rightFlag = false;
	BSTNode() {}
	BSTNode(T val) : info(val) {}
};

template <typename T>
class RightBST
{
	BSTNode<T>* root;
	void remove(BSTNode<T>* ptr);
public:
	RightBST() : root(nullptr)
	{};
	~RightBST();
	class Iterator
	{
		friend class RightBST<T>;
		BSTNode<T>* pointee;
		Iterator(BSTNode<T>* ptr)
		{
			pointee = ptr;
			if (pointee)
			{
				while (pointee->left)
				{
					pointee = pointee->left;
				}
			}
		}
	public:
		const T& operator*()
		{
			return pointee->info;
		}
		const Iterator& operator++()
		{
			if (pointee->rightFlag)
			{
				pointee = pointee->right;
			}
			else
			{
				pointee = pointee->right;
				while (pointee->left)
				{
					pointee = pointee->left;
				}
			}
			return *this;
		}
		bool operator!=(const Iterator& other) const
		{
			return pointee != other.pointee;
		}
	};
	void insert(T key);
	void remove(T key);
	bool search(T key);
	Iterator begin() const
	{
		return Iterator(root);
	}
	Iterator end() const
	{
		return Iterator(nullptr);
	}
};

int main()
{
	RightBST<int> b;
	b.insert(100);
	b.insert(30);
	b.insert(150);
	b.insert(10);
	b.insert(70);
	b.insert(200);
	b.insert(50);
	b.insert(80);
	b.insert(180);
	b.insert(40);
	b.insert(190);
	b.insert(35);

	for (auto i : b)
	{
		cout << i << ", ";
		++i; // <--- "does not do anything but added in Lab pdf" 
	}

	cout << "\n************************\n";

	RightBST<int>::Iterator i = b.begin();

	while (i != b.end())
	{
		cout << *i << ", ";
		++i;
	}

	cout << "\n************************\n";

	i = b.begin();
	++i; ++i; ++i; ++i;
	cout << *i;

	return 0;
}

template<typename T>
void RightBST<T>::remove(BSTNode<T>* ptr)
{
	if (!ptr)
	{
		return;
	}
	remove(ptr->left);
	if (!ptr->rightFlag)
		remove(ptr->right);
	delete ptr;
}

template<typename T>
RightBST<T>::~RightBST()
{
	remove(root);
	root = nullptr;
}

template<typename T>
void RightBST<T>::insert(T key)
{
	if (!root)
	{
		root = new BSTNode<T>(key);
		return;
	}
	BSTNode<T>* ptr = root;
	BSTNode<T>* prev = root;
	while (ptr)
	{
		prev = ptr;
		if (key < ptr->info)
		{
			ptr = ptr->left;
		}
		else // if (key >= ptr->info)
		{
			if (!ptr->rightFlag)
				ptr = ptr->right;
			else
				ptr = nullptr;
		}
	}

	if (key < prev->info)
	{
		prev->left = new BSTNode<T>(key);
		prev->left->right = prev;
		prev->left->rightFlag = true;
	}
	else // to right 
	{
		BSTNode<T>* saved = prev->right;
		prev->right = new BSTNode<T>(key);
		prev->rightFlag = false;
		prev->right->right = saved;
		prev->right->rightFlag = true;
	}
}

template<typename T>
void RightBST<T>::remove(T key)
{
	BSTNode<T>* ptr = root, * prev = root;
	while (ptr)
	{
		if (ptr->info == key)
		{
			if (!ptr->left && ptr->rightFlag) // degree 0
			{
				if (prev->right == ptr)
				{
					BSTNode<T>* saved = ptr->right;
					delete prev->right;
					prev->right = saved;
				}
				else // if (prev->left == ptr)
				{
					delete prev->left;
					prev->left = nullptr;
				}
			}
			else if ((bool)ptr->left != ((bool)ptr->right && !ptr->rightFlag)) // degree 1
			{
				if (prev->right == ptr)
				{
					prev->right = ptr->right ? ptr->right : ptr->left;
					delete ptr;
				}
				else // if (prev->left == ptr)
				{

					prev->left = ptr->right ? ptr->right : ptr->left;
					delete ptr;
				}
			}
			else if ((ptr->right && !ptr->rightFlag) && ptr->left) // degree 2
			{
				BSTNode<T>* tempPtr = ptr;
				// going to its inorder successor
				tempPtr = tempPtr->right;
				while (tempPtr->left->left)
				{
					tempPtr = tempPtr->left;
				}
				ptr->info = tempPtr->left->info;
				delete tempPtr->left;
				tempPtr->left = nullptr;
			}
			return;
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
}

template<typename T>
bool RightBST<T>::search(T key)
{
	BSTNode<T>* ptr = root;
	while (ptr)
	{
		if (ptr->info == key)
		{
			return true;
		}
		else if (key < ptr->info)
		{
			ptr = ptr->left;
		}
		else // if (key >= ptr->info)
		{
			if (ptr->rightFlag)
			{
				return false;
			}
			ptr = ptr->right;
		}
	}
	return false;
}
