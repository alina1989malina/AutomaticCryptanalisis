#include "SymbolicOctonion.h"



void SymbolicOctonion::operator=(const SymbolicOctonion &inSymbolicOctonion){
    this->e0 = inSymbolicOctonion.e0;
    this->e1 = inSymbolicOctonion.e1;
    this->e2 = inSymbolicOctonion.e2;
    this->e3 = inSymbolicOctonion.e3;
    this->e4 = inSymbolicOctonion.e4;
    this->e5 = inSymbolicOctonion.e5;
    this->e6 = inSymbolicOctonion.e6;
    this->e7 = inSymbolicOctonion.e7;
}

void SymbolicOctonion::operator+=(const SymbolicOctonion &inSymbolicOctonion){
    this->e0 = this->e0 + inSymbolicOctonion.e0;
    this->e1 = this->e1 + inSymbolicOctonion.e1;
    this->e2 = this->e2 + inSymbolicOctonion.e2;
    this->e3 = this->e3 + inSymbolicOctonion.e3;
    this->e4 = this->e4 + inSymbolicOctonion.e4;
    this->e5 = this->e5 + inSymbolicOctonion.e5;
    this->e6 = this->e6 + inSymbolicOctonion.e6;
    this->e7 = this->e7 + inSymbolicOctonion.e7;
}

void SymbolicOctonion::operator-=(const SymbolicOctonion &inSymbolicOctonion){
    this->e0 = this->e0 - inSymbolicOctonion.e0;
    this->e1 = this->e1 - inSymbolicOctonion.e1;
    this->e2 = this->e2 - inSymbolicOctonion.e2;
    this->e3 = this->e3 - inSymbolicOctonion.e3;
    this->e4 = this->e4 - inSymbolicOctonion.e4;
    this->e5 = this->e5 - inSymbolicOctonion.e5;
    this->e6 = this->e6 - inSymbolicOctonion.e6;
    this->e7 = this->e7 - inSymbolicOctonion.e7;
}

void SymbolicOctonion::operator*=(const SymbolicOctonion &inOct){
    PolynomialFraction e0New = e0*inOct.e0 - e1*inOct.e1 - e2*inOct.e2 - e3*inOct.e3 - e4*inOct.e4 - e5*inOct.e5 - e6*inOct.e6 - e7*inOct.e7;
    PolynomialFraction e1New = e0*inOct.e1 + e1*inOct.e0 + e2*inOct.e4 + e3*inOct.e7 - e4*inOct.e2 + e5*inOct.e6 - e6*inOct.e5 - e7*inOct.e3;
    PolynomialFraction e2New = e0*inOct.e2 - e1*inOct.e4 + e2*inOct.e0 + e3*inOct.e5 + e4*inOct.e1 - e5*inOct.e3 + e6*inOct.e7 - e7*inOct.e6;
    PolynomialFraction e3New = e0*inOct.e3 - e1*inOct.e7 - e2*inOct.e5 + e3*inOct.e0 + e4*inOct.e6 + e5*inOct.e2 - e6*inOct.e4 + e7*inOct.e1;
    PolynomialFraction e4New = e0*inOct.e4 + e1*inOct.e2 - e2*inOct.e1 - e3*inOct.e6 + e4*inOct.e0 + e5*inOct.e7 + e6*inOct.e3 - e7*inOct.e5;
    PolynomialFraction e5New = e0*inOct.e5 - e1*inOct.e6 + e2*inOct.e3 - e3*inOct.e2 - e4*inOct.e7 + e5*inOct.e0 + e6*inOct.e1 + e7*inOct.e4;
    PolynomialFraction e6New = e0*inOct.e6 + e1*inOct.e5 - e2*inOct.e7 + e3*inOct.e4 - e4*inOct.e3 - e5*inOct.e1 + e6*inOct.e0 + e7*inOct.e2;
    PolynomialFraction e7New = e0*inOct.e7 + e1*inOct.e3 + e2*inOct.e6 - e3*inOct.e1 + e4*inOct.e5 - e5*inOct.e4 - e6*inOct.e2 + e7*inOct.e0;

    e0 = e0New;
    e1 = e1New;
    e2 = e2New;
    e3 = e3New;
    e4 = e4New;
    e5 = e5New;
    e6 = e6New;
    e7 = e7New;
}

SymbolicOctonion SymbolicOctonion::operator+(const SymbolicOctonion &inSymbolicOctonion) const
{
    SymbolicOctonion tmp(*this);
    tmp+=inSymbolicOctonion;
    return tmp;
}

SymbolicOctonion SymbolicOctonion::operator-(const SymbolicOctonion &inSymbolicOctonion) const
{
    SymbolicOctonion tmp(*this);
    tmp+=inSymbolicOctonion;
    return tmp;
}

SymbolicOctonion SymbolicOctonion::operator*(const SymbolicOctonion &inSymbolicOctonion) const
{
    SymbolicOctonion tmp(*this);
    tmp*=inSymbolicOctonion;
    return tmp;
}





PolynomialFraction SymbolicOctonion::normSqr(){
    return e0*e0+e1*e1+e2*e2+e3*e3+e4*e4+e5*e5+e6*e6+e7*e7;
}

SymbolicOctonion inv(SymbolicOctonion &inSymbolicOctonion){
    SymbolicOctonion result;

    result.e0 = inSymbolicOctonion.e0/(inSymbolicOctonion.normSqr());
    result.e1 = - inSymbolicOctonion.e1/(inSymbolicOctonion.normSqr());
    result.e2 = - inSymbolicOctonion.e2/(inSymbolicOctonion.normSqr());
    result.e3 = - inSymbolicOctonion.e3/(inSymbolicOctonion.normSqr());
    result.e4 = - inSymbolicOctonion.e4/ (inSymbolicOctonion.normSqr());
    result.e5 = - inSymbolicOctonion.e5/ (inSymbolicOctonion.normSqr());
    result.e6 = - inSymbolicOctonion.e6/ (inSymbolicOctonion.normSqr());
    result.e7 = - inSymbolicOctonion.e7/ (inSymbolicOctonion.normSqr());

    return result;
}

SymbolicOctonion SymbolicOctonion::operator()(const SymbolicOctonion &inSymbolicOctonion) const {
    map <Variable, PolynomialFraction> substitution;

    //filling map
    substitution[Variable(string("x_0")) ] = inSymbolicOctonion.e0;
    substitution[Variable(string("x_1")) ] = inSymbolicOctonion.e1;
    substitution[Variable(string("x_2")) ] = inSymbolicOctonion.e2;
    substitution[Variable(string("x_3")) ] = inSymbolicOctonion.e3;
    substitution[Variable(string("x_4")) ] = inSymbolicOctonion.e4;
    substitution[Variable(string("x_5")) ] = inSymbolicOctonion.e5;
    substitution[Variable(string("x_6")) ] = inSymbolicOctonion.e6;
    substitution[Variable(string("x_7")) ] = inSymbolicOctonion.e7;


    SymbolicOctonion result;
    result.e0 = e0(substitution);
    result.e1 = e1(substitution);
    result.e2 = e2(substitution);
    result.e3 = e3(substitution);
    result.e4 = e4(substitution);
    result.e5 = e5(substitution);
    result.e6 = e6(substitution);
    result.e7 = e7(substitution);

    return result;


}

SymbolicOctonion SymbolicOctonion::evaluate(const SymbolicOctonion &inSymbolicOctonion) const {
    map <Variable, PolynomialFraction> substitution;

    //filling map
    substitution[Variable(string("x_0")) ] = inSymbolicOctonion.e0;
    substitution[Variable(string("x_1")) ] = inSymbolicOctonion.e1;
    substitution[Variable(string("x_2")) ] = inSymbolicOctonion.e2;
    substitution[Variable(string("x_3")) ] = inSymbolicOctonion.e3;
    substitution[Variable(string("x_4")) ] = inSymbolicOctonion.e4;
    substitution[Variable(string("x_5")) ] = inSymbolicOctonion.e5;
    substitution[Variable(string("x_6")) ] = inSymbolicOctonion.e6;
    substitution[Variable(string("x_7")) ] = inSymbolicOctonion.e7;


    SymbolicOctonion result;
    result.e0 = e0(substitution);
    result.e1 = e1(substitution);
    result.e2 = e2(substitution);
    result.e3 = e3(substitution);
    result.e4 = e4(substitution);
    result.e5 = e5(substitution);
    result.e6 = e6(substitution);
    result.e7 = e7(substitution);

    return result;


}
