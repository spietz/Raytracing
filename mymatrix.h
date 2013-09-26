#ifndef _mymatrix_h
#define _mymatrix_h

#include <vector>

class mymatrix
{
    private:
        int _M, _N;
        std::vector<double> _data;
        int index(int m, int n) const;
    public:
        mymatrix(int M, int N) : _M(M), _N(N), _data(_M*_N, 0.0) {};
        double read(int m, int n) const;
        void write(int m, int n, double val);
        void print();
        mymatrix & operator+=(const mymatrix & rhs);
        mymatrix operator+(const mymatrix & rhs);
};

#endif
