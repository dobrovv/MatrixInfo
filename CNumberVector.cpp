#include "CNumberVector.h"

#include <QDebug>

CNumberVector::CNumberVector(int N)
    : QVector<CNumber>(N,CNumber()) {}

CNumberVector CNumberVector::operator*(const CNumber scalar) const {
    CNumberVector res = *this;
    return res *= scalar;
}

CNumberVector CNumberVector::operator/(const CNumber scalar) const {
    CNumberVector res = *this;
    return res /= scalar;
}

CNumberVector &CNumberVector::operator*=(const CNumber scalar) {
    for(int i=0; i<size(); ++i)
        (*this)[i] = (*this)[i] * scalar;
    return *this;
}

CNumberVector &CNumberVector::operator/=(const CNumber scalar) {
    return (*this) *= CNumber(1,1) / scalar;
}

CNumberVector &CNumberVector::operator+=(const CNumberVector &other) {
    Q_ASSERT(this->size() == other.size());
    for(int i=0; i<size(); ++i)
        (*this)[i] = (*this)[i] + other[i];
    return *this;
}

CNumberVector &CNumberVector::operator-=(const CNumberVector &other) {
    Q_ASSERT(this->size() == other.size());
    for(int i=0; i<size(); ++i)
        (*this)[i] = (*this)[i] - other[i];
    return *this;
}

CNumberVector &CNumberVector::operator*=(const CNumberVector &other) {
    Q_ASSERT(this->size() == other.size());
    for(int i=0; i<size(); ++i)
        (*this)[i] = (*this)[i] * other[i];
    return *this;
}

CNumberVector &CNumberVector::operator/=(const CNumberVector &other) {
    Q_ASSERT(this->size() == other.size());
    for(int i=0; i<size(); ++i)
        (*this)[i] = (*this)[i] / other[i];
    return *this;
}

CNumberVector CNumberVector::operator+(const CNumberVector &other) const {
    CNumberVector res = *this;
    return res += other;
}

CNumberVector CNumberVector::operator-(const CNumberVector &other) const {
    CNumberVector res = *this;
    return res -= other;
}

CNumberVector CNumberVector::operator*(const CNumberVector &other) const {
    CNumberVector res = *this;
    return res *= other;
}


CNumberVector CNumberVector::operator/(const CNumberVector &other) const {
    CNumberVector res = *this;
    return res /= other;
}



QDebug operator<<(QDebug dbg, const CNumberVector vec)
{
    dbg << "(";
    for ( int i=0; i < vec.size(); ++i )
        dbg.noquote() << vec[i].toString() + (i == vec.size() - 1 ? " )" : ",");
    return dbg.quote();
}
