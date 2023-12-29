#ifndef CMATRIX_H
#define CMATRIX_H

#include <QPair>

#include "CNumber.h"
#include "CNumberVector.h"

class CMatrix
{
private:
    int m_M, m_N;
    QVector<CNumberVector> m;

public:
    CMatrix(int M=0, int N=0);

    CNumberVector & operator[](int i);

    CNumber getElement(int i, int j) const;
    CNumberVector getRow(int i) const;
    CNumberVector getColum(int j) const;

    void setElement(int i, int j, CNumber value);
    void setRow(int i, const CNumberVector & row);
    void setColumn(int j, const CNumberVector & column);

    CMatrix &removeRow(int i);
    CMatrix &removeColumn(int j);

    void swapRows(int i1, int i2);

    int M() const {return m_M;}
    int N() const {return m_N;}
    QPair<int,int> size() const;

    bool operator== (const CMatrix& other ) const;

    void setSize(int M, int N);

    inline bool isSquare() const {return M()==N();}

    static CMatrix Zero(int m, int n);
    static CMatrix Identity(int n);

    static CMatrix horzcat(CMatrix matrix, CMatrix other);
    static CMatrix vertcat(CMatrix matrix, CMatrix other);

    QPair<CMatrix,CMatrix> horzsplit(int column);
    QPair<CMatrix,CMatrix> vertsplit(int row);

    CMatrix &operator *= (CNumber scalar);
    CMatrix operator * (CNumber scalar) const;

    QString toString() const;

    CMatrix echelonForm() const;
    CMatrix echelonFormReduced() const;
    CMatrix inverse() const;
    CMatrix transpose() const;

    CNumber det() const;
    CMatrix adj() const;
};

QDebug operator<<(QDebug dbg, const CMatrix m);

#endif // CMATRIX_H
