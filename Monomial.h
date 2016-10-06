#ifndef MONOMIAL_H
#define MONOMIAL_H

#include <NTL/ZZ_p.h>
//#include <map>

//#include "Utility.h"
//#include "Variable.h"
#include "MonomialOrder.h"

using namespace std;
using namespace NTL;

NTL_CLIENT

//using namespace std;

class Monomial{
private:
    friend class PolynomialFraction;
    friend class PolynomialIdeal;
    friend class Polynomial;
    // (variable name, exponent) Exponent should always be > 0
    map <Variable, int> exponent;
    bool (*MonomialOrder)(const map <Variable, int> &a, const map <Variable, int> &b);
public:
    //Begin constructors

    Monomial(){
        exponent = map <Variable, int> ();
        MonomialOrder = LexicographicalOrder ;
    }

    Monomial(Variable x){
        exponent[x] = 1;
        MonomialOrder = LexicographicalOrder ;
    }

    Monomial(string S){
        stringstream Sstream(S);
        readStream(Sstream);
    }

    Monomial(const Monomial &mon){//copy constructor
        MonomialOrder = mon.MonomialOrder;
        for(map <Variable, int>::const_iterator variable = mon.exponent.begin(); variable!=mon.exponent.end(); variable++){
            exponent[variable->first] = variable->second;
        }
    }

    // End constructors

    bool empty() const{
        return exponent.empty();
    }

    bool containsVariable(Variable X) const{
        return exponent.find(X) != exponent.end();
    }

    ZZ_p evaluate(map <Variable, ZZ_p> &val) const;

    long int degree(){
        if(empty()){
            return -1;
        }
        else{
            long int res=0;
            for(map <Variable, int>::const_iterator variable = exponent.begin(); variable!=exponent.end(); variable++){
                res+= variable->second;
            }
            return res;
        }
    }

    // Begin operators (or similar)
    // TODO: It must be stated (ordinamento Monomiale)
    bool operator < (Monomial const &A) const{
        return MonomialOrder(exponent, A.exponent);
    }

    bool operator > (Monomial const &A) const{
        return (*this != A) and !(*this < A) ;
    }

    // FIXME: Cancellare il commento
    friend bool PrintCmp(Monomial const &A, Monomial const &B) {
        return A > B;
    }

    Monomial operator * (Monomial const &A) const;

    bool dominates(Monomial const &A) const;

    Monomial operator / (Monomial const &A) const;

    friend Monomial lcm(Monomial const &A, Monomial const &B) {
        Monomial res = A;
        for (map <Variable, int>::const_iterator variable = B.exponent.begin();variable != B.exponent.end();variable++ ) {
            Variable x = variable->first;
            res.exponent[x] = max(res.exponent[x], variable->second);
        }
        return res;
    }


    bool operator == (Monomial const &A) const{
        return exponent == A.exponent;
    }

    bool operator != (Monomial const &A) const{
        return exponent != A.exponent;
    }

    Monomial operator()(map <Variable, Monomial> &val) const; //substitution
    //End operators

    // Begin input output
    bool readStream(istream &in);

    void writeStream(ostream &out, bool ImplicitOne) const;

    friend istream & operator >> (istream &in, Monomial &A) {
        A.readStream(in);
        return in;
    }

    friend ostream&  operator << (ostream &out, Monomial const &A) {
        A.writeStream(out, false);
        return out;
    }
    // End input output


};

bool PrintCmpTerm(pair <Monomial, ZZ_p> const &left, pair <Monomial, ZZ_p> const &right);


#endif // MONOMIAL_H
