#ifndef CNUMBER_H
#define CNUMBER_H

#include <QString>
#include <QDebug>

class CNumber {
    bool isRational;
    long long nom;
    long long denom;
    double fp;

public:
    CNumber(long long nominator=0, long long denominator=1);

    CNumber(double decimal_value);

    inline int nominator() const { return nom;}
    inline int denominator() const { return denom;}
    inline double decimal() const {return isRational ? (double)nom / (double)denom : fp;}

    inline bool rational() const { return isRational;}
    inline bool integer() const { return rational() && denominator() == 1;}

    CNumber operator+ ( const CNumber &other ) const;
    CNumber operator- ( const CNumber &other ) const;
    CNumber operator* ( const CNumber &other ) const;
    CNumber operator/ ( const CNumber &other ) const;

    inline CNumber operator+ ( double value ) const {return *this + CNumber(value);}
    inline CNumber operator- ( double value ) const {return *this - CNumber(value);}
    inline CNumber operator* ( double value ) const {return *this * CNumber(value);}
    inline CNumber operator/ ( double value ) const {return *this / CNumber(value);}

    CNumber &operator+= ( const CNumber &other );
    CNumber &operator-= ( const CNumber &other );
    CNumber &operator*= ( const CNumber &other );
    CNumber &operator/= ( const CNumber &other );

    static CNumber fromString(const QString &string);
    QString toString() const;

    inline operator double() const {return decimal();}

private:
    int gcd(int a, int b);
    void simplifyFraction();
};

inline CNumber operator+ ( double value, const CNumber &n ) {return CNumber(value)+n;}
inline CNumber operator- ( double value, const CNumber &n ) {return CNumber(value)-n;}
inline CNumber operator* ( double value, const CNumber &n ) {return CNumber(value)*n;}
inline CNumber operator/ ( double value, const CNumber &n ) {return CNumber(value)/n;}

inline QDebug operator<<(QDebug dbg, const CNumber n){
    return dbg.noquote() << n.toString();
}

#endif // CNUMBER_H
