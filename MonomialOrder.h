#ifndef MONOMIALORDER_H
#define MONOMIALORDER_H

#include "Utility.h"
#include "Variable.h"
using namespace std;


bool LexicographicalOrder(map <Variable, int> const &A, map <Variable, int> const &B) ;

bool GradedReverse(map <Variable, int> const &A, map <Variable, int> const &B);

bool EliminationOrder(map <Variable, int> &A, map <Variable, int> &B) ;

#endif // MONOMIALORDER_H
