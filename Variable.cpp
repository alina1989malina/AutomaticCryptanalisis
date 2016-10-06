#include "Variable.h"

char a[]={'@'};

//int a[]={-17};

const vector<int> Variable::EliminationVariable(a,a+1);

// Begin input output
/*
bool Variable::readStream(istream &in) {

    char c;
    if( !in.get( c ) )
    {
        if(tuple.empty())
            tuple.push_back(c);
        else tuple[0] = c;
        return false;
    }

    if(tuple.empty())
        tuple.push_back(c);
    else tuple[0] = c;

    if ( ( c < 'a' || 'z' < c ) && ( c < 'A' || 'Z' < c ) ) {
        in.unget();
        return false;
    }

    int n;
    in.get( c );
    if ( c== '[' ) {
        if ( !(in >> n) ) return false;
        tuple.push_back(n);
    }
    else{
        in.unget();
        return true;
    }

    in.get( c );//"]"
    in.get( c );
    if ( c== '[' ) {
        if ( !(in >> n) ) return false;
        tuple.push_back(n);
    }
    else in.unget();

    return true;
}*/



bool Variable::readStream(istream &in) {

    tuple.clear();

    char c;
    if( !in.get( c ) )
    {
        if(tuple.empty())
            tuple.push_back(c);
        else tuple[0] = c;
        return false;
    }

    if(tuple.empty())
        tuple.push_back(c);
    else tuple[0] = c;

    if ( ( c < 'a' || 'z' < c ) && ( c < 'A' || 'Z' < c ) ) {
        in.unget();
        return false;
    }

    int n;
    in.get( c );
    if ( c== '_' ) {

        if ( !(in >> n) ) return false;
        if(tuple.size()==1)
            tuple.push_back(n);
        else
            tuple[1] = n;
        return true;
    }
    else{
        in.unget();
        return true;
    }
/*
    in.get( c );
    if ( c== '_' ) {
        if ( !(in >> n) ) return false;
        tuple.push_back(n);
    }
    else in.unget();
*/
    return true;
}
