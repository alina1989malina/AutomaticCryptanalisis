#ifndef SymbolicOctonion_H
#define SymbolicOctonion_H

#include <iostream>

#include "PolynomialFraction.h"

using namespace std;

class SymbolicOctonion
{
    //Polynomial e0, e1, e2, e3, e4, e5, e6, e7;
public:
    SymbolicOctonion(){};

    SymbolicOctonion(PolynomialFraction e0,PolynomialFraction e1,PolynomialFraction e2,PolynomialFraction e3,PolynomialFraction e4,PolynomialFraction e5,PolynomialFraction e6, PolynomialFraction e7){
        this->e0 = e0;
        this->e1 = e1;
        this->e2 = e2;
        this->e3 = e3;
        this->e4 = e4;
        this->e5 = e5;
        this->e6 = e6;
        this->e7 = e7;
    }

    PolynomialFraction normSqr();


    // Copy
    void operator=(const SymbolicOctonion &inSymbolicOctonion);
    // add SymbolicOctonion
    void operator+=(const SymbolicOctonion &ininSymbolicOctonion);
    // sum of two SymbolicOctonion
    SymbolicOctonion operator+(const SymbolicOctonion &inSymbolicOctonion) const;
    // sub SymbolicOctonion
    void operator-=(const SymbolicOctonion &inSymbolicOctonion);
    // Difference of two SymbolicOctonions
    SymbolicOctonion operator-(const SymbolicOctonion &inSymbolicOctonion) const;
    // multiply by SymbolicOctonion
    void operator*=(const SymbolicOctonion &inSymbolicOctonion);
    // product of two SymbolicOctonion
    SymbolicOctonion operator*(const SymbolicOctonion &ininSymbolicOctonion) const;

    // SymbolicOctonion inverse

    // Output stream
    friend ostream &operator<<(ostream &os, const SymbolicOctonion &inSymbolicOctonion);
    //private:
    PolynomialFraction e0, e1, e2, e3, e4, e5, e6, e7;
};


inline long operator==(const SymbolicOctonion &a, const SymbolicOctonion &b)
{
   return ( (a.e0 == b.e0) && (a.e1 == b.e1) && (a.e2 == b.e2) && (a.e3 == b.e3) && (a.e0 == b.e0) && (a.e4 == b.e4) && (a.e5 == b.e5) && (a.e6 == b.e6) && (a.e7 == b.e7) );
}

inline long operator!=(const SymbolicOctonion& a, const SymbolicOctonion& b)
{
   return !(a == b);
}


SymbolicOctonion inv(SymbolicOctonion &inSymbolicOctonion);

#endif // SymbolicOctonion_H
