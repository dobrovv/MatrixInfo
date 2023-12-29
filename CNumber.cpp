#include "CNumber.h"
//#include <QStringList>

CNumber::CNumber(long long nominator, long long denominator)
    : isRational(true), nom(nominator), denom(denominator)
{
    simplifyFraction();
//    if(denominator > 1000000){
//        fp = double(nom) / double(denom);
//        isRational = false;
//    }

}


CNumber::CNumber(double decimal_value)
{

    if ( decimal_value == static_cast<int>(decimal_value) ){
        isRational = true;
        nom = decimal_value;
        denom = 1;
    } else {
        isRational = false;
        fp = decimal_value;
    }
}

CNumber CNumber::operator+(const CNumber &other) const {
    if (rational() && other.rational())
        return CNumber( nominator()*other.denominator() + denominator()*other.nominator()
                        , denominator()*other.denominator() );
    else
        return decimal() + other.decimal();
}

CNumber CNumber::operator-(const CNumber &other) const {
    return *this + (other * CNumber(-1.0));
}

CNumber CNumber::operator*(const CNumber &other) const {
    if (rational() && other.rational())
        return CNumber( nominator()*other.nominator(), denominator()*other.denominator() );
    else
        return decimal() * other.decimal();
}

CNumber CNumber::operator/(const CNumber &other) const {
    if (rational() && other.rational())
        return CNumber( nominator()*other.denominator(), denominator()*other.nominator() );
    else
        return decimal() / other.decimal();
}

CNumber &CNumber::operator+=(const CNumber &other) {
    return *this = *this + other;
}

CNumber &CNumber::operator-=(const CNumber &other) {
    return *this = *this -other;
}

CNumber &CNumber::operator*=(const CNumber &other) {
    return *this = *this * other;
}

CNumber &CNumber::operator/=(const CNumber &other) {
    return *this = *this / other;
}

CNumber CNumber::fromString(const QString &string)
{
    CNumber res;
    QStringList numbers = string.split("/");
    if ( numbers.size() > 1 ){   // is rational

        double nomin = numbers[0].toDouble(); // nominator
        double denom = numbers[1].toDouble(); // denominator

        if (nomin != int(nomin) || denom != int(denom) ) {
            return CNumber(nomin/denom);
        } else {
            return CNumber(int(nomin), int(denom));
        }
    }
    return CNumber(string.toDouble());
}

QString CNumber::toString() const {
    if ( rational() ) {
        if (denominator() == 1) {
            return QString::number(nominator());
        } else {
            return QString("%1/%2").arg(nominator()).arg(denominator());
        }
    } else {
        return QString::number(fp);
    }
}



int CNumber::gcd(int a, int b){
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void CNumber::simplifyFraction() {
    int divisor = gcd(nom, denom);
    nom /= divisor;
    denom /= divisor;
}
