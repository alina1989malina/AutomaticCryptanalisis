#ifndef YAGISAVACRYPTOSYSTEM_H
#define YAGISAVACRYPTOSYSTEM_H

#include "SymbolicOctonion.h"
#include "SymbolicMatrix.h"

class YagisavaCryptosystem
{
public:
    YagisavaCryptosystem();
    YagisavaCryptosystem(int in_s, int in_k){
        s = in_s;
        k = in_k;
    }

    SymbolicOctonion encrypt(const PolynomialFraction &m);
    SymbolicMatrix encryptMatrix2by2(const PolynomialFraction &m);

    PolynomialFraction decrypt(const SymbolicOctonion &c);

    bool checkCorrectness();

private:
    //symbolic cryptosystem
    int s,k;
    vector <SymbolicOctonion> y;
    vector <SymbolicOctonion> a;
    vector <SymbolicOctonion> z;

    //an exemplary cryptosystem
    SymbolicMatrix secretKey;
    vector<ZZ_p> z_;
};

#endif // YAGISAVACRYPTOSYSTEM_H
