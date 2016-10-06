#include "YagisavaCryptosystem.h"

YagisavaCryptosystem::YagisavaCryptosystem()
{
    secretKey.setDims(2,2);
    z_.resize(2);
    for(unsigned int i =0;i<z_.size();i++){
        z_[i] = random_ZZ_p();// to_ZZ_p(RandomBnd(to_int(ZZ_p::ModulusSize())));
    }
    secretKey.fillWithUniformlyRandomConstants();

    cout<<"Secret key:"<<endl;
    cout<<"K = "<<secretKey<<endl;
    cout<<"K^-1 = "<<inv(secretKey)<<endl;
    cout<<"z = (";
    for(unsigned int i =0;i<z_.size();i++){
        cout<< z_[i]<<",";
    }
    cout<<")";

}

SymbolicOctonion YagisavaCryptosystem::encrypt(const PolynomialFraction &m){

    stringstream plaintextStream;
    plaintextStream << m;
    string plaintextString = plaintextStream.str();

    //Step 1: making SymbolicOctonion
    SymbolicOctonion O (plaintextString+string("+r_0"),plaintextString+string("+r_1"),plaintextString+string("+r_2"),plaintextString+string("+r_3"),plaintextString+string("+r_4"),plaintextString+string("+r_5"),plaintextString+string("+r_6"),plaintextString+string("+r_7"));
    SymbolicOctonion x(string("x_0"),string("x_1"),string("x_2"),string("x_3"),string("x_4"),string("x_5"),string("x_6"),string("x_7"));

    //let's k=s=1
    SymbolicOctonion y(string("y_0"),string("y_1"),string("y_2"),string("y_3"),string("y_4"),string("y_5"),string("y_6"),string("y_7"));
    SymbolicOctonion a(string("A"),string("B"),string("C"),string("D"),string("E"),string("F"),string("G"),string("H"));
    SymbolicOctonion z(string("J"),string("K"),string("L"),string("I"),string("N"),string("P"),string("Q"),string("R"));

    O = y * O * inv(y);

    return O;
/*
    SymbolicOctonion* y = new SymbolicOctonion[s];
    //filling y_i'ths
    for(int i=0;i<s;i++){
        stringstream s1; s1 << "y_0_"<<i;
        stringstream s2; s2 << "y_1_"<<i;
        stringstream s3; s3 << "y_2_"<<i;
        stringstream s4; s4 << "y_3_"<<i;
        stringstream s5; s5 << "y_4_"<<i;
        stringstream s6; s6 << "y_5_"<<i;
        stringstream s7; s7 << "y_6_"<<i;
        stringstream s8; s8 << "y_7_"<<i;

        y[i]= SymbolicOctonion(s1.str(),s2.str(),s3.str(),s4.str(),s5.str(),s6.str(),s7.str(),s8.str()  );
    }


    SymbolicOctonion* a = new SymbolicOctonion[k];
    //filling a_i'ths
    for(int i=0;i<k;i++){
        stringstream s1; s1 << "a[0]["<<i<<"]";
        stringstream s2; s2 << "a[1]["<<i<<"]";
        stringstream s3; s3 << "a[2]["<<i<<"]";
        stringstream s4; s4 << "a[3)("<<i<<")";
        stringstream s5; s5 << "a[4)("<<i<<")";
        stringstream s6; s6 << "a[5)("<<i<<")";
        stringstream s7; s7 << "a[6)("<<i<<")";
        stringstream s8; s8 << "a[7)("<<i<<")";

        a[i]= SymbolicOctonion(s1.str(),s2.str(),s3.str(),s4.str(),s5.str(),s6.str(),s7.str(),s8.str() );
    }

    SymbolicOctonion* z = new SymbolicOctonion[k];
    //filling z_i'ths
    for(int i=0;i<k;i++){
        stringstream s1; s1 << "z(0)("<<i<<")";
        stringstream s2; s2 << "z(1)("<<i<<")";
        stringstream s3; s3 << "z(2)("<<i<<")";
        stringstream s4; s4 << "z(3)("<<i<<")";
        stringstream s5; s5 << "z(4)("<<i<<")";
        stringstream s6; s6 << "z(5)("<<i<<")";
        stringstream s7; s7 << "z(6)("<<i<<")";
        stringstream s8; s8 << "z(7)("<<i<<")";

        z[i]= SymbolicOctonion(s1.str(),s2.str(),s3.str(),s4.str(),s5.str(),s6.str(),s7.str(),s8.str() );

        //z[i]= SymbolicOctonion("z(0)("+i+")","z(1)("+i+")","z(2)("+i+")","z(3)("+i+")","z(4)("+i+")","z(5)("+i+")","z(6)("+i+")","z(7)("+i+")" );
    }




    for(int i = s-1; i>0; i--){// making m with wave
        //cout<<y[0].e0;
        O = y[i] * O;
        O = O * inv(y[i]);
    }

    SymbolicOctonion C = x;

    for(int i = 0; i<k; i++){ //making C
        C = inv(a[i])* C;
        C*=z[i];
    }

    C = O*C;

    for(int i = k-1; i<0; i--){ //making C
        C = C*z[i];
        C = inv(a[i])* C;
    }


    //Step 2: output SymbolicOctonion
    ofstream outfile;
    outfile.open ("YagisavaCPA.txt");

    /*
    for(unsigned i=0;i<8;i++){
        outfile<<"e("<<i<<")(0) = "<< C.e0 <<endl; //C.e0
        outfile<<"e("<<i<<")(1) = "<< C.e1 <<endl; //C.e1
        outfile<<"e("<<i<<")(2) = "<< C.e2 <<endl; //C.e2
        outfile<<"e("<<i<<")(3) = "<< C.e3 <<endl; //C.e3
        outfile<<"e("<<i<<")(4) = "<< C.e4 <<endl; //C.e4
        outfile<<"e("<<i<<")(5) = "<< C.e5 <<endl; //C.e5
        outfile<<"e("<<i<<")(6) = "<< C.e6 <<endl; //C.e6
        outfile<<"e("<<i<<")(7) = "<< C.e7 <<endl; //C.e7

        //for(unsigned j=0;j<8;j++){
            //outfile<<"e("<<i<<")("<<j<<") = m + r(0)("<<")" <<endl; //C.e0
        //}
    }
    */
}

SymbolicMatrix YagisavaCryptosystem::encryptMatrix2by2(const PolynomialFraction &m){
    SymbolicMatrix a;
    a.setDims(2,2);
    PolynomialFraction r = PolynomialFraction(random_ZZ_p());

    a.setEntry(0,0,r*PolynomialFraction(z_[0]));//a_i = r*z_i
    a.setEntry(0,1,r*PolynomialFraction(z_[1]));
    a.setEntry(1,0,r*PolynomialFraction(-z_[1]));
    a.setEntry(1,1,r*PolynomialFraction(z_[0]));

    return secretKey*a*inv(secretKey);
}
