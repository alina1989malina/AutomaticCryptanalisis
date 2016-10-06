#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>


#include <limits.h>
#include <NTL/ZZ.h>

#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_pXFactoring.h>
#include <NTL/mat_poly_ZZ_p.h>
#include <NTL/vec_ZZ_p.h>
#include <NTL/mat_ZZ_p.h>

#include "PolynomialIdeal.h"
#include "SymbolicOctonion.h"
#include "SymbolicMatrix.h"
#include "Cryptosystems/YagisavaCryptosystem.h"


using namespace std;
using namespace NTL;

NTL_CLIENT

void tryYagisava(){

    unsigned s = 1; //number of
    unsigned k = 1; //number of

    //PolynomialFraction PolFr(string("m+a"));

    //Step 1: making SymbolicOctonion
    SymbolicOctonion O ( string("m+r_0"),string("m+r_1"),string("m+r_2"),string("m+r_3"),string("m+r_4"),string("m+r_5"),string("m+r_6"),string("m+r_7"));
    SymbolicOctonion x(string("x_0"),string("x_1"),string("x_2"),string("x_3"),string("x_4"),string("x_5"),string("x_6"),string("x_7"));

    //let's k=s=1
    SymbolicOctonion y(string("j"),string("k"),string("l"),string("i"),string("n"),string("p"),string("q"),string("r"));
    SymbolicOctonion a(string("A"),string("B"),string("C"),string("D"),string("E"),string("F"),string("G"),string("H"));

    SymbolicOctonion z(string("J"),string("K"),string("L"),string("I"),string("N"),string("P"),string("Q"),string("R"));

    SymbolicOctonion O1 ( string("a_0x_0+b_0x_1+c_0x_2+d_0x_3+e_0x_4+f_0x_5+g_0x_6+h_0x_7"),string("a_1x_0+b_1x_1+c_1x_2+d_1x_3+e_1x_4+f_1x_5+g_1x_6+h_1x_7"),string("a_2x_0+b_2x_1+c_2x_2+d_2x_3+e_2x_4+f_2x_5+g_2x_6+h_2x_7"),string("a_3x_0+b_3x_1+c_3x_2+d_3x_3+e_3x_4+f_3x_5+g_3x_6+h_3x_7"),string("a_4x_0+b_4x_1+c_4x_2+d_4x_3+e_4x_4+f_4x_5+g_4x_6+h_4x_7"),string("a_5x_0+b_5x_1+c_5x_2+d_5x_3+e_5x_4+f_5x_5+g_5x_6+h_5x_7"),string("a_6x_0+b_6x_1+c_6x_2+d_6x_3+e_6x_4+f_6x_5+g_6x_6+h_6x_7"),string("a_7x_0+b_7x_1+c_7x_2+d_7x_3+e_7x_4+f_7x_5+g_7x_6+h_7x_7"));
    SymbolicOctonion O2 ( string("j_0x_0+k_0x_1+l_0x_2+m_0x_3+n_0x_4+o_0x_5+p_0x_6+q_0x_7"),string("j_1x_0+k_1x_1+l_1x_2+m_1x_3+n_1x_4+o_1x_5+p_1x_6+q_1x_7"),string("j_2x_0+k_2x_1+l_2x_2+m_2x_3+n_2x_4+o_2x_5+p_2x_6+q_2x_7"),string("j_3x_0+k_3x_1+l_3x_2+m_3x_3+n_3x_4+o_3x_5+p_3x_6+q_3x_7"),string("j_4x_0+k_4x_1+l_4x_2+m_4x_3+n_4x_4+o_4x_5+p_4x_6+q_4x_7"),string("j_5x_0+k_5x_1+l_5x_2+m_5x_3+n_5x_4+o_5x_5+p_5x_6+q_5x_7"),string("j_6x_0+k_6x_1+l_6x_2+m_6x_3+n_6x_4+o_6x_5+p_6x_6+q_6x_7"),string("j_7x_0+k_7x_1+l_7x_2+m_7x_3+n_7x_4+o_7x_5+p_7x_6+q_7x_7"));
    SymbolicOctonion O3 ( string("r_0x_0+s_0x_1+t_0x_2+u_0x_3+v_0x_4+w_0x_5+y_0x_6+z_0x_7"),string("r_1x_0+s_1x_1+t_1x_2+u_1x_3+v_1x_4+w_1x_5+y_1x_6+z_1x_7"),string("r_2x_0+s_2x_1+t_2x_2+u_2x_3+v_2x_4+w_2x_5+y_2x_6+z_2x_7"),string("r_3x_0+s_3x_1+t_3x_2+u_3x_3+v_3x_4+w_3x_5+y_3x_6+z_3x_7"),string("r_4x_0+s_4x_1+t_4x_2+u_4x_3+v_4x_4+w_4x_5+y_4x_6+z_4x_7"),string("r_5x_0+s_5x_1+t_5x_2+u_5x_3+v_0x_4+w_5x_5+y_5x_6+z_5x_7"),string("r_6x_0+s_6x_1+t_6x_2+u_6x_3+v_6x_4+w_6x_5+y_6x_6+z_6x_7"),string("r_7x_0+s_7x_1+t_7x_2+u_7x_3+v_7x_4+w_7x_5+y_7x_6+z_7x_7"));

    ofstream outfile;
    outfile.open ("OctonionSubstitutionAssociativeness.txt");

    YagisavaCryptosystem yagisavaCryptosystem;
    SymbolicOctonion c1 = yagisavaCryptosystem.encrypt(PolynomialFraction(string("m_1")));
    SymbolicOctonion c2 = yagisavaCryptosystem.encrypt(PolynomialFraction(string("m_2")));
    SymbolicOctonion c3 = yagisavaCryptosystem.encrypt(PolynomialFraction(string("m_3")));

    outfile<<c1 <<endl;
    outfile<<c2 <<endl;
    outfile<<c3 <<endl;

    SymbolicOctonion res1 = c1(c2);
    SymbolicOctonion res2 = c2(c1);
    outfile<< res1;
    outfile<< res2;

    /*
    outfile<< O1;
    outfile<< O2;
    outfile<< O3;*/
    //SymbolicOctonion res1 = O1(O2);//O1(O2(O3));//O1(y);//x(y);
    //O = x+y;//y * O * inv(y);
    //outfile<< res1;

    //SymbolicOctonion res2 = O2(O1);//O2(O1(O3));//O1(O2) (O3);
   //O = x+y;//y * O * inv(y);
   //outfile<< res2;

   if(res1 == res2){
       cout <<"res1==res2"<<endl;
   }
   else{
       cout <<"res1!=res2"<<endl;
   }

   outfile.close();
}

SymbolicMatrix fillYagisavaMatrix(string s){ // relocate to class YagisavaCryptosystem

    SymbolicMatrix a;

    a.setDims(8,8);
    //filling diagonal of the matrix a
    for(int i=0;i<8;i++){
        a.setEntry(i,i,PolynomialFraction(s+string("_0")));
    }

    a.setEntry(1,0,-PolynomialFraction(s+string("_1")));
    a.setEntry(2,0,-PolynomialFraction(s+string("_2")));
    a.setEntry(3,0,-PolynomialFraction(s+string("_3")));
    a.setEntry(4,0,-PolynomialFraction(s+string("_4")));
    a.setEntry(5,0,-PolynomialFraction(s+string("_5")));
    a.setEntry(6,0,-PolynomialFraction(s+string("_6")));
    a.setEntry(7,0,-PolynomialFraction(s+string("_7")));

    a.setEntry(2,1,-PolynomialFraction(s+string("_4")));
    a.setEntry(3,1,-PolynomialFraction(s+string("_7")));
    a.setEntry(4,1,PolynomialFraction(s+string("_2")));
    a.setEntry(5,1,-PolynomialFraction(s+string("_6")));
    a.setEntry(6,1,PolynomialFraction(s+string("_5")));
    a.setEntry(7,1,PolynomialFraction(s+string("_3")));

    a.setEntry(3,2,-PolynomialFraction(s+string("_5")));
    a.setEntry(4,2,-PolynomialFraction(s+string("_1")));
    a.setEntry(5,2,PolynomialFraction(s+string("_3")));
    a.setEntry(6,2,-PolynomialFraction(s+string("_7")));
    a.setEntry(7,2,PolynomialFraction(s+string("_6")));

    a.setEntry(4,3,-PolynomialFraction(s+string("_6")));
    a.setEntry(5,3,-PolynomialFraction(s+string("_2")));
    a.setEntry(6,3,PolynomialFraction(s+string("_4")));
    a.setEntry(7,3,-PolynomialFraction(s+string("_1")));

    a.setEntry(5,4,-PolynomialFraction(s+string("_7")));
    a.setEntry(6,4,-PolynomialFraction(s+string("_3")));
    a.setEntry(7,4,PolynomialFraction(s+string("_5")));

    a.setEntry(6,5,-PolynomialFraction(s+string("_1")));
    a.setEntry(7,5,-PolynomialFraction(s+string("_4")));

    a.setEntry(7,6,-PolynomialFraction(s+string("_2")));

    //filling upper triangular antisymmetric
    for(int j = 1;j<8;j++){
        for(int i=0;i<j;i++){
            a.setEntry(i,j,PolynomialFraction(-a.getEntry(j,i)));
        }
    }

    return a;
}

SymbolicMatrix fillAntiYagisavaMatrix(string s){ // relocate to class YagisavaCryptosystem

    SymbolicMatrix a;

    a.setDims(8,8);
    //filling diagonal of the matrix a
    for(int i=0;i<8;i++){
        a.setEntry(i,i,PolynomialFraction(string("a_0")));
    }

    a.setEntry(1,0,-PolynomialFraction(s+string("_1")));
    a.setEntry(2,0,-PolynomialFraction(s+string("_2")));
    a.setEntry(3,0,-PolynomialFraction(s+string("_3")));
    a.setEntry(4,0,-PolynomialFraction(s+string("_4")));
    a.setEntry(5,0,-PolynomialFraction(s+string("_5")));
    a.setEntry(6,0,-PolynomialFraction(s+string("_6")));
    a.setEntry(7,0,-PolynomialFraction(s+string("_7")));

    a.setEntry(2,1,PolynomialFraction(s+string("_4")));
    a.setEntry(3,1,PolynomialFraction(s+string("_7")));
    a.setEntry(4,1,-PolynomialFraction(s+string("_2")));
    a.setEntry(5,1,PolynomialFraction(s+string("_6")));
    a.setEntry(6,1,-PolynomialFraction(s+string("_5")));
    a.setEntry(7,1,-PolynomialFraction(s+string("_3")));

    a.setEntry(3,2,PolynomialFraction(s+string("_5")));
    a.setEntry(4,2,PolynomialFraction(s+string("_1")));
    a.setEntry(5,2,-PolynomialFraction(s+string("_3")));
    a.setEntry(6,2,PolynomialFraction(s+string("_7")));
    a.setEntry(7,2,-PolynomialFraction(s+string("_6")));

    a.setEntry(4,3,PolynomialFraction(s+string("_6")));
    a.setEntry(5,3,PolynomialFraction(s+string("_2")));
    a.setEntry(6,3,-PolynomialFraction(s+string("_4")));
    a.setEntry(7,3,PolynomialFraction(s+string("_1")));

    a.setEntry(5,4,PolynomialFraction(s+string("_7")));
    a.setEntry(6,4,PolynomialFraction(s+string("_3")));
    a.setEntry(7,4,-PolynomialFraction(s+string("_5")));

    a.setEntry(6,5,PolynomialFraction(s+string("_1")));
    a.setEntry(7,5,PolynomialFraction(s+string("_4")));

    a.setEntry(7,6,PolynomialFraction(s+string("_2")));

    //filling upper triangular antisymmetric
    for(int j = 1;j<8;j++){
        for(int i=0;i<j;i++){
            a.setEntry(i,j,PolynomialFraction(-a.getEntry(j,i)));
        }
    }

    return a;
}


int main(int argc, char *argv[])
{
    unsigned p = 5;// matrix dimension
    ZZ_p::init(to_ZZ(p));

    SymbolicMatrix A,B,A_anti,B_anti,C,D,C_anti,D_anti, A_inv, AXB;
    A.setDims(8,8);
    B.setDims(8,8);

    A = fillYagisavaMatrix(string("a"));
    A_inv = inv(A);
    B = fillYagisavaMatrix(string("b"));
    A_anti = fillAntiYagisavaMatrix(string("a"));
    B_anti = fillAntiYagisavaMatrix(string("b"));
    C = A*B;
    D = B*A;
    C_anti = A_anti*B;
    D_anti = B_anti*A;
    //cout<<x<<endl<<endl;
  //cout<<B<<endl<<endl;
    //cout<<A*B<<endl<<endl;
 //cout<<B*A<<endl<<endl;

 //if (C==D) cout<<"eq"<<endl;
// else cout<<"not eq"<<endl;

 SymbolicOctonion x("x_0","x_1","x_2","x_3","x_4","x_5","x_6","x_7");
 SymbolicOctonion a("a_0","a_1","a_2","a_3","a_4","a_5","a_6","a_7");
 SymbolicOctonion b("b_0","b_1","b_2","b_3","b_4","b_5","b_6","b_7");

 SymbolicOctonion ax = a*x;
 SymbolicOctonion xa = x*a;



// if (ax==xa) cout<<"ax = xa"<<endl;
// else cout<<"ax != xa"<<endl;
// cout<<"ax = "<<ax<<endl;
// cout<<"xa = "<<xa<<endl;

// Variable x0("x_0");
 //cout<<ax.e7.getNumerator().extractPartDivisibleBy(x0)<<endl;

  cout<<"ax.getMatrix() result:"<<endl<<ax.getMatrix()<<endl;

 cout<<"xa.getMatrix() result:"<<endl<<xa.getMatrix()<<endl;

 if (xa.getMatrix() == A_anti) cout<<"xa.getMatrix() == A_anti"<<endl;
 else cout<<"xa.getMatrix() != A_anti"<<endl;



 SymbolicOctonion bax = b*ax;
 cout<<"bax.getMatrix() result:"<<endl<<bax.getMatrix()<<endl;
 if (bax.getMatrix() == C) cout<<"eq and => b*(a*x) equiv to A*B"<<endl;
 else cout<<"not eq"<<endl;

 SymbolicOctonion axb = ax*b;
 AXB = axb.getMatrix();
 cout<<"axb.getMatrix() result:"<<endl<<axb.getMatrix()<<endl;
 if (axb.getMatrix() == D_anti) cout<<"eq and => (a*x)*b equiv to "<<endl;
 else cout<<"not eq"<<endl;

 cout<<"Shhh: "<<AXB*A_inv<<endl;










/*
    vector <Polynomial> gen;
    gen.push_back(string("x_1y_2+z+3w+1"));
    gen.push_back(string("y_1z+2x-3w^4"));
    gen.push_back(string("zx_1-y_1+4w"));


    PolynomialIdeal I = PolynomialIdeal(gen);
    cout<<I<<endl;

    //I.reduceGrobnerBasis();
    //I.normalizeBasis();
    cout << I << "\n";* /

    SymbolicMatrix a(fillYagisavaMatrix());
    cout<<a*a<<endl<<endl;
/*
    SymbolicMatrix k;

    k.setDims(2,2);
    k.fillSymbolicMatrix(string("k"),0);

    cout<<k<<endl;
    cout<<inv(k)<<endl;
    cout<<k*inv(k)<<endl;

    k.setDims(3,3);
    k.fillSymbolicMatrix(string("k"),0);

    cout<<k<<endl;
    cout<<inv(k)<<endl;
    cout<<k*inv(k)<<endl;

    k.setDims(5,5);
    k.fillSymbolicMatrix(string("k"),0);

    cout<<k<<endl;
    cout<<inv(k)<<endl;
    cout<<k*inv(k)<<endl;* /

    YagisavaCryptosystem toyYagisavaCryptosystem;

    SymbolicMatrix c[10];//ciphertexts

    c[0] = toyYagisavaCryptosystem.encryptMatrix2by2(PolynomialFraction("1"));
    c[1] = toyYagisavaCryptosystem.encryptMatrix2by2(PolynomialFraction("2"));
    c[2] = toyYagisavaCryptosystem.encryptMatrix2by2(PolynomialFraction("3"));
    c[3] = toyYagisavaCryptosystem.encryptMatrix2by2(PolynomialFraction("4"));
    c[4] = toyYagisavaCryptosystem.encryptMatrix2by2(PolynomialFraction("4"));
    c[5] = toyYagisavaCryptosystem.encryptMatrix2by2(PolynomialFraction("4"));
    c[6] = toyYagisavaCryptosystem.encryptMatrix2by2(PolynomialFraction("4"));
    c[7] = toyYagisavaCryptosystem.encryptMatrix2by2(PolynomialFraction("4"));
    c[8] = toyYagisavaCryptosystem.encryptMatrix2by2(PolynomialFraction("4"));
    c[9] = toyYagisavaCryptosystem.encryptMatrix2by2(PolynomialFraction("4"));


    ofstream outfile;
    outfile.open ("YagisavaBreaking.txt");

    outfile<<endl<<a*a<<endl<<endl;

    vector <Polynomial> gen;

    SymbolicMatrix k;//hypotetic secret key
    k.setDims(2,2);
    k.fillSymbolicMatrix("k",0);

    cout<<endl<<c[0]<<endl;

    outfile<<"C ="<<endl<<c[0]<<endl<<endl;
    outfile<<"K ="<<endl<<k<<endl<<endl;
    outfile<<"K^-1 ="<<endl<<inv(k)<<endl<<endl;
    SymbolicMatrix t = k*c[0]*inv(k);
    outfile<<"K*C*K^{-1} ="<<endl<<t<<endl<<endl;

    //we take diagonal entries and equalize them
    //and then add resulting polynomial to ideal

    gen.push_back(t.getEntry(0,0).getNumerator()-t.getEntry(1,1).getNumerator());
    gen.push_back(t.getEntry(1,0).getNumerator()+t.getEntry(0,1).getNumerator());


    //SymbolicMatrix k;//hypotetic secret key
    k.setDims(2,2);
    k.fillSymbolicMatrix("k",0);

    cout<<endl<<c[0]*c[5]<<endl;

    outfile<<"C ="<<endl<<c[0]*c[5]<<endl<<endl;
    outfile<<"K ="<<endl<<k<<endl<<endl;
    outfile<<"K^-1 ="<<endl<<inv(k)<<endl<<endl;
    SymbolicMatrix tt = k*c[0]*c[5]*inv(k);
    outfile<<"K*C*K^{-1} ="<<endl<<t<<endl<<endl;

    //we take diagonal entries and equalize them
    //and then add resulting polynomial to ideal

    gen.push_back(tt.getEntry(0,0).getNumerator()-tt.getEntry(1,1).getNumerator());
    gen.push_back(tt.getEntry(1,0).getNumerator()+tt.getEntry(0,1).getNumerator());


    PolynomialIdeal I = PolynomialIdeal(gen);
    cout<<I<<endl;
    I.GaussianAlgorithm();
    cout<<I<<endl;

    outfile.close();




    /*
    k.setDims(2,2);
    k.fillSymbolicMatrix("k",0);
    SymbolicMatrix c;
    c.setDims(2,2);
    c.fillSymbolicMatrix("c",0);

    ofstream outfile;
    outfile.open ("YagisavaCryptosystem.txt");

    outfile<<"C ="<<endl<<c<<endl<<endl;
    outfile<<"K ="<<endl<<k<<endl<<endl;
    outfile<<"K^-1 ="<<endl<<inv(k)<<endl<<endl;
    SymbolicMatrix r = k*c*inv(k);
    outfile<<"K*C*K^{-1} ="<<endl<<r<<endl<<endl;


    //we take diagonal entries and equalize them
    //and then add resulting polynomial to ideal
    vector <Polynomial> gen;
    gen.push_back(r.getEntry(0,0).getNumerator()-r.getEntry(1,1).getNumerator());
    gen.push_back(r.getEntry(1,0).getNumerator()+r.getEntry(0,1).getNumerator());

    PolynomialIdeal I = PolynomialIdeal(gen);
    cout<<I<<endl;
    //I.GaussianAlgorithm();
    //cout<<I<<endl;

    outfile.close();
*/

/*
    ofstream outfile;
    outfile.open ("InvA.txt");

    outfile<<a<<endl<<endl;
    outfile<<inv(a)<<endl;

    outfile.close();
*/




/*
    SymbolicOctonion C = x;

    C = inv(a)* C * z;

    C = O*C;

    C = C*z;
    C = inv(a)* C;


    //Step 2: output SymbolicOctonion
    ofstream outfile;
    outfile.open ("YagisavaCPAsmall.txt");

    outfile<<"e(0) = "<< C.e0 <<endl; //C.e0
    outfile<<"e(1) = "<< C.e1 <<endl; //C.e1
    outfile<<"e(2) = "<< C.e2 <<endl; //C.e2
    outfile<<"e(3) = "<< C.e3 <<endl; //C.e3
    outfile<<"e(4) = "<< C.e4 <<endl; //C.e4
    outfile<<"e(5) = "<< C.e5 <<endl; //C.e5
    outfile<<"e(6) = "<< C.e6 <<endl; //C.e6
    outfile<<"e(7) = "<< C.e7 <<endl; //C.e7

    outfile.close();




    /*
    //Step 1: making SymbolicOctonion
    SymbolicOctonion O ("m+r[0]","m+r[1]","m+r[2]","m+r[3]","m+r[4]","m+r[5]","m+r[6]","m+r[7]");
    //SymbolicOctonion x("x0","x1","x2","x3","x4","x5","x6","x7");
    SymbolicOctonion* y = new SymbolicOctonion[s];/*
    //filling y_i'ths
    for(int i=0;i<s;i++){
        stringstream s1; s1 << "y[0)("<<i<<")";
        stringstream s2; s2 << "y[1)("<<i<<")";
        stringstream s3; s3 << "y[2)("<<i<<")";
        stringstream s4; s4 << "y[3)("<<i<<")";
        stringstream s5; s5 << "y[4)("<<i<<")";
        stringstream s6; s6 << "y[5)("<<i<<")";
        stringstream s7; s7 << "y[6)("<<i<<")";
        stringstream s8; s8 << "y[7)("<<i<<")";

        y[i]= SymbolicOctonion(s1.str(),s2.str(),s3.str(),s4.str(),s5.str(),s6.str(),s7.str(),s8.str()  );
    }

    SymbolicOctonion* a = new SymbolicOctonion[k];
    //filling a_i'ths
    for(int i=0;i<k;i++){
        stringstream s1; s1 << "a[0)("<<i<<")";
        stringstream s2; s2 << "a[1)("<<i<<")";
        stringstream s3; s3 << "a[2)("<<i<<")";
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
    * /

    outfile<<"e(0) = "<< C.e0 <<endl; //C.e0
    outfile<<"e(1) = "<< C.e1 <<endl; //C.e1
    outfile<<"e(2) = "<< C.e2 <<endl; //C.e2
    outfile<<"e(3) = "<< C.e3 <<endl; //C.e3
    outfile<<"e(4) = "<< C.e4 <<endl; //C.e4
    outfile<<"e(5) = "<< C.e5 <<endl; //C.e5
    outfile<<"e(6) = "<< C.e6 <<endl; //C.e6
    outfile<<"e(7) = "<< C.e7 <<endl; //C.e7


    outfile.close();*/
    system("pause");
}
