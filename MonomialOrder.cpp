#include "MonomialOrder.h"

bool LexicographicalOrder(map <Variable, int> const &A, map <Variable, int> const &B) {

    map <Variable, int>::const_iterator it1 = A.begin();
    map <Variable, int>::const_iterator end1 = A.end();
    map <Variable, int>::const_iterator it2 = B.begin();
    map <Variable, int>::const_iterator end2 = B.end();

        while ( it1 != end1 and it2 != end2 and (*it1) == (*it2) ) {
                it1++;
                it2++;
        }

        if ( it1 == end1 and it2 == end2 ) return false; //equality
        else if ( it1 == end1 ) return true;
        else if ( it2 == end2 ) return false;
        else if ( (*it1).first != (*it2).first ) {
                // 'x' is more important than 'y'
                return (*it1).first > (*it2).first;
        }
        else {
                return (*it1).second < (*it2).second;
        }
}


bool GradedReverse(map <Variable, int> const &A, map <Variable, int> const &B) {
        // Total Degree comparison
        int TotalDegree1 = 0;
        int TotalDegree2 = 0;
        for (map <Variable, int>::const_iterator var = A.begin(); var!= A.end(); var++)
            TotalDegree1 += var->second;
        for (map <Variable, int>::const_iterator var = B.begin(); var!= B.end(); var++)
            TotalDegree2 += var->second;

        if ( TotalDegree1 != TotalDegree2 ) return TotalDegree1 < TotalDegree2;

        // Inverted lex
        map <Variable, int>::const_iterator it1 = A.begin();
        map <Variable, int>::const_iterator end1 = A.end();
        map <Variable, int>::const_iterator it2 = B.begin();
        map <Variable, int>::const_iterator end2 = B.end();

        while ( it1 != end1 && it2 != end2 && (*it1) == (*it2) ) {
                it1++;
                it2++;
        }

        if ( it1 == end1 && it2 == end2 ) return false; //equality
        else if ( (*it1).first != (*it2).first ) {
                return (*it1).first > (*it2).first;
        }
        else {
                return (*it1).second > (*it2).second;
        }
}

//bool EliminationOrder(map <Variable, int> const &A, map <Variable, int> const &B)
bool EliminationOrder(map <Variable, int> &A, map <Variable, int> &B) {
        Variable EliminationVariable = Variable(Variable::EliminationVariable);
        bool member1 = A.find(EliminationVariable) != A.end();
        bool member2 = B.find(EliminationVariable) != B.end();

        if ( member1 && member2 ) {
            //int exponent1 = ( *( A.find(EliminationVariable)));
            int exponent1 = A[EliminationVariable];
            int exponent2 = B[EliminationVariable];
                //int exponent1 = A.at(EliminationVariable);
                //int exponent2 = B.at(EliminationVariable);
                if ( exponent1 != exponent2 ) {
                        return exponent1 < exponent2;
                }
        }
        else if( member1 && !member2 ) return false;
        else if( !member1 && member2 ) return true;

        return GradedReverse(A, B);
}

