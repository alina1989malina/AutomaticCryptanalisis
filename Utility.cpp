#include "Utility.h"


bool signReadStream(istream &in, long long int &sign) {
        char c;
        if( !in.get(c) ) {
                return false;
        }
        else if ( c == '-' ) {
                sign = -1;
                return true;
        }
        else if ( c == '+' ) {
                sign = 1;
                return true;
        }

        in.unget();
        return false;
}

unsigned long long int integerGcdComputation(unsigned long long int x, unsigned long long int y) {
        if ( y == 0 ) return x;
        return integerGcdComputation(y, x % y);
}

long long int integerGcd(long long int x, long long int y) {
        if ( x < 0 ) x = -x;
        if ( y < 0 ) y = -y;
        if ( x < y ) swap(x, y);
        return integerGcdComputation(x, y);
}

bool readStream_(ZZ_p &val, istream &in, bool ImplicitSign, bool &ImplicitOne) {
        long long int sign = 1;

        if( !ImplicitSign ) {
                if ( !signReadStream(in, sign) ) {
                        return false;
                }
        }

        long long int NoSign = 1;
        char c;

        if ( !in.get(c) ) return false; // Forse dovrei ungettare?
        in.unget();

        if ( ('0' <= c && c <= '9') ||
                         ( ImplicitSign && (c == '-' || c == '+') ) ) {
                ImplicitOne = false;
                in >> NoSign;
        }
        else {
                ImplicitOne = true;
        }

        val = to_ZZ_p( sign * NoSign );
        //val = ( sign * NoSign ) % mod;

        //if ( val < 0 ) val += mod;

        return true;
}

/*
void writeStream(ZZ_p &val, ostream &out, bool ImplicitSign, bool ImplicitOne) {
        if ( !ImplicitSign) out << '+';
        if ( ImplicitOne ) {
            if ( val != to_ZZ_p(1) ) out << val;
        }
        else out << val;
}*/
