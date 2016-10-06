#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "Utility.h"
#include "Monomial.h"
using namespace std;

class Polynomial
{
private:
    map <Monomial, ZZ_p> coef;

    friend class PolynomialFraction;
    friend class PolynomialIdeal;

    void removeNullCoefficients();

public:
    // Begin constructors
    Polynomial(){
        coef = map <Monomial, ZZ_p>();
    }

    Polynomial (ZZ_p c) {
        coef = map <Monomial, ZZ_p>();
        if ( c != to_ZZ_p(0) ) coef[Monomial()] = c;
    }

    Polynomial (Monomial M, ZZ_p c) {
        coef = map <Monomial, ZZ_p>();
        coef[M] = c;
    }

    Polynomial (Monomial M) {
        coef = map <Monomial, ZZ_p>();
        coef[M] = 1;
    }


    Polynomial (long long int c){
        Polynomial (to_ZZ_p(c));
    }


    Polynomial (string S) {
        coef = map <Monomial, ZZ_p>();
        stringstream Sstream(S);
        assert( readStream(Sstream) );
    }

    /*Polynomial (const char * inPolynomial) {
        Polynomial(string(inPolynomial));
    }*/

    Polynomial (const Polynomial &P) { // copy constructor
        for ( map <Monomial, ZZ_p>::const_iterator mon = P.coef.begin(); mon!=P.coef.end(); mon++) {
            coef[Monomial(mon->first)] = mon->second;
        }
    }
    // End constructors

    bool empty() const{
        return coef.empty();
    }

    long int degree(){
        if(empty()) return -1;
        else{
            long int maxDegree = 0;
            for ( map <Monomial, ZZ_p>::const_iterator mon = coef.begin(); mon!=coef.end(); mon++) {
                Monomial currentMonomial(mon->first);
                if(currentMonomial.degree()> maxDegree){
                    maxDegree = currentMonomial.degree();
                }
            }
            return maxDegree;
            //leadingMonomial().degree();//wrong!! we need explore all monomials and select the biggest degree!!
        }
    }

    bool containsVariable(Variable X) const{
        for (map <Monomial, ZZ_p>::const_iterator mon = coef.begin();mon!=coef.end(); mon++) {
            if ( mon->first.containsVariable(X) ) return true;
        }
        return false;
    }

    bool containsMonomial(Monomial M) const{
        for (map <Monomial, ZZ_p>::const_iterator mon = coef.begin();mon!=coef.end(); mon++) {
            if ( mon->first == M ) return true;
        }
        return false;
    }

    ZZ_p getCoefficientOfTermWithMonomial(Monomial M){
        for (map <Monomial, ZZ_p>::const_iterator mon = coef.begin();mon!=coef.end(); mon++) {
            if ( mon->first == M ) return mon->second;
        }
        return to_ZZ_p(0);
    }

    bool isDivisibleBy(Polynomial const &A);

    Polynomial extractPartDivisibleBy(Monomial M){
        Polynomial res;


        for (map <Monomial, ZZ_p>::iterator mon = coef.begin();mon!=coef.end(); mon++) {
            Monomial currentMon(mon->first);
            Polynomial currentMonomial(currentMon);


           /* if(currentMonomial.isDivisibleBy(divisor)){
                //add to result
                res+=currentMonomial;
            }*/
        }
        return res;
    }

    Polynomial extractPartDivisibleBy(Variable V){
        Polynomial res;

        Monomial divisor(V);

        for (map <Monomial, ZZ_p>::iterator mon = coef.begin();mon!=coef.end(); mon++) {
            Monomial currentMon(mon->first);

            if(currentMon.containsVariable(V)){
                //add to result
                currentMon = currentMon / divisor;
                Polynomial currentMonomial(currentMon,mon->second);
                res+=currentMonomial;
            }
        }
        return res;
    }

    // TODO: Potrebbe restituire un polinomio (valutando solo alcune
    // delle variabili e non tutte)
    ZZ_p evaluate(map <Variable, ZZ_p> &val) const{
        ZZ_p res = to_ZZ_p(0);
        for(map <Monomial, ZZ_p>::const_iterator mon = coef.begin();mon!=coef.end(); mon++) {
            res += mon->second * mon->first.evaluate(val);
        }
        return res;
    }

    // Begin operators
    Polynomial operator + (Polynomial const &A) const{
        Polynomial res = *this;
        for (map <Monomial, ZZ_p>::const_iterator mon = A.coef.begin();mon!=A.coef.end(); mon++ )
            res.coef[mon->first] += mon->second;
        res.removeNullCoefficients();
        return res;
    }

    Polynomial operator - (Polynomial const &A) const{
        Polynomial res = *this;
        for (map <Monomial, ZZ_p>::const_iterator mon = A.coef.begin();mon!=A.coef.end(); mon++ )
            res.coef[mon->first] -= mon->second;
        res.removeNullCoefficients();
        return res;
    }

    Polynomial operator * (Polynomial const &A) const{
        Polynomial res;
        for (map <Monomial, ZZ_p>::const_iterator mon1 = coef.begin();mon1!=coef.end(); mon1++ ){
            for (map <Monomial, ZZ_p>::const_iterator mon2 = A.coef.begin();mon2!=A.coef.end(); mon2++ )
                res.coef[mon1->first * mon2->first] += mon1->second * mon2->second;
        }
        res.removeNullCoefficients();
        return res;
    }

    void operator += (Polynomial const &A) {
        (*this) = (*this) + A;
    }

    void operator -= (Polynomial const &A) {
        (*this) = (*this) - A;
    }

    Polynomial operator - () const{
        //create null polinomial
        Polynomial zero(to_ZZ_p(0));
        return zero - (*this);
    }

    void operator *= (Polynomial const &A) {
        (*this) = (*this) * A;
    }

    Polynomial operator * (ZZ_p c) const{
        if ( c == to_ZZ_p(0) ) return Polynomial();
        Polynomial res = *this;
        for (map <Monomial, ZZ_p>::iterator it = res.coef.begin(); it!=res.coef.end(); it++) {
            (*it).second *= c;
        }
        return res;
    }

    Polynomial operator / (ZZ_p c) const{
        assert( c != to_ZZ_p(0) );
        Polynomial res = *this;
        for (map <Monomial, ZZ_p>::iterator it = res.coef.begin(); it!=res.coef.end(); it++) {
            (*it).second /= c;
        }
        return res;
    }

    void operator *= (ZZ_p c) {
        (*this) = (*this) * c;
    }

    void operator /= (ZZ_p c) {
        (*this) = (*this) / c;
    }

    bool operator == (Polynomial const &A) const{
        return coef == A.coef;
    }

    bool operator != (Polynomial const &A) const{
        return coef != A.coef;
    }

    bool operator < (Polynomial const &A) const{
        return leadingMonomial() < A.leadingMonomial();
    }

    bool operator > (Polynomial const &A) const{
        return leadingMonomial() > A.leadingMonomial();
    }


    Polynomial operator()(map <Variable, Polynomial> &val) const{
        Polynomial res = Polynomial(to_ZZ_p(0));
        for(map <Monomial, ZZ_p>::const_iterator mon = coef.begin();mon!=coef.end(); mon++) {
            Polynomial evaluatedMonomial(to_ZZ_p(1));

            for(map <Variable, int>::const_iterator variable = mon->first.exponent.begin(); variable != mon->first.exponent.end(); variable++){
                //Polynomial v = val[variable->first];
                //for(int i = 0; i < variable->second; i++) evaluatedMonomial *= v;

                //search if variable is in map
                if(val.find(variable->first)!=val.end()){ //found
                    Polynomial v = val[variable->first];//substitute if this variable is in substitution
                    for(int i = 0; i < variable->second; i++) evaluatedMonomial *= v;
                }
                else{ //not found
                    stringstream variableStream;
                    variableStream<<variable->first;
                    //cout<<variable->first;
                    string variableString = variableStream.str();
                    Polynomial v = Polynomial(variableString);
                    for(int i = 0; i < variable->second; i++) evaluatedMonomial *= v;
                }

            }

            res +=  evaluatedMonomial * mon->second;
        }
        return res;
    }

    // End operators

    // Begin leading...
    ZZ_p leadingCoefficient() const{
        if ( coef.empty() ) return to_ZZ_p(0);
        return ( *coef.rbegin() ).second;
    }

    Monomial leadingMonomial() const{
        if ( coef.empty() ) return Monomial();
        return ( *coef.rbegin() ).first;
    }

    Polynomial leadingTerm() const{
        return Polynomial(leadingMonomial()) * leadingCoefficient();
    }
    // End leading...

    // Begin input output
    bool readStream(istream &in);

    void writeStream(ostream &out) const;

    void writeStreamWithGruppedMonomials(ostream &out, const vector <Monomial> &gruppingCoefficients) const;

    void writeStream(ZZ_p &val, ostream &out, bool ImplicitSign, bool ImplicitOne) const;

    friend istream & operator >> (istream &in, Polynomial &A) {
        A.readStream(in);
        return in;
    }

    friend ostream & operator << (ostream &out, Polynomial const &A) {
        A.writeStream(out);
        return out;
    }

    // End input output




};

Polynomial pow(Polynomial &P, unsigned int e);

// S-polynomial
Polynomial SPolynomial(Polynomial const &P, Polynomial const &Q);

// A-polynomial
Polynomial APolynomial(Polynomial const &P, Polynomial const &Q);

#endif // POLYNOMIAL_H
