#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>

#include <NTL/ZZ_p.h>

using namespace std;
using namespace NTL;

NTL_CLIENT

#ifdef POLLY_DEBUG
        #define MP_WRITE(str) do { std::clog << str << std::endl; } while( false )
#else
        #define MP_WRITE(str) do { } while ( false )
#endif

bool signReadStream(istream &in, long long int &sign);

unsigned long long int integerGcdComputation(unsigned long long int x, unsigned long long int y);

long long int integerGcd(long long int x, long long int y);

bool readStream_(ZZ_p &val, istream &in, bool ImplicitSign, bool &ImplicitOne);

//void writeStream(ZZ_p &val, ostream &out, bool ImplicitSign, bool ImplicitOne);


#endif // UTILITY_H
