
#include "Monomial.h"

ZZ_p Monomial::evaluate(map <Variable, ZZ_p> &val) const{
    ZZ_p res = to_ZZ_p(1);
    for(map <Variable, int>::const_iterator variable = exponent.begin(); variable != exponent.end(); variable++){
        ZZ_p v = val[variable->first];
        for(int i = 0; i < variable->second; i++) res *= v;
    }
    return res;
}

// Begin operators (or similar)

Monomial Monomial::operator * (Monomial const &A) const{
    Monomial res=*this;
    for (map <Variable, int>::const_iterator variable = A.exponent.begin(); variable != A.exponent.end(); variable++) {
        res.exponent[variable->first] += variable->second;
    }
    return res;
}

bool Monomial::dominates(Monomial const &A) const{
    for (map <Variable, int>::const_iterator variable = A.exponent.begin(); variable != A.exponent.end(); variable++ ) {
        map <Variable, int>::const_iterator ExponentIter = exponent.find(variable->first);
        if ( (ExponentIter == exponent.end()) ||
                         (variable->second > (*ExponentIter).second )) {
                return false;
        }
    }
    return true;
}

Monomial Monomial::operator / (Monomial const &A) const{
    assert( dominates(A) ); //Forse è da togliere l'assert
    Monomial res;
    for (map <Variable, int>::const_iterator variable = exponent.begin(); variable != exponent.end(); variable++ ) {
        Variable x = variable->first;
        map <Variable, int>::const_iterator ExponentIter = A.exponent.find(x);
        if ( ExponentIter == A.exponent.end() ) {
                res.exponent[x] = variable->second;
        }
        else if ( variable->second > (*ExponentIter).second ) {
                res.exponent[x] = variable->second - (*ExponentIter).second;
        }
    }
    return res;
}

Monomial Monomial::operator()(map <Variable, Monomial> &val) const{ //substitution
    Monomial res ;
    for(map <Variable, int>::const_iterator variable = exponent.begin(); variable != exponent.end(); variable++){
        Monomial v = val[variable->first];
        //for(int i = 0; i < variable->second; i++) res *= v;
    }
    return res;
}

//End operators

// Begin input output

bool Monomial::readStream(istream &in) {
    Variable c;
    while ( c.readStream( in ) ) {
        int e = 1;
        char d;
        if ( in.get(d) ) {
            if ( d == '^' ) {
                if ( !( in >> e ) )
                    in.unget();
            }/*
            //begin attempt to use special symbols for power of variable (2 and 3)
            else if ( d == "²"[0] ) {
                if ( in.get(d) ) {
                    if ( d == "²"[1] ) e = 2;
                    else if ( d == "³"[1] ) e = 3;
                    else {
                        in.unget();
                        in.unget();
                    }
                }//end  if ( in.get(d) )
                else{
                    in.unget();
                }
            }*/
            else in.unget();
        }
        if ( e != 0 ) exponent[c] += e;
    }//end while

    return true;
}

void Monomial::writeStream(ostream &out, bool ImplicitOne) const{
    if ( empty() ) {
        if ( !ImplicitOne ) out << '1';
        return;
    }

    for( map <Variable, int>::const_iterator variable = exponent.begin(); variable != exponent.end(); variable++  ) {
        int e = variable->second;
        if (e == 0) continue;

        variable->first.writeStream( out );

        if ( e > 1 ) out << "^" << e;

        //if (e == 2) out << "²";//using special symbols for sqr and 3 power
        //if (e == 3) out << "³";
        //else if ( e > 3 ) out << "^" << e;
    }
}

bool PrintCmpTerm(pair <Monomial, ZZ_p> const &left, pair <Monomial, ZZ_p> const &right) {
    return PrintCmp(left.first, right.first);
}
