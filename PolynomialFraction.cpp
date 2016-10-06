#include "PolynomialFraction.h"

PolynomialFraction::PolynomialFraction()
{
    denominator = Polynomial(to_ZZ_p(1));
}

PolynomialFraction PolynomialFraction::operator * (PolynomialFraction const &A) const{

    Polynomial newNumerator = numerator*A.numerator;
    Polynomial newDenominator = denominator*A.denominator;
    PolynomialFraction res(newNumerator,newDenominator);
    res.normalize();
    return res;//PolynomialFraction(newNumerator/gcd(newNumerator,newDenominator),newDenominator/gcd(newNumerator,newDenominator));
}

PolynomialFraction PolynomialFraction::operator / (PolynomialFraction const &A) const{
    Polynomial newNumerator = numerator*A.denominator;
    Polynomial newDenominator = denominator*A.numerator;
    PolynomialFraction res(newNumerator,newDenominator);
    res.normalize();
    return res;//PolynomialFraction(newNumerator,newDenominator);//PolynomialFraction(newNumerator/gcd(newNumerator,newDenominator),newDenominator/gcd(newNumerator,newDenominator));
}

PolynomialFraction PolynomialFraction::operator()(map <Variable, PolynomialFraction> &val) const{

    PolynomialFraction tempNumerator = PolynomialFraction(to_ZZ_p(0));

    //evaluate numerator
    for(map <Monomial, ZZ_p>::const_iterator mon = numerator.coef.begin();mon!=numerator.coef.end(); mon++) {
        PolynomialFraction evaluatedMonomial(to_ZZ_p(1));


        for(map <Variable, int>::const_iterator variable = mon->first.exponent.begin(); variable != mon->first.exponent.end(); variable++){

            //search if variable is in map
            if(val.find(variable->first)!=val.end()){ //found
                PolynomialFraction v = val[variable->first];//substitute if this variable is in substitution
                for(int i = 0; i < variable->second; i++) evaluatedMonomial *= v;
            }
            else{ //not found
                stringstream variableStream;
                variableStream<<variable->first;
                //cout<<variable->first;
                string variableString = variableStream.str();
                PolynomialFraction v = PolynomialFraction(variableString);
                for(int i = 0; i < variable->second; i++) evaluatedMonomial *= v;
            }


        }

        tempNumerator += evaluatedMonomial* mon->second ;
    }

    //evaluate denominator
    PolynomialFraction tempDenominator = PolynomialFraction(to_ZZ_p(0));
    for(map <Monomial, ZZ_p>::const_iterator mon = denominator.coef.begin();mon!=denominator.coef.end(); mon++) {
        PolynomialFraction evaluatedMonomial(to_ZZ_p(1));

        for(map <Variable, int>::const_iterator variable = mon->first.exponent.begin(); variable != mon->first.exponent.end(); variable++){
            //search if variable is in map
            if(val.find(variable->first)!=val.end()){ //found
                PolynomialFraction v = val[variable->first];//substitute if this variable is in substitution
                for(int i = 0; i < variable->second; i++) evaluatedMonomial *= v;
            }
            else{//not found
                stringstream variableStream;
                variableStream<<variable->first;
                //cout<<variable->first;
                string variableString = variableStream.str();
                PolynomialFraction v = PolynomialFraction(variableString);
                for(int i = 0; i < variable->second; i++) evaluatedMonomial *= v;
            }
        }

        tempDenominator +=  evaluatedMonomial * mon->second;
    }

    return tempNumerator / tempDenominator;//(tempNumerator / tempDenominator).normalize();//what about division by zero?
}
