#ifndef POLYNOMIALFRACTION_H
#define POLYNOMIALFRACTION_H

#include "Polynomial.h"

class PolynomialFraction
{
private:
    Polynomial numerator, denominator;
public:
    // Begin constructors
    PolynomialFraction();

    PolynomialFraction(Polynomial inNumerator){
        this->numerator = inNumerator;
        this->denominator = Polynomial(to_ZZ_p(1));
    }

    PolynomialFraction(Polynomial inNumerator, Polynomial inDenominator){
        this->numerator = inNumerator;
        this->denominator = inDenominator;
    }

    PolynomialFraction (string S) {

        stringstream Sstream(S);
        assert( readStream(Sstream) );
    }
    // End constructors

    // Begin operators
    PolynomialFraction operator + (PolynomialFraction const &A) const{
        Polynomial newNumerator;
        Polynomial newDenominator;
        if(A.denominator==denominator){
            newNumerator = numerator + A.numerator;
            newDenominator = denominator;
        }
        else{
            newNumerator = numerator*A.denominator + A.numerator*denominator;
            newDenominator = denominator*A.denominator;
        }
        PolynomialFraction res(newNumerator,newDenominator);
        res.normalize();
        return res;//(PolynomialFraction(newNumerator,newDenominator)).normalize();//PolynomialFraction(newNumerator/gcd(newNumerator,newDenominator),newDenominator/gcd(newNumerator,newDenominator));
    }

    PolynomialFraction operator - (PolynomialFraction const &A) const{
        Polynomial newNumerator;
        Polynomial newDenominator;
        if(A.denominator==denominator){
            newNumerator = numerator - A.numerator;
            newDenominator = denominator;
        }
        else{
            newNumerator = numerator*A.denominator - A.numerator*denominator;
            newDenominator = denominator*A.denominator;
        }
        PolynomialFraction res(newNumerator,newDenominator);
        res.normalize();
        return res;//(PolynomialFraction(newNumerator,newDenominator)).normalize();//PolynomialFraction(newNumerator/gcd(newNumerator,newDenominator),newDenominator/gcd(newNumerator,newDenominator));
    }

    PolynomialFraction operator - () const{//unary operator -
        PolynomialFraction res(*this);
        res.numerator = - res.numerator;
        return res;
    }

    void operator -= (PolynomialFraction const &A) {
        (*this) = (*this) - A;
    }

    void operator += (PolynomialFraction const &A) {
        (*this) = (*this) + A;
    }

    void operator *= (PolynomialFraction const &A) {
        (*this) = (*this) * A;
    }

    PolynomialFraction operator * (ZZ_p c) const{
        if ( c == to_ZZ_p(0) ) return PolynomialFraction();

        PolynomialFraction res(numerator*c ,denominator);//(PolynomialFraction(numerator*c ,denominator)).normalize();
        res.normalize();
        return res;
    }

    PolynomialFraction operator * (PolynomialFraction const &A) const;

    PolynomialFraction operator / (PolynomialFraction const &A) const;

    bool operator == (PolynomialFraction const &A) const{
        return (numerator.coef == A.numerator.coef)&&(denominator.coef == A.denominator.coef);
    }

    bool operator != (PolynomialFraction const &A) const{
        return !((*this)==A);
    }

    PolynomialFraction operator()(map <Variable, PolynomialFraction> &val) const;

    void normalize(){
        //cout<<"denominator.degree()"<<denominator.degree()<<endl;
        //reduces numerator with denominator
        if(numerator==Polynomial(to_ZZ_p(0))){
            denominator = Polynomial(to_ZZ_p(1));
        }

        if(denominator.degree()==0){
            numerator = numerator* inv(denominator.getCoefficientOfTermWithMonomial(Monomial(string("1"))));
            denominator = Polynomial(to_ZZ_p(1));
        }

        if(numerator==denominator){
            numerator = Polynomial(to_ZZ_p(1));
            denominator = Polynomial(to_ZZ_p(1));
        }

        //if denomiator and numerator have common divisor we need remove it...
    }

    // End operators

    //Begin getters
    Polynomial getNumerator(){
        return this->numerator;
    }

    Polynomial getDenominator(){
        return this->denominator;
    }

    //End getters



    // Begin input output
    bool readStream(istream &in) {

        char c;
        if(!in.get(c)) {return false;}

        if(c== '('){//we have two-floor fraction
            Polynomial temp;
            in >> temp;
            numerator = temp;
            in.get(c);
            if(c!= ')') {return false;}
            in.get(c);
            if(c!= '/') {return false;}
            in.get(c);
            if(c!= '(') {return false;}
            in >> temp;
            denominator = temp;
            in.get(c);
            if(c!= ')') {return false;}
        }
        else{
            //assume we have one-floor fraction
            in.unget();
            Polynomial temp;
            in >> temp;
            numerator = temp;
            denominator = Polynomial(to_ZZ_p(1));
        }
        return true;


        //if not "(" and not "/"
        //read as usual polynomial with 1 in denominator
        //else distribute numerator and denominator
    }

    void writeStream(ostream &out) const{

        if(denominator!=Polynomial(to_ZZ_p(1))){
            out<<"(";
            numerator.writeStream(out);
            out<<")/(";
            denominator.writeStream(out);
            out<<")";
        }
        else{
            numerator.writeStream(out);
        }

    }

    friend ostream & operator << (ostream &out, PolynomialFraction const &A) {
        A.writeStream(out);
        return out;
    }

};

#endif // POLYNOMIALFRACTION_H
