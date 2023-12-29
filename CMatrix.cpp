#include "CMatrix.h"
#include <QDebug>

CMatrix::CMatrix(int M, int N)
    : m_M(M), m_N(N), m(M, CNumberVector(N)){}

CNumberVector &CMatrix::operator[](int i){
    return m[i];
}

CNumber CMatrix::getElement(int i, int j) const {
    return m[i][j];
}

CNumberVector CMatrix::getRow(int i) const {
    return m[i];
}

CNumberVector CMatrix::getColum(int j) const {
    CNumberVector res(N());
    for( int i=0; i < M(); ++i)
        res[i] = m[i][j];
    return res;
}

void CMatrix::setElement(int i, int j, CNumber value) {
    m[i][j]= value;
}

void CMatrix::setRow(int i, const CNumberVector &row)
{
    Q_ASSERT(i < M() && row.size() == N() );
    m[i] = row;
}

void CMatrix::setColumn(int j, const CNumberVector &column)
{
    Q_ASSERT(j < N() && column.size() == M() );
    for (int i = 0; i < M(); ++i) {
            m[i][j] = column[i];
    }
}

CMatrix& CMatrix::removeRow(int i)
{
    m.remove(i);
    --m_M;
    return *this;
}

CMatrix& CMatrix::removeColumn(int j)
{
    for(int i =0; i<M(); ++i)
        m[i].remove(j);
    --m_N;
    return *this;
}

void CMatrix::swapRows(int i1, int i2)
{
    CNumberVector temp = m[i1];
    m[i1] = m[i2];
    m[i2] = temp;
}

QPair<int, int> CMatrix::size() const {
    return QPair<int,int>(m_M,m_N);
}

bool CMatrix::operator==(const CMatrix &other) const
{
    if ( M()!= other.M() || N() != other.N())
        return false;

    for(int i=0; i<M(); ++i)
        for(int j=0; j<N(); ++j)
            if (getElement(i,j) != other.getElement(i,j))
                return false;
    return true;
}

void CMatrix::setSize(int M, int N) {

    if ( M != m_M ){
        m.resize(M);
        m_M=M;
    }

    for(int i=0; i < M; ++i){
        m[i].resize(N);
    }
    m_N=N;
}

CMatrix CMatrix::Zero(int m, int n)
{
    return CMatrix(m,n);
}

CMatrix CMatrix::Identity(int n)
{
    CMatrix mx(n,n);
    for (int i=0; i<n; ++i)
        mx[i][i] = CNumber(1,1);
    return mx;
}

CMatrix CMatrix::horzcat(CMatrix matrix, CMatrix other)
{
    Q_ASSERT(matrix.M() == other.M());

    CMatrix combined = matrix;
    combined.setSize(combined.M(), matrix.N()+other.N());
    for (int i=0; i<other.M(); ++i) {
        for(int j=0; j<other.N(); ++j){
            combined[i][j+matrix.N()] = other[i][j];
        }
    }
    return combined;
}

CMatrix CMatrix::vertcat(CMatrix matrix, CMatrix other)
{
    Q_ASSERT(matrix.N() == other.N());

    CMatrix combined = matrix;
    combined.setSize(matrix.M()+other.M(), combined.N());
    for (int i=0; i<other.M(); ++i) {
        for(int j=0; j<other.N(); ++j){
            combined[i+matrix.M()][j] = other[i][j];
        }
    }
    return combined;
}

QPair<CMatrix, CMatrix> CMatrix::horzsplit(int row)
{
    QPair<CMatrix, CMatrix> result;
    result.first.setSize(row, N());
    result.second.setSize(M()-row, N());

    for (int j=0; j<N(); ++j){
        for (int i=0; i<row; ++i)
                result.first[i][j]=getElement(i,j);
        for (int i=row; i<M(); ++i)
                result.second[i-row][j]=getElement(i,j);
    }

    return result;
}

QPair<CMatrix, CMatrix> CMatrix::vertsplit(int column)
{
    QPair<CMatrix, CMatrix> result;
    result.first.setSize(M(), column);
    result.second.setSize(M(), N()-column);

    for(int i=0; i<M(); ++i){
        for(int j=0; j<column; ++j)
                result.first[i][j]=getElement(i,j);
        for(int j=column; j<N(); ++j)
                result.second[i][j-column]=getElement(i,j);
    }

    return result;
}

CMatrix &CMatrix::operator *=(CNumber scalar)
{
    for (int i = 0; i < M(); ++i)
        m[i] *= scalar;
    return *this;
}

CMatrix CMatrix::operator *(CNumber scalar) const
{
    return CMatrix(*this) *= scalar;
}

QString CMatrix::toString() const
{
    QString res;
    res += "[";
    for ( int i=0; i < M(); ++i ){
        res += "[";
        for (int j=0; j < N(); ++j )
            res += m[i][j].toString() + (j == N()-1 ? "" : ",");
        res += QString("]") + (i == M()-1 ? "" : ",");
    }
    res += "]";
    return res;
}


QDebug operator<<(QDebug dbg, const CMatrix m)
{
    if (m.M() == 0 || m.N() == 0)
        return dbg << "| |";

    for ( int i=0; i < m.M(); ++i ){
        dbg.nospace() << "|";
        for (int j=0; j < m.N(); ++j ){
            dbg.space();
            dbg.noquote() << m.getElement(i,j).toString();
            dbg.nospace();
        }
        dbg << QString("|") + (i==m.M()-1?"":"\n");
    }
    return dbg.space();
}

CMatrix CMatrix::echelonForm() const{
    CMatrix m = *this;
    // i_l and j_l are row and column index of the current leading one
    // i and j are indexes of the current element

    for(int i_l=0, j_l=0; i_l<m.M() && j_l<m.N(); ++i_l, ++j_l){
        //qDebug() << QString("Leading Row:%1 Leading Column:%2").arg(i_l+1).arg(j_l+1);

        if (m[i_l][j_l] == 0) {
            // swap with a row that has a nonzero element in column j
            for (int swapWith=i_l+1; swapWith<m.M(); ++swapWith){
                if (m[swapWith][j_l] != 0){
                    //qDebug() << QString("R%1 <- R%2").arg(i_l+1).arg(swapWith+1);
                    //qDebug() << QString("R%1 <- R%2").arg(swapWith+1).arg(i_l+1);
                    m.swapRows(i_l, swapWith);
                    //qDebug() << m;
                    break;
                }
            }
            if (m[i_l][j_l] == 0){ // swap failed
                i_l -=1;    // continue with the next column
                continue;   // but stay on the same row (to push zero row vectors down)
            }
        }

        CNumber cFactor = 1.0 / m[i_l][j_l];

        //qDebug() << QString("R%1 <- R%1 * %2").arg(i_l+1).arg(cFactor.toString());
        m[i_l] *= cFactor;
        //qDebug() << m;

        for (int i=i_l+1; i<m.M(); ++i){

            CNumber rowMultiple = m[i][j_l];
            if(rowMultiple == 0)
                continue;

            //qDebug() << QString("R%1 <- R%1 - %2 * R%3").arg(i+1).arg(rowMultiple.toString()).arg(i_l+1);
            m[i] -= rowMultiple * m[i_l];
            //qDebug() << m;
        }
    }


    return m;
}

CMatrix CMatrix::echelonFormReduced() const{
    CMatrix m = *this;
    m = m.echelonForm();
    for (int i_l=m.M()-1; i_l > 0; --i_l ){

        if (m[i_l].isZeroVector())
            continue;
        int j_l = m[i_l].indexOf(CNumber(1,1));

        //qDebug() << QString("Leading Row:%1 Leading Column:%2").arg(i_l+1).arg(j_l+1);

        for (int i = i_l-1; i >= 0; --i){
            CNumber rowMultiple = m[i][j_l];
            if(rowMultiple == 0)
                continue;

            //qDebug() << QString("R%1 <- R%1 - %2 * R%3").arg(i+1).arg(rowMultiple.toString()).arg(i_l+1);
            m[i] -= rowMultiple * m[i_l];
            //qDebug() << m;
        }
    }
    return m;
}

CMatrix CMatrix::transpose() const
{
    CMatrix result(N(), M());

    for (int i=0; i<M(); ++i)
        result.setColumn(i, getRow(i));

    return result;
}

CMatrix CMatrix::inverse() const
{
    if (!isSquare())
        return CMatrix();

    //qDebug() << "Adjoin the identity matrix to A -> [A|I]";
    CMatrix combined = CMatrix::horzcat(*this, Identity(M()));
    //qDebug() << combined;
    combined = combined.echelonFormReduced();
    //qDebug() << "Check wheter left matrix is the identity matrix";
    QPair<CMatrix, CMatrix> res = combined.vertsplit(N());
    //qDebug() << res.first;

    return (res.first == Identity(M())) ? res.second : CMatrix();
}

CNumber CMatrix::det() const {
    CMatrix mx = *this;
    CNumber result(1,1);
    // i_l and j_l are row and column index of the current leading one
    // i and j are indexes of the current element

    for(int i_l=0, j_l=0; i_l<mx.M() && j_l<mx.N(); ++i_l, ++j_l){
        //qDebug() << QString("Leading Row:%1 Leading Column:%2").arg(i_l+1).arg(j_l+1);

        if (mx[i_l][j_l] == 0) {
            // swap with a row that has a nonzero element in column j
            for (int swapWith=i_l+1; swapWith<mx.M(); ++swapWith){
                if (mx[swapWith][j_l] != 0){
                    //qDebug() << QString("R%1 <- R%2").arg(i_l+1).arg(swapWith+1);
                    //qDebug() << QString("R%1 <- R%2").arg(swapWith+1).arg(i_l+1);
                    //qDebug() << QString("det(A)=%1 * (-1)...").arg(result.toString());
                    mx.swapRows(i_l, swapWith);
                    result *= -1.0;
                    //qDebug() << mx;
                    break;
                }
            }
            if (mx[i_l][j_l] == 0){ // swap failed
                if(mx[i_l].isZeroVector()){
                    //qDebug() << QString("Zero Row");
                    return CNumber(0,1);
                }
                i_l -=1;    // continue with the next column
                continue;   // but stay on the same row
            }
        }

        CNumber cFactor =  mx[i_l][j_l];

        //qDebug() << QString("R%1 <- R%1 * %2").arg(i_l+1).arg(cFactor.toString());
        //qDebug() << QString("det(A)= %1 * (%2)...").arg(result.toString()).arg(cFactor.toString());
        mx[i_l] *= 1.0 / cFactor;
        result *= cFactor;
        //qDebug() << mx;

        for (int i=i_l+1; i<mx.M(); ++i){

            CNumber rowMultiple = mx[i][j_l];
            if(rowMultiple == 0)
                continue;

            //qDebug() << QString("R%1 <- R%1 - %2 * R%3").arg(i+1).arg(rowMultiple.toString()).arg(i_l+1);
            mx[i] -= rowMultiple * mx[i_l];
            //qDebug() << mx;
        }
    }

    return result;
}

CMatrix CMatrix::adj() const
{
    CMatrix Cofact(M(), N());

    for (int i=0; i<M(); ++i) {
        for (int j = 0; j < N(); ++j) {
            CMatrix minor = *this;
            Cofact[i][j] = minor.removeRow(i).removeColumn(j).det()
                         * (((i+j)%2) ? CNumber(-1,1) : CNumber(1,1));
        }
    }
    return Cofact.transpose();
}
