#ifndef POLYNOMIALIDEAL_H
#define POLYNOMIALIDEAL_H

#include <set>
#include "Utility.h"
#include "Polynomial.h"
using namespace std;

class PolynomialIdeal
{
private:
    bool IsGrobnerBasis, IsMinimized, IsReduced;
    vector <Polynomial> generators;
public:
    // Begin constructors
    PolynomialIdeal(){
        IsGrobnerBasis = IsMinimized = IsReduced = true;
        generators = vector <Polynomial>();
    }

    PolynomialIdeal (vector <Polynomial> gen) {
        IsGrobnerBasis = IsMinimized = IsReduced = false;
        generators = gen;
    }

    PolynomialIdeal (vector <string> gen) {
        IsGrobnerBasis = IsMinimized = IsReduced = false;
        for (unsigned int i=0;i<gen.size(); i++)
            generators.push_back(Polynomial(gen[i]));
    }

    // End Constructors


    // Begin getters
    bool empty() const{
        return generators.empty();
    }

    vector <Polynomial> getIdealGenerators() {
        return generators;
    }

    unsigned int getNumberOfVariables(){

        std::set<Variable> variablesOfIdeal;

        for (unsigned int i=0;i<generators.size(); i++){
            //variablesOfIdeal.insert()
            for ( map <Monomial, ZZ_p>::const_iterator mon = generators[i].coef.begin(); mon!=generators[i].coef.end(); mon++) {
                Monomial currentMonomial(mon->first);

                for(map <Variable, int>::const_iterator variable = currentMonomial.exponent.begin(); variable!=currentMonomial.exponent.end(); variable++){
                    variablesOfIdeal.insert(variable->first);
                }
            }
        }

        return variablesOfIdeal.size();
    }

    unsigned int getNumberOfVariousMonomials(){

        std::set<Monomial> monomialsOfIdeal;

        for (unsigned int i=0;i<generators.size(); i++){
            for ( map <Monomial, ZZ_p>::const_iterator mon = generators[i].coef.begin(); mon!=generators[i].coef.end(); mon++) {
                monomialsOfIdeal.insert(mon->first);
            }
        }

        return monomialsOfIdeal.size();
    }
    // End getters

    // Begin basis modificators
    void removeNullPolynomials() {
        generators.erase(
                remove( generators.begin(), generators.end(), Polynomial(0) ),
                generators.end() );
    }

    void normalizeBasis() {
        for (unsigned int i = 0; i < generators.size(); i++) {
            generators[i] /= generators[i].leadingCoefficient();
        }
        sort(generators.begin(), generators.end());
    }
    // End basis modificators

    //Begin linearization
    void GaussianAlgorithm(){

        //firstly we sort generators according to leading monomials
        // first polynomial has leading monomial

        for (unsigned int i=0;i<generators.size(); i++){

            if(generators[i].degree()!=-1){
            //find coefficient for leading monomial in generators[i]
            ZZ_p leading = generators[i].leadingCoefficient();
            Monomial currentLeadingMonomial = generators[i].leadingMonomial();
            //multiply polynomial
            generators[i] = generators[i]*inv(leading);

            //then search this monmial in other generators and sub them after multiplication
            for(unsigned int j=i+1;j<generators.size();j++){
                if(generators[j].containsMonomial(currentLeadingMonomial)){
                    //multiply geneators[j] and sub them to eliminate monomial
                    ZZ_p currentLeading = generators[j].getCoefficientOfTermWithMonomial(currentLeadingMonomial);
                    generators[j] = generators[j]*(inv(currentLeading)) - generators[i];
                }
            }

        }

            //reverse motion the Gauss algorithm..
            //for(unsigned int j=0;j<i; j++)
        }



    }

    void XLAlgorithm(){
        for (unsigned int i=0;i<generators.size(); i++){
            //multiply all generators and add them to generators
            //do GaussAlgorithm
        }
    }

    void triangularDecomposition(){
        //int k;
    }

    // End linearization

    // Begin Grobner
    // Multivariate division for the generators
    Polynomial divisionRemainder(Polynomial &P) const;

    void BuchbergerAlgorithm(unsigned int i0);

    void involutiveAlgorithm();

    void calculateGrobnerBasis();

    void minimizeGrobnerBasis();

    void reduceGrobnerBasis();
    // End Grobner

    // Begin operators
    bool contains(Polynomial &P) {
    //bool contains(Polynomial const &P) {
        if ( !IsGrobnerBasis ) calculateGrobnerBasis();
        return divisionRemainder(P).empty();
    }

    bool operator == (PolynomialIdeal &I ) {
        if ( !IsReduced ) reduceGrobnerBasis();
        if ( !I.IsReduced ) I.reduceGrobnerBasis();
        normalizeBasis();
        I.normalizeBasis();

        return generators == I.generators;
    }

    PolynomialIdeal operator + (PolynomialIdeal const &I) const{
        vector <Polynomial> res( generators.size() + I.generators.size() );
        res.insert(res.end(), generators.begin(), generators.end());
        res.insert(res.end(), I.generators.begin(), I.generators.end());
        return PolynomialIdeal(res);
    }

    PolynomialIdeal operator * (PolynomialIdeal const &I) const{
        vector <Polynomial> res;
        for (unsigned int i = 0; i < generators.size(); i++) {
            for (unsigned int j = 0; j < generators.size(); j++) {
                res.push_back(generators[i] * generators[j]);
            }
        }
        return res;
    }

    friend PolynomialIdeal IdealIntersection (PolynomialIdeal &I, PolynomialIdeal &J) {
        Polynomial t = Polynomial(Monomial(Variable(Variable::EliminationVariable)));
        Polynomial t1 = Polynomial(to_ZZ_p(1)) - t;

        vector <Polynomial> NewGenerators;

        for (unsigned int i = 0; i < I.generators.size() ; i++)
            NewGenerators.push_back( t * Polynomial(I.generators[i]) );
        for (unsigned int i = 0; i < J.generators.size() ; i++)
            NewGenerators.push_back( t1 * Polynomial(J.generators[i]) );

        PolynomialIdeal NewIdeal = PolynomialIdeal(NewGenerators);

        NewIdeal.reduceGrobnerBasis();

        vector <Polynomial> IntersectionGenerators;

        // Come riesce ad accedere a generators? Visto che la specializzazione
        // è diversa (e generators è private)
        for (unsigned int i = 0; i < NewIdeal.generators.size();i++ ) {
            if ( !NewIdeal.generators[i].containsVariable(Variable(Variable::EliminationVariable)) ) {
                IntersectionGenerators.push_back(Polynomial(NewIdeal.generators[i]));
            }
        }
        return PolynomialIdeal(IntersectionGenerators);
    }
    // End operators

    // Begin input output
    friend ostream & operator << (ostream &out, PolynomialIdeal const &A) {
        for (unsigned int i = 0; i < A.generators.size(); i++ )
            cout << A.generators[i] << "\n";
        return out;
    }
    // End input output

};

vector <Polynomial> stringToPol(vector<string> S);

#endif // POLYNOMIALIDEAL_H
