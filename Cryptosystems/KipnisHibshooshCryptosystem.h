#ifndef KIPNISHIBSHOOSHCRYPTOSYSTEM_H
#define KIPNISHIBSHOOSHCRYPTOSYSTEM_H

#include "SymbolicMatrix.h"

class KipnisHibshooshCryptosystem
{
private:
    SymbolicMatrix K;//the secret key
public:
    KipnisHibshooshCryptosystem();

    SymbolicMatrix encrypt(const PolynomialFraction &m);

    PolynomialFraction decrypt(const SymbolicMatrix &c);

    bool checkCorrectness();
};

#endif // KIPNISHIBSHOOSHCRYPTOSYSTEM_H
