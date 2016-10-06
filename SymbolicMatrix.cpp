#include "SymbolicMatrix.h"

SymbolicMatrix::SymbolicMatrix()
{
}

void SymbolicMatrix::setDims(unsigned int cols, unsigned int rows){

    A.resize(cols);
    for(unsigned int i=0;i<cols;i++){
        A[i].resize(rows);
    }
}

SymbolicMatrix SymbolicMatrix::operator+(const SymbolicMatrix& a) const{
    SymbolicMatrix res(*this);
    res+=a;
    return res;
}

SymbolicMatrix SymbolicMatrix::operator*(const SymbolicMatrix& a) const{
    SymbolicMatrix res(*this);
    res*=a;
    return res;
}

void SymbolicMatrix::operator+=(const SymbolicMatrix &b){
    int resultNumberOfCols = (*this).getNumberOfRows();
    int resultNumberOfRows = b.getNumberOfCols();

    SymbolicMatrix result;
    result.setDims(resultNumberOfCols,resultNumberOfRows);

    for(unsigned i=0;i<result.getNumberOfCols();i++){
        for(unsigned j=0;j<result.getNumberOfRows();j++){
            PolynomialFraction temp(A[i][j]+ b.getEntry(i,j));
            result.setEntry(i,j,temp);
        }
    }
    (*this) = result;
}

void SymbolicMatrix::operator*=(const SymbolicMatrix &b){
    int resultNumberOfCols = (*this).getNumberOfRows();
    int resultNumberOfRows = b.getNumberOfCols();

    SymbolicMatrix result;
    result.setDims(resultNumberOfCols,resultNumberOfRows);

    for(unsigned i=0;i<result.getNumberOfCols();i++){
        for(unsigned j=0;j<result.getNumberOfRows();j++){
            PolynomialFraction temp(to_ZZ_p(0));
            for(unsigned k=0;k<getNumberOfCols();k++){
                temp+= A[i][k]* b.getEntry(k,j);
            }
            result.setEntry(i,j,temp);
        }
    }

    (*this) = result;
}

void SymbolicMatrix::setEntry(unsigned int col,unsigned int row, const PolynomialFraction &elem){
    A[col][row] = elem;
}

SymbolicMatrix inv(const SymbolicMatrix& a){

    unsigned n = a.getNumberOfRows();
    if(a.getNumberOfCols() != n){
        cout<<"inv: nonsquare matrix"<<endl;
        return a;
    }

    SymbolicMatrix result;

    result.setDims(n,n);

    if(n==1){
        result.setEntry(0,0,-a.getEntry(0,0));
        return result;
    }

    if(n==0){
        cout<<"You are trying to invert an empty matrix!"<<endl;
        result.setEntry(0,0,PolynomialFraction(to_ZZ_p(0)));
        return result;
    }

    PolynomialFraction determinant = a.determinant();
    SymbolicMatrix adj = a.adjugate();

    for(unsigned int i=0;i<n;i++){
        for(unsigned j=0;j<n;j++){
            result.setEntry(i,j,adj.getEntry(i,j)/determinant);
        }
    }

    return result;

    /* Victor's Variant:

    unsigned i,j,k,pos;

    vector <vector <PolynomialFraction> > m;
    m.resize(n);

    for(i = 0; i < n; i++){
        m[i].resize(2*n);

        for (j = 0; j < n; j++) {
            m[i][j].setEntry(a.getEntry(i,j));
            m[i][n+j].setEntry(PolynomialFraction(to_ZZ_p(0)));
        }

        m[i][n+i].setEntry(PolynomialFraction(to_ZZ_p(1)));

    }

    PolynomialFraction &det = PolynomialFraction(to_ZZ_p(1));

    for (k = 0; k < n; k++) {
        pos = -1;
        for (i = k; i < n; i++) {
            if (pos == -1 && !IsZero(t1)) {
               pos = i;
            }
        }
    }

    /*
    void inv(ZZ_p& d, mat_ZZ_p& X, const mat_ZZ_p& A)
    {
       long n = A.NumRows();
       if (A.NumCols() != n)
          Error("inv: nonsquare matrix");

       if (n == 0) {
          set(d);
          X.SetDims(0, 0);
          return;
       }

       long i, j, k, pos;
       ZZ t1, t2;
       ZZ *x, *y;

       const ZZ& p = ZZ_p::modulus();

       vec_ZZVec M;
       sqr(t1, p);//p=t^2
       mul(t1, t1, n);//t1*=n

       M.SetLength(n);

       for (i = 0; i < n; i++) {
          M[i].SetSize(2*n, t1.size());
          for (j = 0; j < n; j++) {
             M[i][j] = rep(A[i][j]);
             clear(M[i][n+j]);
          }
          set(M[i][n+i]);
       }

       ZZ det;
       set(det);//det=1

       for (k = 0; k < n; k++) {
          pos = -1;
          for (i = k; i < n; i++) {
             rem(t1, M[i][k], p);//t1=M[i][k] mod p
             M[i][k] = t1;
             if (pos == -1 && !IsZero(t1)) {
                pos = i;
             }
          }

          if (pos != -1) {
             if (k != pos) {
                swap(M[pos], M[k]);
                NegateMod(det, det, p);
             }

             MulMod(det, det, M[k][k], p);

             // make M[k, k] == -1 mod p, and make row k reduced

             InvMod(t1, M[k][k], p);
             NegateMod(t1, t1, p);
             for (j = k+1; j < 2*n; j++) {
                rem(t2, M[k][j], p);
                MulMod(M[k][j], t2, t1, p);
             }

             for (i = k+1; i < n; i++) {
                // M[i] = M[i] + M[k]*M[i,k]

                t1 = M[i][k];   // this is already reduced

                x = M[i].elts() + (k+1);
                y = M[k].elts() + (k+1);

                for (j = k+1; j < 2*n; j++, x++, y++) {
                   // *x = *x + (*y)*t1

                   mul(t2, *y, t1);
                   add(*x, *x, t2);
                }
             }
          }
          else {
             clear(d);
             return;
          }
       }

       X.SetDims(n, n);
       for (k = 0; k < n; k++) {
          for (i = n-1; i >= 0; i--) {
             clear(t1);
             for (j = i+1; j < n; j++) {
                mul(t2, rep(X[j][k]), M[i][j]);
                add(t1, t1, t2);
             }
             sub(t1, t1, M[i][n+k]);
             conv(X[i][k], t1);
          }
       }

       conv(d, det);
    }*/
}

SymbolicMatrix transpose(const SymbolicMatrix& a){
    SymbolicMatrix res;
    res.setDims(a.getNumberOfRows(),a.getNumberOfCols());
    for(int i=0;i<a.getNumberOfCols();i++){
        for(int j=0;j<a.getNumberOfRows();j++){
            res.setEntry(j,i,a.getEntry(i,j));
        }
    }

    return res;
}

SymbolicMatrix SymbolicMatrix::adjugate() const{

    unsigned n = getNumberOfRows();
    if(getNumberOfCols() != n){
        cout<<"inv: nonsquare matrix"<<endl;
        return SymbolicMatrix(*this);//PolynomialFraction(to_ZZ_p(0));
    }

    SymbolicMatrix result;

    result.setDims(n,n);

    for(unsigned int i=0;i<n;i++){
        for(unsigned int j=0;j<n;j++){
            PolynomialFraction currentEntry(PolynomialFraction(to_ZZ_p(static_cast<int>(pow(-1.0,(int)(i+j)))))  * (submatrix(i, j)).determinant());
            result.setEntry(j,i,currentEntry);
        }
    }
    return result;
}

PolynomialFraction SymbolicMatrix::determinant() const {
    unsigned n = getNumberOfRows();
    if(getNumberOfCols() != n){
        cout<<"inv: nonsquare matrix"<<endl;
        return PolynomialFraction(to_ZZ_p(0));
    }

    if(n==1){
        return A[0][0];//output the only matrix entry...
    }

    if(n==0){
        cout<<"Ypu are trying to evaluate the determinant of an empty matrix!"<<endl;
        return PolynomialFraction(to_ZZ_p(0));//output the only matrix entry...
    }

    PolynomialFraction res(to_ZZ_p(0));

    for(unsigned int i=0;i<n;i++){
        //cout<<submatrix(i, 0);
        res+= PolynomialFraction(to_ZZ_p(static_cast<int>(pow(-1.0,(int)i)))) * A[i][0] * (submatrix(i, 0)).determinant();
    }
    return res;
}

SymbolicMatrix SymbolicMatrix::submatrix(int i, int j) const {
    SymbolicMatrix res;

    res.setDims(getNumberOfCols()-1,getNumberOfRows()-1);

    int a = 0;

    for(unsigned int ii=0;ii<getNumberOfCols();ii++){
        if(ii==i) continue;	//Skip ith row
        //res[a] = new int[n - 1];
        int b = 0;

        for(int jj = 0; jj< getNumberOfRows(); jj++) {
            if(jj==j) continue;	//Skip jth column
            res.setEntry(a,b,A[ii][jj]);
            b++;
        }

        a++; //Increment row index
    }

    return res;
}

bool SymbolicMatrix::unitTest(unsigned int maxDimension){

    bool result = true;
    //SymbolicMatrix testMatrix;

    for(unsigned int i=1;i<=maxDimension;i++){
        setDims(i,i);
        //fill the matrix
        fillSymbolicMatrix("m", 0);

        //find inverse and multiply them
        SymbolicMatrix testMatrix (*this);
        testMatrix = testMatrix* inv(testMatrix);

        //we need to obtain Identity matrix

        //if not then cout i, matrix and return false
    }

    return result;
}
