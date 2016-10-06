#include "PolynomialIdeal.h"

Polynomial PolynomialIdeal::divisionRemainder(Polynomial &P) const{

    MP_WRITE("divisionRemainder");
    Polynomial remainder = Polynomial(to_ZZ_p(0));
    MP_WRITE("Polynomial = " << P << "\nStarting division:");
    while ( !P.empty() ) {
        cout<<"\t"<<P<<endl;
        MP_WRITE("\t" << P); //  /*
        bool divided = false;
        Monomial PleadMon = P.leadingMonomial();
        ZZ_p PleadCoef = P.leadingCoefficient();
        for (unsigned int i=0;i<generators.size(); i++ ) {
            Monomial QleadMon = generators[i].leadingMonomial();
            ZZ_p QleadCoef = generators[i].leadingCoefficient();

            if ( PleadMon.dominates(QleadMon) ) {
                Monomial DivisionMon = PleadMon / QleadMon;
                ZZ_p DivisionCoef = PleadCoef / QleadCoef;
                P -= generators[i] * Polynomial(DivisionMon) * DivisionCoef;
                divided = true;
                break;
            }
        }//end for
        if ( divided ) continue; // */

        Polynomial NewRemainder = P.leadingTerm();
        remainder += NewRemainder;
        P -= NewRemainder;
    }
    MP_WRITE("Remainder = " << remainder << "\n");

    return remainder;
}

void PolynomialIdeal::BuchbergerAlgorithm(unsigned int i0) {
    MP_WRITE("Generators:");
    for (unsigned int i=0;i<generators.size(); i++) MP_WRITE("\t" <<  generators[i]);

    MP_WRITE("S-Polynomials:");
    for (unsigned int i = i0; i < generators.size(); i++) {
        for (unsigned int j = 0; j < i; j++) {
            Monomial LeadMonP = generators[i].leadingMonomial();
            Monomial LeadMonQ = generators[j].leadingMonomial();

            // If leading monomial are coprime, than it is not necessary
            // to check the S-polynomial
            if (LeadMonP * LeadMonQ == lcm(LeadMonP, LeadMonQ)) continue;

            Polynomial S = SPolynomial(generators[i], generators[j]);

            MP_WRITE("\t" << S);

            Polynomial remainder = divisionRemainder(S);
            if ( !remainder.empty() ) {
                MP_WRITE("Adding to generators: " << remainder << "\n");
                generators.push_back(remainder);

                BuchbergerAlgorithm(i);
                return;
            }
        }
    }
}

void PolynomialIdeal::calculateGrobnerBasis() {
    removeNullPolynomials();

    if ( !IsGrobnerBasis ) {
        BuchbergerAlgorithm(0);
        IsGrobnerBasis = true;
    }
}

void PolynomialIdeal::minimizeGrobnerBasis() {
    if ( !IsGrobnerBasis ) calculateGrobnerBasis();
    if ( IsMinimized ) return;

    vector <Polynomial> res = generators;
    for ( unsigned int i = 0; i < generators.size(); i++) {
        for ( unsigned int j = i+1; j < generators.size(); j++) {
            Monomial IleadMon = generators[i].leadingMonomial();
            Monomial JleadMon = generators[j].leadingMonomial();

            if ( JleadMon.dominates(IleadMon) ) res[j] = to_ZZ_p(0);
            else if ( IleadMon.dominates(JleadMon) ) res[i] = to_ZZ_p(0);
        }
    }

    generators = res;
    removeNullPolynomials();

    IsMinimized = true;
}

void PolynomialIdeal::reduceGrobnerBasis() {

    if ( !IsMinimized ) minimizeGrobnerBasis();
    if ( IsReduced ) return;

    bool changed = true;
    while (changed) {
        changed = false;
        vector <Polynomial> NewGenerators;
        for (unsigned int i = 0; i < generators.size(); i++) {
            vector <Polynomial> GeneratorsCopy = generators;
            GeneratorsCopy.erase(GeneratorsCopy.begin()+i);
            PolynomialIdeal ReducedIdeal = PolynomialIdeal(GeneratorsCopy);
            Polynomial NewGenerator = ReducedIdeal.divisionRemainder(generators[i]);
            if ( NewGenerator != generators[i] ) changed = true;
            NewGenerators.push_back(NewGenerator);
        }
        generators = NewGenerators;
        removeNullPolynomials();
    }
    IsReduced = true;

}




vector <Polynomial> stringToPol(vector<string> S) {
    vector <Polynomial> res;
    for (unsigned int i =0;i<S.size(); i++)
        res.push_back( Polynomial(S[i]) );
    return res;
}

