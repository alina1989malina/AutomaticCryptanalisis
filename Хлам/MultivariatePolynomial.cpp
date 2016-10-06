#include "MultivariatePolynomial.h"

MultivariatePolynomial::MultivariatePolynomial()
{
}





void MultivariatePolynomial::operator=(const MultivariatePolynomial &inMultivariatePolynomial){
    coeffs = inMultivariatePolynomial.coeffs;
}


void MultivariatePolynomial::operator+=(const MultivariatePolynomial &inMultivariatePolynomial){

}

// sum of two MultivariatePolynomials
MultivariatePolynomial MultivariatePolynomial::operator+(const MultivariatePolynomial &inMultivariatePolynomial) const{
    MultivariatePolynomial tmp(*this);
    tmp+=inMultivariatePolynomial;
    return tmp;
}

// sub MultivariatePolynomial
void MultivariatePolynomial::operator-=(const MultivariatePolynomial &inMultivariatePolynomial);

// Difference of two MultivariatePolynomials
MultivariatePolynomial MultivariatePolynomial::operator-(const MultivariatePolynomial &inMultivariatePolynomial) const;


//  multiplying by MultivariatePolynomial
void MultivariatePolynomial::operator*=(const MultivariatePolynomial &inMultivariatePolynomial);


// product of two MultivariatePolynomials
MultivariatePolynomial MultivariatePolynomial::operator*(const MultivariatePolynomial &inZZ_p_matX) const{

    MultivariatePolynomial tmp(*this);
    tmp*=inMultivariatePolynomial;
    return tmp;
}

// Substitution of one MultivariatePolynomial to another
MultivariatePolynomial MultivariatePolynomial::operator()(const MultivariatePolynomial &inMultivariatePolynomial);

//! Output stream
friend ostream &operator<<(ostream &os, const MultivariatePolynomial &inMultivariatePolynomial);
