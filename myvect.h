#ifndef MYVECT_H
#define MYVECT_H

#include <algorithm>
#include <iostream>
using namespace std;


template <typename Object>
class Vector
{
public:

    explicit Vector(int initSize = 0) : theSize{ initSize },
        theCapacity{ initSize + SPARE_CAPACITY }
    { objects = new Object[theCapacity];
    cout << "Method 1, default constructor" << endl; }

    Vector(const Vector& rhs) : theSize{ rhs.theSize },
        theCapacity{ rhs.theCapacity }, objects{ nullptr }
    {

        objects = new Object[theCapacity];
        for (int k = 0; k < theSize; ++k)
            objects[k] = rhs.objects[k];
        cout << "Method 2, copy constructor" << endl;
    }

    Vector& operator= (const Vector& rhs)
    {
        Vector copy(rhs);
        std::swap(*this, copy);
        cout << "Method 3, copy assignment operator" << endl;

        return *this;
    }

    ~Vector()
    {
        cout << "Method 4, destructor" << endl;
        delete[] objects;
    }

    Vector(Vector&& rhs) : theSize{ rhs.theSize },
        theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
    {
        cout << "Starting method 5, move assignment operator" << endl;
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
        cout << "Finishing method 5, move assignment operator" << endl;
    }


    Vector& operator= (Vector&& rhs)
    {
        cout << "Starting method 6, move assignment operator" << endl;
        std::swap(theSize, rhs.theSize);
        std::swap(theCapacity, rhs.theCapacity);
        std::swap(objects, rhs.objects);
        cout << "Finishing method 6, move assignment operator" << endl;
        return *this;
    }

    void resize(int newSize)
    {
        if (newSize > theCapacity)
            reserve(newSize * 2);
        theSize = newSize;
        cout << "Method 7, resize" << endl;
    }

    void reserve(int newCapacity)
    {
        if (newCapacity < theSize)
            return;

        Object* newArray = new Object[newCapacity];
        for (int k = 0; k < theSize; ++k)
            newArray[k] = std::move(objects[k]);

        theCapacity = newCapacity;
        std::swap(objects, newArray);
        delete[] newArray;

        cout << "Method 8, reserve" << endl;
    }

    Object& operator[ ](int index)
    {
        return objects[index]; cout << "Method 9, [ ]" << endl;
    }

    const Object& operator[ ](int index) const
    {
        return objects[index]; cout << "Method 10, [ ] (const)" << endl;
    }

    bool empty() const
    {
        cout << "Method 11, bool empty" << endl; return size() == 0;
    }
    int size() const
    {
        cout << "Method 12, size" << endl; return theSize;
    }
    int capacity() const
    {
        cout << "Method 13, capacity" << endl; return theCapacity;
    }

    void push_back(const Object& x)
    {
        if (theSize == theCapacity)
            reserve(2 * theCapacity + 1);
        objects[theSize++] = x;
        cout << "Method 14, push_back" << endl;
    }

    void push_back(Object&& x)
    {
        if (theSize == theCapacity)
            reserve(2 * theCapacity + 1);
        objects[theSize++] = std::move(x);
        cout << "Method 15, push_back" << endl;
    }

    void pop_back()
    {
        --theSize;
        cout << "Method 16, pop_back" << endl;
    }

    const Object& back() const
    {
        cout << "Method 17, back" << endl;
        return objects[theSize - 1];
    }

    typedef Object* iterator;
    typedef const Object* const_iterator;

    iterator begin()
    {
        cout << "Method 18, begin" << endl; return &objects[0];
    }
    const_iterator begin() const
    {
        cout << "Method 19, begin const" << endl; return &objects[0];
    }
    iterator end()
    {
        cout << "Method 20, end" << endl; return &objects[size()];
    }
    const_iterator end() const
    {
        cout << "Method 21, end const" << endl;  return &objects[size()];
    }

    static const int SPARE_CAPACITY = 16;

private:
    int theSize;
    int theCapacity;
    Object* objects;
};


#endif
