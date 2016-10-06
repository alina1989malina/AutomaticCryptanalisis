#ifndef VARIABLE_H
#define VARIABLE_H

#include "Utility.h"
using namespace std;

class Variable
{
private:
    vector <int> tuple;
public:
    //static const char EliminationVariable = '@';
    static const vector <int> EliminationVariable;

    // Begin constructors
    Variable() {}

    Variable(const vector<int> x) {
        tuple = x;
    }
    /*Variable(char x) {
        c = x;
    }*/
    Variable(string s) {
        stringstream Sstream(s);
        readStream(Sstream);
    }
    // End constructors

    // Begin operators
    bool const operator < (Variable X) const{
        return tuple < X.tuple;
    }

    bool const operator > (Variable X) const{
        return tuple > X.tuple;
    }

    bool const operator == (Variable X) const{
        return tuple == X.tuple;
    }

    bool const operator != (Variable X) const{
        return tuple != X.tuple;
    }
    // End operators

    // Begin input output
    bool readStream(istream &in);

    void writeStream(ostream &out) const{
            out << char(tuple[0]);

            if(tuple.size()>1)
                out<<"_"<<tuple[1];
            if(tuple.size()>2)
                out<<"_"<<tuple[2];
    }
    // End input output
};

#endif // VARIABLE_H
