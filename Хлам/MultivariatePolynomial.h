#ifndef MULTIVARIATEPOLYNOMIAL_H
#define MULTIVARIATEPOLYNOMIAL_H

#include <vector>
#include <sstream>
#include <iostream>
#include <NTL/ZZ_p.h>

using namespace std;
using namespace NTL;

NTL_CLIENT

class MultivariatePolynomial
{
public:
    MultivariatePolynomial();
    MultivariatePolynomial(ZZ_p *coeffs);

    // Copy
    void operator=(const MultivariatePolynomial &inMultivariatePolynomial);
    // adding MultivariatePolynomial
    void operator+=(const MultivariatePolynomial &inMultivariatePolynomial);
    // sum of two MultivariatePolynomials
    MultivariatePolynomial operator+(const MultivariatePolynomial &inMultivariatePolynomial) const;
    // sub MultivariatePolynomial
    void operator-=(const MultivariatePolynomial &inMultivariatePolynomial);
    // Difference of two MultivariatePolynomials
    MultivariatePolynomial operator-(const MultivariatePolynomial &inMultivariatePolynomial) const;
    //  multiplying by MultivariatePolynomial
    void operator*=(const MultivariatePolynomial &inMultivariatePolynomial);
    // product of two MultivariatePolynomials
    MultivariatePolynomial operator*(const MultivariatePolynomial &inZZ_p_matX) const;
    // Substitution of one MultivariatePolynomial to another
    MultivariatePolynomial operator()(const MultivariatePolynomial &inMultivariatePolynomial);

    //! Output stream
    friend ostream &operator<<(ostream &os, const MultivariatePolynomial &inMultivariatePolynomial);

    ZZ_p coeffs[8];
};

#endif // MULTIVARIATEPOLYNOMIAL_H
