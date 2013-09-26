#include "mymatrix.h"
#include <iostream>
#include <vector>
#include <stdexcept>

using std::vector;
using std::cout;
using std::endl;

mymatrix & mymatrix::operator+=(const mymatrix & rhs)
{
    for (int m = 0; m != _M; ++m)
    {
        for (int n = 0; n != _N; ++n)
        {
            write(m, n, read(m,n) + rhs.read(m,n));
        }
    }
    return *this;
}

mymatrix mymatrix::operator+(const mymatrix & rhs)
{
    mymatrix ret = *this;
    ret += rhs;
    return ret;
}

int mymatrix::index(int m, int n) const
{
    if (m<0 || m>=_M || n<0 || n>=_N)
    {
        throw std::out_of_range("Matrix index out of range");
    }
    return m+_M*n;
}

double mymatrix::read(int m, int n) const
{
    return _data[index(m,n)];
}

void mymatrix::write(int m, int n, double val)
{
    _data[index(m,n)] = val;
}

void mymatrix::print()
{
    for (int m = 0; m != _M; ++m)
    {
        for (int n = 0; n != _N; ++n)
        {
            cout << read(m,n) << " ";
        }
        cout << endl;
    }
    cout << endl;
}
