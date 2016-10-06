#ifndef SYMBOLICMATRIX_H
#define SYMBOLICMATRIX_H

#include "PolynomialFraction.h"
#include "PolynomialIdeal.h"

class SymbolicMatrix
{

private:
    vector<vector <PolynomialFraction> > A;
public:
    SymbolicMatrix();

    SymbolicMatrix(string s, int numberOfCols, int numberOfRows, bool mode){
        setDims(numberOfCols,numberOfRows);
        fillSymbolicMatrix(s, mode);
    }

    void setDims(unsigned int cols, unsigned int rows);

    //Begin getters

    unsigned int getNumberOfCols() const {
        return A.size();
    }

    unsigned int getNumberOfRows() const {
        if(A.size()>0)
        return A[0].size();
        else return 0;
    }

    SymbolicMatrix getRow(int rowNumber){

        SymbolicMatrix res;
        if(rowNumber<getNumberOfRows()){

            res.setDims(getNumberOfCols(),1);

            for(int i=0;i<getNumberOfCols();i++){
                res.setEntry(rowNumber,i,A[rowNumber][i]);
            }

        }
        return res;

    }

    SymbolicMatrix getCol(int colNumber){

        SymbolicMatrix res;

        if(colNumber<getNumberOfCols()){

            res.setDims(1,getNumberOfRows());

            for(int i=0;i<getNumberOfRows();i++){
                res.setEntry(i,colNumber,A[i][colNumber]);
            }

        }
        return res;


    }

    //End getters

    void setEntry(unsigned int cols,unsigned int row, const PolynomialFraction &elem);
    PolynomialFraction getEntry(unsigned int col,unsigned int row) const{
        return A[col][row];
    }



    SymbolicMatrix operator+(const SymbolicMatrix& a) const;
    SymbolicMatrix operator-(const SymbolicMatrix& a) const;
    SymbolicMatrix operator*(const SymbolicMatrix& a) const;
    void operator*=(const SymbolicMatrix& a);
    void operator+=(const SymbolicMatrix& a);

    SymbolicMatrix operator-() const;

    PolynomialFraction determinant() const;

    SymbolicMatrix submatrix(int i, int j) const;
    SymbolicMatrix adjugate() const;

    bool isIdent();

    void fillSymbolicMatrix(string s, bool mode){
        //mode =0 means one-dimensional indexing, mode =1 means bi-dimensional

        int k = 0;
        for(unsigned int i = 0; i<getNumberOfCols();i++){
            for(unsigned int j = 0;j<getNumberOfRows();j++){
                stringstream currentEntry;

                if(mode==0){
                    currentEntry<<s<<"_"<<(i*getNumberOfRows()+j);
                }
                else{
                    currentEntry<<s<<"_"<<i<<"_"<<j;
                }

                PolynomialFraction currentPolynomialFraction(currentEntry.str());
                setEntry(i,j,currentPolynomialFraction);

                k++;
            }
        }
    }

    void fillWithUniformlyRandomConstants(){
        //mode =0 means one-dimensional indexing, mode =1 means bi-dimensional

        for(unsigned int i = 0; i<getNumberOfCols();i++){
            for(unsigned int j = 0;j<getNumberOfRows();j++){
                stringstream currentEntry;

                currentEntry<< random_ZZ_p();

                PolynomialFraction currentPolynomialFraction(currentEntry.str());
                setEntry(i,j,currentPolynomialFraction);

            }
        }
    }

    bool operator == (SymbolicMatrix const &B) const{
        if ((this->getNumberOfRows() == B.getNumberOfRows()) && (this->getNumberOfCols() == B.getNumberOfCols())){
            for(unsigned int i = 0;i<getNumberOfCols();i++){
                for(unsigned int j = 0;j<getNumberOfRows();j++){
                    if (this->getEntry(i,j) !=  B.getEntry(i,j)) return false;
                }
            }
            return true;
        }
        else return false;
    }

    bool operator != (SymbolicMatrix const &B) const{
        return !((*this)==B);
    }

    // Output stream
    friend ostream &operator<<(ostream &os, const SymbolicMatrix &inSymbolicMatrix){
        os <<"["<<endl;
        for(unsigned int i=0;i<inSymbolicMatrix.getNumberOfRows();i++){
            for(unsigned int j=0;j<inSymbolicMatrix.getNumberOfCols();j++){
                os<<inSymbolicMatrix.getEntry(i,j)<<"\t";
            }
            os<<endl;
        }

        os << "]"<<endl;
        return os;
    }


    bool unitTest(unsigned int maxDimension);


};

SymbolicMatrix inv(const SymbolicMatrix& a);

SymbolicMatrix transpose(const SymbolicMatrix& a);

SymbolicMatrix singleGauss(const SymbolicMatrix& a,const SymbolicMatrix& b);
SymbolicMatrix batchGauss(const SymbolicMatrix& a,const SymbolicMatrix& b);

#endif // SYMBOLICMATRIX_H
