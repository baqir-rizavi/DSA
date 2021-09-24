#include <iostream>
#include <functional>	// for hash and pair class
#include <forward_list>	// can use custom made
#include <algorithm>	// for iterating functions example. "find/find_if/remove_if/copy"
using namespace std;

/*
* hashing of the "key" gives almost unique integral value which is then used 
* to store its "value" the "almost" part is solved by making an array 
* linkedlist, if hash gives the same value used before, 
* the list at that index is increamented, all operation is in O(1) on average
* every object/variable has a hash value already which is accesed by hash class
*/

template<typename KEY, typename VALUE>
class HashMap
{
private:
	int size = 20;
	int objectCount = 0;
	forward_list<pair<KEY, VALUE>>* data;
	//==============================
	int getHashValue(KEY key) const;
	void resize();
	//==============================
public:
	HashMap();
	HashMap(int size);
	HashMap(const HashMap& map);
	HashMap& operator=(const HashMap& map);
	void add(const KEY& key, const VALUE& val);
	VALUE& get(KEY key);
	void remove(KEY key);
	bool isPresent(KEY Key);
	bool isEmpty() const;
	int getCount() const;
	~HashMap();
};

int main()
{
	HashMap<int, string> h(20);
	h.add(4, "hi");
	cout << h.get(4);
}

#pragma region  implementation_of_HashMap_functions

template<typename KEY, typename VALUE>
int HashMap<KEY, VALUE>::getHashValue(KEY key) const
{
	hash<KEY> h;
	return h(key) % size;
}

template<typename KEY, typename VALUE>
void HashMap<KEY, VALUE>::resize()
{
	if (objectCount < 3 * size / 4)
		return;

	HashMap<KEY, VALUE> newMap(size * 2);

	for (int i = 0; i < size; i++)
		for_each(data[i].begin(), data[i].end(), [&](const pair<KEY, VALUE>& p) { add(p.first, p.second); });

	this->~HashMap();
	*this = newMap;
	//TODO: apply resize in case of shortening
}

template<typename KEY, typename VALUE>
HashMap<KEY, VALUE>::HashMap() : HashMap(20)
{}

template<typename KEY, typename VALUE>
HashMap<KEY, VALUE>::HashMap(int size)
{
	this->size = size;
	data = new forward_list<pair<KEY, VALUE>>[size];
}

template<typename KEY, typename VALUE>
HashMap<KEY, VALUE>::HashMap(const HashMap& map)
{
	*this = map;
}

template<typename KEY, typename VALUE>
HashMap<KEY, VALUE>& HashMap<KEY, VALUE>::operator= (const HashMap& map)
{
	if (this == &map)
		return *this;
	
	this->~HashMap();

	if (map.isEmpty())
		return *this;

	objectCount = map.objectCount;
	size = map.size;

	data = new forward_list<pair<KEY, VALUE>>[size];

	for (int i = 0; i < size; i++)
		copy(map.data[i].begin(), map.data[i].end(), data[i].begin());

	return *this;
}

template<typename KEY, typename VALUE>
void HashMap<KEY, VALUE>::add(const KEY& key, const VALUE& val)
{
	if (isPresent(key))
		return;
	data[getHashValue(key)].push_front(pair<KEY, VALUE>(key, val));
	objectCount++;
	resize();
}

template<typename KEY, typename VALUE>
VALUE& HashMap<KEY, VALUE>::get(KEY key)
{
	typename forward_list<pair<KEY, VALUE>>::iterator it;
	it = find_if(data[getHashValue(key)].begin(), data[getHashValue(key)].end(), [&](pair<KEY, VALUE> p) {return p.first == key; });
	
	if (it != data[getHashValue(key)].end())
		return it->second;
	else
		exit(0);

	// TODO: throw exception
}

template<typename KEY, typename VALUE>
void HashMap<KEY, VALUE>::remove(KEY key)
{
	data[getHashValue(key)].remove_if([&](pair<KEY, VALUE> p) {return p.first == key; });
	objectCount--;
}

template<typename KEY, typename VALUE>
bool HashMap<KEY, VALUE>::isPresent(KEY key)
{
	return (find_if(data[getHashValue(key)].begin(), data[getHashValue(key)].end(), [&](pair<KEY, VALUE> p) {return p.first == key; }) != data[getHashValue(key)].end());
}

template<typename KEY, typename VALUE>
bool HashMap<KEY, VALUE>::isEmpty() const
{
	return objectCount == 0;
}

template<typename KEY, typename VALUE>
int HashMap<KEY, VALUE>::getCount() const
{
	return objectCount;
}

template<typename KEY, typename VALUE>
HashMap<KEY, VALUE>::~HashMap()
{
	delete[] data;
}

#pragma endregion
