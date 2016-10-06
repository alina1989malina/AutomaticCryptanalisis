#ifndef SymbolicOctonion_H
#define SymbolicOctonion_H

#include <iostream>

#include "PolynomialFraction.h"
#include "SymbolicMatrix.h"

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

    SymbolicOctonion(string e0, string e1, string e2, string e3, string e4, string e5, string e6, string e7){
        this->e0 = PolynomialFraction(e0);
        this->e1 = PolynomialFraction(e1);
        this->e2 = PolynomialFraction(e2);
        this->e3 = PolynomialFraction(e3);
        this->e4 = PolynomialFraction(e4);
        this->e5 = PolynomialFraction(e5);
        this->e6 = PolynomialFraction(e6);
        this->e7 = PolynomialFraction(e7);
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

    SymbolicOctonion operator()(const SymbolicOctonion &inSymbolicOctonion) const;

    SymbolicOctonion evaluate(const SymbolicOctonion &inSymbolicOctonion) const;

    // SymbolicOctonion inverse

    // Output stream
    friend ostream &operator<<(ostream &os, const SymbolicOctonion &inSymbolicOctonion){

        os <<"("<<endl;
        os << inSymbolicOctonion.e0 <<" ,"<<endl;
        os << inSymbolicOctonion.e1 <<" ,"<<endl;
        os << inSymbolicOctonion.e2 <<" ,"<<endl;
        os << inSymbolicOctonion.e3 <<" ,"<<endl;
        os << inSymbolicOctonion.e4 <<" ,"<<endl;
        os << inSymbolicOctonion.e5 <<" ,"<<endl;
        os << inSymbolicOctonion.e6 <<" ,"<<endl;
        os << inSymbolicOctonion.e7 <<" ,"<<endl;
        os << ")"<<endl;
        return os;

    }

    SymbolicMatrix getMatrix(){
       SymbolicMatrix a;
       a.setDims(8,8);

       Variable x0("x_0");
       Variable x1("x_1");
       Variable x2("x_2");
       Variable x3("x_3");
       Variable x4("x_4");
       Variable x5("x_5");
       Variable x6("x_6");
       Variable x7("x_7");

       a.setEntry(0,0,this->e0.getNumerator().extractPartDivisibleBy(x0));
       a.setEntry(0,1,this->e1.getNumerator().extractPartDivisibleBy(x0));
       a.setEntry(0,2,this->e2.getNumerator().extractPartDivisibleBy(x0));
       a.setEntry(0,3,this->e3.getNumerator().extractPartDivisibleBy(x0));
       a.setEntry(0,4,this->e4.getNumerator().extractPartDivisibleBy(x0));
       a.setEntry(0,5,this->e5.getNumerator().extractPartDivisibleBy(x0));
       a.setEntry(0,6,this->e6.getNumerator().extractPartDivisibleBy(x0));
       a.setEntry(0,7,this->e7.getNumerator().extractPartDivisibleBy(x0));

       a.setEntry(1,0,this->e0.getNumerator().extractPartDivisibleBy(x1));
       a.setEntry(1,1,this->e1.getNumerator().extractPartDivisibleBy(x1));
       a.setEntry(1,2,this->e2.getNumerator().extractPartDivisibleBy(x1));
       a.setEntry(1,3,this->e3.getNumerator().extractPartDivisibleBy(x1));
       a.setEntry(1,4,this->e4.getNumerator().extractPartDivisibleBy(x1));
       a.setEntry(1,5,this->e5.getNumerator().extractPartDivisibleBy(x1));
       a.setEntry(1,6,this->e6.getNumerator().extractPartDivisibleBy(x1));
       a.setEntry(1,7,this->e7.getNumerator().extractPartDivisibleBy(x1));

       a.setEntry(2,0,this->e0.getNumerator().extractPartDivisibleBy(x2));
       a.setEntry(2,1,this->e1.getNumerator().extractPartDivisibleBy(x2));
       a.setEntry(2,2,this->e2.getNumerator().extractPartDivisibleBy(x2));
       a.setEntry(2,3,this->e3.getNumerator().extractPartDivisibleBy(x2));
       a.setEntry(2,4,this->e4.getNumerator().extractPartDivisibleBy(x2));
       a.setEntry(2,5,this->e5.getNumerator().extractPartDivisibleBy(x2));
       a.setEntry(2,6,this->e6.getNumerator().extractPartDivisibleBy(x2));
       a.setEntry(2,7,this->e7.getNumerator().extractPartDivisibleBy(x2));

       a.setEntry(3,0,this->e0.getNumerator().extractPartDivisibleBy(x3));
       a.setEntry(3,1,this->e1.getNumerator().extractPartDivisibleBy(x3));
       a.setEntry(3,2,this->e2.getNumerator().extractPartDivisibleBy(x3));
       a.setEntry(3,3,this->e3.getNumerator().extractPartDivisibleBy(x3));
       a.setEntry(3,4,this->e4.getNumerator().extractPartDivisibleBy(x3));
       a.setEntry(3,5,this->e5.getNumerator().extractPartDivisibleBy(x3));
       a.setEntry(3,6,this->e6.getNumerator().extractPartDivisibleBy(x3));
       a.setEntry(3,7,this->e7.getNumerator().extractPartDivisibleBy(x3));

       a.setEntry(4,0,this->e0.getNumerator().extractPartDivisibleBy(x4));
       a.setEntry(4,1,this->e1.getNumerator().extractPartDivisibleBy(x4));
       a.setEntry(4,2,this->e2.getNumerator().extractPartDivisibleBy(x4));
       a.setEntry(4,3,this->e3.getNumerator().extractPartDivisibleBy(x4));
       a.setEntry(4,4,this->e4.getNumerator().extractPartDivisibleBy(x4));
       a.setEntry(4,5,this->e5.getNumerator().extractPartDivisibleBy(x4));
       a.setEntry(4,6,this->e6.getNumerator().extractPartDivisibleBy(x4));
       a.setEntry(4,7,this->e7.getNumerator().extractPartDivisibleBy(x4));

       a.setEntry(5,0,this->e0.getNumerator().extractPartDivisibleBy(x5));
       a.setEntry(5,1,this->e1.getNumerator().extractPartDivisibleBy(x5));
       a.setEntry(5,2,this->e2.getNumerator().extractPartDivisibleBy(x5));
       a.setEntry(5,3,this->e3.getNumerator().extractPartDivisibleBy(x5));
       a.setEntry(5,4,this->e4.getNumerator().extractPartDivisibleBy(x5));
       a.setEntry(5,5,this->e5.getNumerator().extractPartDivisibleBy(x5));
       a.setEntry(5,6,this->e6.getNumerator().extractPartDivisibleBy(x5));
       a.setEntry(5,7,this->e7.getNumerator().extractPartDivisibleBy(x5));

       a.setEntry(6,0,this->e0.getNumerator().extractPartDivisibleBy(x6));
       a.setEntry(6,1,this->e1.getNumerator().extractPartDivisibleBy(x6));
       a.setEntry(6,2,this->e2.getNumerator().extractPartDivisibleBy(x6));
       a.setEntry(6,3,this->e3.getNumerator().extractPartDivisibleBy(x6));
       a.setEntry(6,4,this->e4.getNumerator().extractPartDivisibleBy(x6));
       a.setEntry(6,5,this->e5.getNumerator().extractPartDivisibleBy(x6));
       a.setEntry(6,6,this->e6.getNumerator().extractPartDivisibleBy(x6));
       a.setEntry(6,7,this->e7.getNumerator().extractPartDivisibleBy(x6));

       a.setEntry(7,0,this->e0.getNumerator().extractPartDivisibleBy(x7));
       a.setEntry(7,1,this->e1.getNumerator().extractPartDivisibleBy(x7));
       a.setEntry(7,2,this->e2.getNumerator().extractPartDivisibleBy(x7));
       a.setEntry(7,3,this->e3.getNumerator().extractPartDivisibleBy(x7));
       a.setEntry(7,4,this->e4.getNumerator().extractPartDivisibleBy(x7));
       a.setEntry(7,5,this->e5.getNumerator().extractPartDivisibleBy(x7));
       a.setEntry(7,6,this->e6.getNumerator().extractPartDivisibleBy(x7));
       a.setEntry(7,7,this->e7.getNumerator().extractPartDivisibleBy(x7));




       return a;
    }
    

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
