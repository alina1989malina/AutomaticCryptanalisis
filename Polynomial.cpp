#include "Polynomial.h"

void Polynomial::removeNullCoefficients(){
    map <Monomial, ZZ_p>::iterator it = coef.begin();
    while ( it != coef.end() ) {
        if ( (*it).second == to_ZZ_p(0) ) coef.erase( it++ );
        else it++;
    }
}

// Begin input output
bool Polynomial::readStream(istream &in) {
    bool first = true;
    ZZ_p c;
    bool ImplicitOne;

    while ( readStream_(c, in , first, ImplicitOne) ) {
        first = false;
        Monomial mon;
        in >> mon; // Potrebbe essere vuoto

        if( ImplicitOne and mon.empty() ) {
            // Vuol dire che ha praticamente letto solo il segno
            break;
        }
        coef[mon] += c;
    }
    removeNullCoefficients();
    return true;
}

void Polynomial::writeStream(ostream &out) const{
    bool empty = true;
    bool first = true;

    vector < pair <Monomial, ZZ_p> > PrintOrder(coef.begin(), coef.end());
    sort(PrintOrder.begin(),PrintOrder.end(), PrintCmpTerm);
    for (vector < pair <Monomial, ZZ_p> >::iterator mon = PrintOrder.begin();mon!=PrintOrder.end();mon++ ) {
        ZZ_p c = mon->second;
        Monomial U = mon->first;

        if ( c == to_ZZ_p(0) ) continue;
        empty = false;

        if ( U.empty() ) {
            writeStream(c, out, first, false);
            //c.writeStream(out, first, false);
            //out << "+";
            //if(c!=to_ZZ_p(1)) out<<c;
        }
        else{
            writeStream(c, out, first, true);
            //out<<"+";
            //c.writeStream(out, first, true);
            //if(c!=to_ZZ_p(1)) out<<c;
            U.writeStream(out, true); //here U is always non empty
        }
        first = false;
    }//end for
    if ( empty ) out << "0";
}

void Polynomial::writeStreamWithGruppedMonomials(ostream &out, const vector <Monomial> &gruppingCoefficients) const{

    Polynomial rest(*this);
    for(unsigned int i=0;i<gruppingCoefficients.size();i++){
        // decompose Polynomial into sum of two parts:
        // one is divisible by monomial and second having no one monomial divisible by
        if(i!=0) out <<"+";
        Polynomial withMonom = rest.extractPartDivisibleBy(gruppingCoefficients[i]);
        out<<gruppingCoefficients[i];
        out<<"("<<withMonom<<")";
        rest = rest - withMonom;
    }

    out<<rest;

}

void Polynomial::writeStream(ZZ_p &val, ostream &out, bool ImplicitSign, bool ImplicitOne) const{
        if ( !ImplicitSign) out << '+';
        if ( ImplicitOne ) {
            if ( val != to_ZZ_p(1) ) out << val;
        }
        else out << val;
}

// Begin external functions

Polynomial pow(Polynomial &P, unsigned int e){
    if ( e == 0 ) return Polynomial ("1");
    if ( e == 1 ) return P;

    Polynomial Q = pow(P, e / 2);
    if ( e % 2 ) return P * Q * Q;
    return Q * Q;
}

// S-polynomial
Polynomial SPolynomial(Polynomial const &P, Polynomial const &Q){
    Monomial leadingLcm = lcm(P.leadingMonomial(), Q.leadingMonomial());
    Monomial coefP = leadingLcm / P.leadingMonomial();
    Monomial coefQ = leadingLcm / Q.leadingMonomial();

    Polynomial coefP2 = Polynomial(coefP) / P.leadingCoefficient();
    Polynomial coefQ2 = Polynomial(coefQ) / Q.leadingCoefficient();

    return coefP2*P-coefQ2*Q;
}
