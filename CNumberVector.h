#ifndef CNUMBERVECTOR_H
#define CNUMBERVECTOR_H

#include <QVector>
#include "CNumber.h"

class CNumberVector : public QVector<CNumber> {

public:
    CNumberVector(const QVector<CNumber>& qvec = QVector<CNumber>())
        : QVector(qvec) {}

    explicit CNumberVector(int N);

    inline bool isZeroVector() const {
        return this->count(CNumber()) == this->size();
    }

    CNumberVector &operator*=(const CNumber scalar);
    CNumberVector &operator/=(const CNumber scalar);

    CNumberVector operator* (const CNumber scalar) const;
    CNumberVector operator/ (const CNumber scalar) const;

    CNumberVector &operator+=(const CNumberVector &other);
    CNumberVector &operator-=(const CNumberVector &other);
    CNumberVector &operator*=(const CNumberVector &other);
    CNumberVector &operator/=(const CNumberVector &other);

    CNumberVector operator+(const CNumberVector &other) const;
    CNumberVector operator-(const CNumberVector &other) const;
    CNumberVector operator*(const CNumberVector &other) const;
    CNumberVector operator/(const CNumberVector &other) const;

};

inline CNumberVector operator* (const CNumber scalar, const CNumberVector& vec) {
    return vec * scalar;
}

inline CNumberVector operator/ (const CNumber scalar, const CNumberVector& vec) {
    return vec * scalar;
}

QDebug operator<<(QDebug dbg, const CNumberVector vec);


inline CNumberVector& operator/ (const CNumber scalar, CNumberVector& vec);

#endif // CNUMBERVECTOR_H
