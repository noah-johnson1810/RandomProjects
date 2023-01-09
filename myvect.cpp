#include <iostream>
#include <algorithm>
#include "myvect.h"

using namespace std;

int main()
{
    Vector<int> a;
    const int num = 5;
    Vector<int>::iterator it;

    int change;
    a[0] = 15;

    Vector<int> b(a);
    b[0] = 2;

    Vector<int> c;
    c = b;
    c[0] = 3;

    Vector<int> d((Vector<int>&&) c);
    d[0] = 4;

    a.resize(16); // method 7
    b.resize(1000); // method 8

    Vector<int> e;
    bool empty = e.empty();
    if (empty)
        cout << "e is empty" << endl;
    else
    {
        cout << "e is not empty" << endl;
    }
    e[0] = 1;
    empty = e.empty();
    if (empty)
        cout << "e is empty" << endl;
    else
    {
        cout << "e is not empty" << endl;
    }

    cout << d.capacity();
    d.push_back(num);
    d.push_back(5);
    d.pop_back();
    change = d.back();

    it = d.begin();
    it = d.end();
    const Vector<int> f(d);
    Vector<int>::const_iterator it2 = f.begin();
    Vector<int>::const_iterator it3 = f.end();

    return 0;
}
