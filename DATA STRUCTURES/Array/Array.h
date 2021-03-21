#pragma once

#include <iostream>
#include <iomanip>
//#include <initializer_list>
using namespace std;

template<typename T>
class Array
{
    T* data;
    int capacity;
public:
    //Array();
    //Array(int);
    Array(const initializer_list<T>& list = {});
    Array(const Array<T>&);
    ~Array();
    T& operator [] (int);
    const T& operator [] (int) const;
    int getCapacity() const;
    void reSize(int);
    T* end() const;
    T* begin() const;
    bool isValidIndex(int index) const;

    Array<T>& operator = (const Array<T>&);

    Array<T> operator + (const Array<T>&) const;
    Array<T> operator - (const Array<T>&) const;
    Array<T> operator * (const Array<T>&) const;

    template<typename R>
    friend std::istream& operator>>(std::istream&, Array<R>&);

    template<typename R> 
    friend std::ostream& operator<<(std::ostream&, const Array<R>&);
};

template<typename T>
Array<T>::Array(const initializer_list<T>& list)
{
    capacity = list.size();
    if (capacity <= 0)
    {
        capacity = 0;
        data = nullptr;
        return;
    }
    data = new T[capacity];
    int i = 0;
    for (const T& val : list)
    {
        data[i++] = val;
    }

}

template<typename T>
T* Array<T>::end() const
{
    return data + capacity;
}

template<typename T>
T* Array<T>::begin() const
{
    return data;
}

template<typename T> 
Array<T> Array<T>::operator+(const Array<T>& a) const
{
    const Array<T>& smaller = capacity < a.capacity ? *this : a;
    const Array<T>& largger = capacity >= a.capacity ? *this : a;
    
    Array<T> arr(largger);
    for (int i = 0; i < smaller.capacity; i++)
    {
            arr[i] = data[i] + a[i];
    }
    return arr;
}

template<typename T>
Array<T> Array<T>::operator-(const Array<T>& a) const
{
    const Array<T>& smaller = capacity < a.capacity ? *this : a;
    const Array<T>& largger = capacity >= a.capacity ? *this : a;

    Array<T> arr(largger);
    for (int i = 0; i < smaller.capacity; i++)
    {
        arr[i] = data[i] - a[i];
    }
    return arr;
}

template<typename T>
Array<T> Array<T>::operator*(const Array<T>& a) const
{
    const Array<T>& smaller = capacity < a.capacity ? *this : a;
    const Array<T>& largger = capacity >= a.capacity ? *this : a;

    Array<T> arr(largger);
    for (int i = 0; i < smaller.capacity; i++)
    {
        arr[i] = data[i] * a[i];
    }
    return arr;
}


template<typename T>
bool Array<T>::isValidIndex(int index) const
{
    return index >= 0 && index < capacity;
}
//template<typename T>
//Array<T>::Array()
//{
//    capacity = 0;
//    data = nullptr;
//}
//template<typename T>
//Array<T>::Array(int size) : Array()
//{
//    if (size <= 0)
//        return;
//    capacity = size;
//    data = new T[capacity];
//}


template<typename T>
Array<T>::~Array()
{
    if (data)
        delete[] data;
    data = nullptr;
    capacity = 0;
}
template<typename T>
T& Array<T>::operator [] (int i)
{
    if (isValidIndex(i))
        return data[i];
    
    std::cout << "\n[error]: array out of bound\n"; 
    exit(0);
}
template<typename T>
const T& Array<T>::operator [] (int i) const
{
    if (isValidIndex(i))
        return data[i];

    std::cout << "\n[error]: array out of bound\n"; 
    exit(0);
}

template<typename T>
int Array<T>::getCapacity() const
{
    return capacity;
}
template<typename T>
void Array<T>::reSize(int newCap)
{
    if (newCap <= 0)
    {
        this->~Array();
        return;
    }

    T* ptr = new T[newCap];
    if (capacity > 0)
    {
        int size = newCap < capacity ? newCap : capacity;
        for (int i = 0; i < size; i++)
        {
            ptr[i] = data[i];
        }
    }

    this->~Array();
    capacity = newCap;
    data = ptr;
}

template<typename T>
Array<T>& Array<T>::operator = (const Array<T>& ref)
{
    if (this == &ref)
        return *this;
    this->~Array();
    if (ref.data == nullptr)
    {
        data = nullptr;
        capacity = 0;
        return *this;
    }
    capacity = ref.capacity;
    data = new T[capacity];
    for (int i = 0; i < capacity; i++)
    {
        data[i] = ref.data[i];
    }
    return *this;
}

template<typename T>
Array<T>::Array(const Array <T>& ref)
{
    if (ref.data == nullptr)
    {
        data = nullptr;
        capacity = 0;
        return;
    }
    capacity = ref.capacity;
    data = new T[capacity];
    for (int i = 0; i < capacity; i++)
    {
        data[i] = ref.data[i];
    }
}

template<typename T>
std::ostream& operator <<(std::ostream& out, const Array<T>& ref)
{
    for (int i = 0; i < ref.getCapacity(); i++)
        out << " " << ref[i];
    return out;
}

template<typename T>
std::istream& operator >>(std::istream& in, Array<T>& ref)
{
    for (int i = 0; i < ref.getCapacity(); i++)
        in >> ref[i];
    return in;
}

