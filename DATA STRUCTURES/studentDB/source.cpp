#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
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
struct Student
{
int rollNo;
char name[30];
double CGPA;
Student()
{}
Student(int rn, const char* nm, double gp) : rollNo(rn), CGPA(gp)
{
strcpy(name, nm);
}
};
ostream& operator << (ostream& out, const Student& s)
{
out << right << setw(4) << s.rollNo << " ";
out << setfill('-') << left << setw(32) << s.name;
out << setfill(' ');
out << setw(4) << s.CGPA;
return out;
}
template <typename KEY, typename VALUE>
class DBAVLIndex : public AVL<Pair<KEY, VALUE>>
{
string DBFileName = "StudentDatabase.txt";
AVL<Pair<KEY, VALUE>> markedRecords;
void LVR(AVLNode<Pair<KEY, VALUE>>*, fstream&, Student&);
public:
void setDBFileName(const char* name);
void addRecord(Pair<KEY, VALUE> rec);
VALUE searchRecord(KEY key);
bool removeRecord(KEY key);
void removeMarkedRecords();
void printAll();
};
class StudentDBOperations
{
static char DBFileName[100];
static DBAVLIndex<int, int> index;
public:
static bool initializeDB(const char* fn);
static const char* getDBFileName();
static void setDBFileName(const char* fn);
static bool addRecord(const Student&);
static bool updateRecord(const Student& s);
static void printAll();
static bool removeRecord(int rollNo);
static void removeMarkedRecordsPermanenlty();
};
char StudentDBOperations::DBFileName[100] = "StudentDatabase.txt";
DBAVLIndex<int, int> StudentDBOperations::index;
int main()
{
StudentDBOperations::initializeDB(nullptr);
Student s(5, "ALIZA TARIQ", 3.78);
StudentDBOperations::addRecord(s);
s = Student(47, "AMNA TARIQ", 2.43);
StudentDBOperations::addRecord(s);
s = Student(38, "ANS NAEEM", 2.9);
StudentDBOperations::addRecord(s);
s = Student(37, "MUHAMMAD ISMAEEL", 3.5);
StudentDBOperations::addRecord(s);
s = Student(16, "USAMA RIAZ", 2.7);
StudentDBOperations::addRecord(s);
s = Student(21, "RAFAY QAYYUM", 3.27);
StudentDBOperations::addRecord(s);
s = Student(1, "NAUKHAIZ ANJUM", 2.3);
StudentDBOperations::addRecord(s);
StudentDBOperations::addRecord(s);
s = Student(18, "MUHAMMAD AHSAN", 2.9);
StudentDBOperations::addRecord(s);
s = Student(31, "SALIHA QAISAR", 2.13);
StudentDBOperations::addRecord(s);
s = Student(14, "M. TAHIR", 3.3);
StudentDBOperations::addRecord(s);
s = Student(13, "FAKHAR MEHDI", 2.5);
StudentDBOperations::addRecord(s);
s = Student(12, "WAJAHAT ISLAM GUL", 3.1);
StudentDBOperations::addRecord(s);
s = Student(2, "SADIA UMAR", 2.7);
StudentDBOperations::addRecord(s);
s = Student(53, "SAYYID M. BAQIR RIZAVI", 4);
StudentDBOperations::addRecord(s);
s = Student(44, "NOOR SABA SHAHID", 3.9);
StudentDBOperations::addRecord(s);
s = Student(38, "KOMAL AFZAAL", 3.4);
StudentDBOperations::addRecord(s);
s = Student(9, "GONASH BIN JAVED", 3.5);
StudentDBOperations::addRecord(s);
StudentDBOperations::printAll();
StudentDBOperations::removeRecord(14);
StudentDBOperations::removeRecord(31);
cout << "\n***************************************\n";
StudentDBOperations::printAll();
cout << "\n***************************************\n";
s = Student(14, "MUHAMMAD Tahir", 3.92);
StudentDBOperations::addRecord(s);
StudentDBOperations::printAll();
StudentDBOperations::removeMarkedRecordsPermanenlty();
return 0;
}
template<typename KEY, typename VALUE>
void DBAVLIndex<KEY, VALUE>::LVR(AVLNode<Pair<KEY, VALUE>>* ptr, fstream& h, Student& s)
{
if (!ptr)
return;
LVR(ptr->left, h, s);
h.seekg(ptr->info.val, ios::beg);
h.read((char*)&s, sizeof(Student));
cout << s << '\n';
LVR(ptr->right, h, s);
}
template<typename KEY, typename VALUE>
void DBAVLIndex<KEY, VALUE>::setDBFileName(const char* name)
{
DBFileName = name;
}
template<typename KEY, typename VALUE>
void DBAVLIndex<KEY, VALUE>::addRecord(Pair<KEY, VALUE> rec)
{
AVL<Pair<KEY, VALUE>>::insert(rec);
}
template<typename KEY, typename VALUE>
VALUE DBAVLIndex<KEY, VALUE>::searchRecord(KEY key)
{
AVLNode<Pair<KEY, VALUE>>* ptr = DBAVLIndex<KEY, VALUE>::root;
while (ptr)
{
if (ptr->info.key == key)
{
return ptr->info.val;
}
ptr = (key < ptr->info.key ? ptr->left : ptr->right);
}
return -1;
}
template<typename KEY, typename VALUE>
bool DBAVLIndex<KEY, VALUE>::removeRecord(KEY key)
{
VALUE var = searchRecord(key);
if (var != -1)
{
AVL<Pair<KEY, VALUE>>::remove(Pair<KEY, VALUE>(key, VALUE()));
markedRecords.insert(Pair<KEY, VALUE>(key, var));
return true;
}
else return false;
}
template<typename KEY, typename VALUE>
void DBAVLIndex<KEY, VALUE>::removeMarkedRecords()
{
fstream DBHandle;
DBHandle.open(DBFileName, ios::in | ios::binary);
if (!DBHandle.is_open())
{
exit(0);
}
DBHandle.seekg(0, ios::end);
int lenght = DBHandle.tellg() / sizeof(Student);
DBHandle.seekg(0, ios::beg);
fstream temp;
temp.open("temp.txt", ios::out);
if (!temp.is_open())
{
exit(0);
}
AVL<Pair<KEY, VALUE>>::~AVL();
Student read;
for (int i = 0; i < lenght; i++)
{
DBHandle.read((char*)(&read), sizeof(Student));
if (!markedRecords.search(Pair<KEY, VALUE>(read.rollNo, VALUE())))
{
VALUE p = temp.tellp();
temp.write((char*)(&read), sizeof(Student));
addRecord(Pair<KEY, VALUE>(read.rollNo, p));
}
}
markedRecords.~AVL();
DBHandle.close();
temp.close();
remove(DBFileName.c_str());
rename("temp.txt", DBFileName.c_str());
}
template<typename KEY, typename VALUE>
void DBAVLIndex<KEY, VALUE>::printAll()
{
fstream DBHandle;
DBHandle.open(DBFileName, ios::in | ios::binary);
if (!DBHandle.is_open())
{
//cout << "file error in print";
exit(0);
}
Student read;
LVR(DBAVLIndex<KEY, VALUE>::root, DBHandle, read);
}
bool StudentDBOperations::initializeDB(const char* fn)
{
if (fn != nullptr)
{
setDBFileName(fn);
}
fstream DBHandle;
DBHandle.open(DBFileName, ios::in);
if (DBHandle.is_open())
{
DBHandle.close();
DBHandle.open(DBFileName, ios::binary | ios::app);
}
else
DBHandle.open(DBFileName, ios::binary | ios::out);
if (!DBHandle.is_open())
{
return false;
}
DBHandle.close();
return true;
}
const char* StudentDBOperations::getDBFileName()
{
return DBFileName;
}
void StudentDBOperations::setDBFileName(const char* fn)
{
strcpy(DBFileName, fn);
}
bool StudentDBOperations::addRecord(const Student& s)
{
fstream DBHandle;
DBHandle.open(DBFileName, ios::app | ios::out | ios::binary);
if (!DBHandle.is_open())
{
return false;
}
DBHandle.seekp(0, ios::end);
if (!index.search(Pair<int, int>(s.rollNo, 0)))
{
index.addRecord(Pair<int, int>(s.rollNo, DBHandle.tellp()));
DBHandle.write((char*)(&s), sizeof(Student));
return false;
}
else return true;
}
bool StudentDBOperations::removeRecord(int rollNo)
{
return index.removeRecord(rollNo);
}
void StudentDBOperations::removeMarkedRecordsPermanenlty()
{
index.removeMarkedRecords();
}
bool StudentDBOperations::updateRecord(const Student& s)
{
fstream DBHandle;
DBHandle.open(DBFileName, ios::out | ios::binary | ios::app);
if (!DBHandle.is_open())
{
return false;
}
int var = index.searchRecord(s.rollNo);
if (var == -1)
return false;
DBHandle.seekp(var, ios::beg);
DBHandle.write((char*)(&s), sizeof(Student));
return true;
}
void StudentDBOperations::printAll()
{
index.printAll();
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
cout << ptr->info << ", ";
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
switch (rotation) // "ptr" here is piviot
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
tempPtr = tempPtr->right;
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
switch (rotation) // "ptr" here is piviot
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
