#include <iostream>
#include <vector>
#include <string>

class BigInteger {
private:
    std::vector <int> z;
    bool negative = false;
    void normalize(BigInteger& x) {
        int64_t delta = 0;
        for (uint64_t i = 0; i < x.z.size(); ++i) {
            x.z[i] += delta;
            delta = x.z[i] / 10;
            x.z[i] = x.z[i] % 10;
            if (x.z[i] < 0) {
                --delta;
                x.z[i] += 10;
            }
        }
        if (delta < 0) {
            x.negative = !x.negative;
            delta = -delta;
        }
        while (delta > 0) {
            x.z.push_back(delta % 10);
            delta /= 10;
        }
        while ((x.z[x.z.size() - 1] == 0) && (x.z.size() > 1)) {
            x.z.pop_back();
        }
        if ((x.z.size() == 1) && (x.z[0] == 0)) {
            x.negative = false;
        }
    }
public:
    BigInteger() {
        z.resize(0);
        z.push_back(0);
    }
    BigInteger(const int64_t& x) {
        z.resize(0);
        int64_t temp = x;
        if (temp == 0) {
            z.push_back(0);
        } else {
            if (temp < 0) {
                temp = -temp;
                negative = true;
            }
            while (temp > 0) {
                z.push_back(temp % 10);
                temp /= 10;
            }
        }
    }
    BigInteger(const std::string& s) {
        z.resize(0);
        std::string s1;
        uint64_t i = 0;
        while (i < s.size() && (s[i] == 0 || s[i] == '-'))
            ++i;
        for (; i < s.size(); ++i)
            s1 += s[i];
        int n = s1.size();
        z.resize(n);
        if (s[0] == '-')
            negative = true;
        for (int64_t j = 0 ; j < n; ++j)
            z[j] = s1[n - 1 - j] - '0';
    }
    BigInteger(const BigInteger& x) {
        negative = x.negative;
        z = x.z;
    }
    ~BigInteger() {
        z.clear();
    }

    friend BigInteger operator-(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator+(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator*(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator/(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator%(const BigInteger& a, const BigInteger& b);
    BigInteger& operator=(const BigInteger& x) = default;
    bool operator==(const BigInteger& x) const{
        return ((x.z == z) && (x.negative == negative));
    }
    bool operator!=(const BigInteger& x) const{
        return !(x == *this);
    }
    bool operator<(const BigInteger& x) const {
        if (x == *this) {
            return false;
        }
        if ((x.negative) && (!this->negative)) {
            return false;
        } else if ((!x.negative) && (this->negative)) {
            return true;
        } else if ((!x.negative) && (!this->negative)) {
            if (x.z.size() > z.size()) {
                return true;
            } else if (x.z.size() < z.size()) {
                return false;
            } else {
                int64_t i = z.size() - 1;
                while (i >= 0) {
                    if (z[i] < x.z[i]) {
                        return true;
                    } else if (z[i] > x.z[i]) {
                        return false;
                    } else {
                        --i;
                    }
                }
                return false;
            }
        } else {
            if (x.z.size() > z.size()) {
                return false;
            } else if (x.z.size() < z.size()) {
                return true;
            } else {
                int64_t i = z.size() - 1;
                while (i >= 0) {
                    if (z[i] < x.z[i])
                        return false;
                    else if (z[i] > x.z[i])
                        return true;
                    else
                        --i;
                }
                return false;
            }
        }
    }
    bool operator<=(const BigInteger& x) const{
        return ((*this < x) || (*this == x));
    }
    bool operator>(const BigInteger& x) const{
        return (x < *this);
    }
    bool operator>=(const BigInteger& x) const{
        return ((*this > x) || (*this == x));
    }
    explicit operator bool() {
        bool f;
        if ((z.size() > 1) || (z[0] != 0)) {
            f = true;
        } else {
            f = false;
        }
        return f;
    }
    BigInteger operator-() const{
        BigInteger temp(*this);
        if (temp != 0) {
            temp.negative = !negative;
        }
        return temp;
    }
    BigInteger& operator+=(const BigInteger& x) {
        int64_t n = std::max(x.z.size(), z.size());
        z.resize(n);
        if (x.negative == negative) {
            for (uint64_t i = 0; i < x.z.size(); ++i) {
                z[i] += x.z[i];
            }
        } else {
            if (!negative) {
                if (*this > -x) {
                    for (uint64_t i = 0; i < x.z.size(); ++i) {
                        z[i] -= x.z[i];
                    }
                } else {
                    for (uint64_t i = 0; i < x.z.size(); ++i) {
                        z[i] = x.z[i] - z[i];
                    }
                    negative = !negative;
                }
            } else {
                if (-*this > x) {
                    for (uint64_t i = 0; i < x.z.size(); ++i) {
                        z[i] -= x.z[i];
                    }
                } else {
                    for (uint64_t i = 0; i < x.z.size(); ++i) {
                        z[i] = x.z[i] - z[i];
                    }
                    negative = !negative;
                }
            }
        }
        normalize(*this);
        return *this;
    }
    BigInteger& operator-=(const BigInteger& x) {
        int64_t n = std::max(x.z.size(), z.size());
        z.resize(n);
        *this += -x;
        return *this;
    }
    BigInteger& operator*=(const BigInteger& x) {
        BigInteger temp;
        temp.negative = (negative xor x.negative);
        temp.z.resize(x.z.size() + z.size());
        for (uint64_t i = 0; i < z.size(); ++i) {
            for (uint64_t j = 0; j < x.z.size(); ++j) {
                temp.z[i + j] += z[i] * x.z[j];
            }
        }
        *this = temp;
        if ( *this == 0) {
            negative = false;
        } else {
            normalize(*this);
        }
        return *this;
    }
    BigInteger& operator/=(const BigInteger& x) {
        BigInteger temp = x;
        temp.negative = false;
        uint64_t x_size = x.z.size();
        int64_t des = 0;
        BigInteger copy = *this;
        copy.negative = false;
        BigInteger res;
        if ((x.z.size() > z.size()) || ((x.z.size() == z.size()) && (x.z[z.size() - 1] > z[z.size() - 1]))) {
            *this = 0;
            return *this;
        } else {
            for (uint64_t i = 0; i < z.size() - x.z.size(); ++i) {
                temp *= 10;
                ++des;
            }
            if (copy - temp < 0) {
                for (uint64_t i = 0; i < temp.z.size() - 1; ++i) {
                  temp.z[i] = temp.z[i + 1];
                }
                temp.z.pop_back();
                --des;
            }
            while ((copy > 0) && (temp.z.size() >= x_size)) {
                int64_t k = 1;
                BigInteger mem = temp;
                while (copy - temp >= 0) {
                    temp += mem;
                    ++k;
                }
                temp -= mem;
                --k;
                copy -= temp;
                res.z.push_back(k);
                temp = mem;
                int64_t delta = 0;
                while ((copy - temp < 0) && (temp.z.size() >= x_size)) {
                    for (uint64_t i = 0; i < temp.z.size() - 1; ++i) {
                        temp.z[i] = temp.z[i + 1];
                    }
                    temp.z.pop_back();
                    ++delta;
                }
                if (temp.z.size() < x_size) {
                    for (int64_t i = 0; i < des; ++i) {
                        res.z.push_back(0);
                    }
                    std::vector <int> temp_vector;
                    for (int64_t i = res.z.size() - 1; i >= 0; --i) {
                        temp_vector.push_back(res.z[i]);
                    }
                    res.z = temp_vector;
                    res.negative = (negative xor x.negative);
                    normalize(res);
                    if (res == 0) {
                        res.negative = false;
                    }
                    *this = res;
                    return *this;
                } else {
                    des -= delta;
                    for (int64_t i = 0; i < delta - 1; ++i) {
                        res.z.push_back(0);
                    }
                }
            }
            std::vector <int> temp_vector;
            for (int64_t i = res.z.size() - 1; i >= 0; --i) {
                temp_vector.push_back(res.z[i]);
            }
            res.z = temp_vector;
            res.negative = (negative xor x.negative);
            normalize(res);
            *this = res;
            return *this;
        }
    }
    BigInteger& operator%=(const BigInteger& x) {
        bool f = negative xor x.negative;
        negative = false;
        BigInteger copy = *this / x;
        copy *= x;
        copy.negative = false;
        *this -= copy;
        negative = f;
        normalize(*this);
        return *this;
    }
    BigInteger& operator++() {
        *this +=1 ;
        return *this;
    }
    BigInteger operator++(int) {
        BigInteger copy = *this;
        ++*this;
        return copy;
    }
    BigInteger& operator--() {
        *this -= 1;
        return *this;
    }
    BigInteger operator--(int) {
        BigInteger copy = *this;
        --*this;
        return copy;
    }

    std::string toString() const{
        std::string s;
        if (z.empty()) {
            s = "0";
            return s;
        }
        if (!negative) {
            for (int64_t i = z.size() - 1; i >= 0; --i) {
                s += static_cast<char>(z[i] + 48);
            }
            return s;
        } else {
            s = "-";
            for (int64_t i = z.size() - 1; i >= 0; --i) {
                s += static_cast<char>(z[i] + 48);
            }
            return s;
        }
    }
    void clear() {
        z.clear();
        negative = false;
    }
    BigInteger abs() const {
        BigInteger copy = *this;
        copy.negative = false;
        return copy;
    }
};
std::istream& operator>>(std::istream& in, BigInteger& s) {
    s.clear();
    std::string str;
    in >> str;
    s = BigInteger(str);
    return in;
}
std::ostream& operator<<(std::ostream& out, const BigInteger& s) {
    out << s.toString();
    return out;
}
BigInteger operator+(const BigInteger& a, const BigInteger& b) {
    BigInteger copy = a;
    copy += b;
    return copy;
}
BigInteger operator-(const BigInteger& a, const BigInteger& b) {
    BigInteger copy = a;
    copy -= b;
    return copy;
}
BigInteger operator*(const BigInteger& a, const BigInteger& b) {
    BigInteger copy = a;
    copy *= b;
    return copy;
}
BigInteger operator/(const BigInteger& a, const BigInteger& b) {
    BigInteger copy = a;
    copy /= b;
    return copy;
}
BigInteger operator%(const BigInteger& a, const BigInteger& b) {
    BigInteger copy = a;
    copy %= b;
    return copy;
}

class Rational {
private:
    BigInteger num;
    BigInteger den;
    BigInteger NOD(const BigInteger& x, const BigInteger& y) const{
        if (y == 0)
            return x;
        BigInteger temp = x % y;
        return NOD(y, temp);
    }
    void normalise(Rational& x) {
        BigInteger d = NOD(x.den, x.num);
        d = d.abs();
        x.den /= d;
        x.num /= d;
        if (x.den < 0) {
            x.den = -x.den;
            x.num = -x.num;
        }
    }
    void sameDen(Rational& x, Rational& y) {
        BigInteger temp = NOD(x.den, y.den).abs();
        BigInteger copy = x.den;
        x.num *= (y.den / temp);
        x.den *= (y.den / temp);
        y.num *= (copy / temp);
        y.den *= (copy / temp);
    }
public:
    Rational() {
        num = 0;
        den = 1;
    }
    Rational(const BigInteger& x) {
        num = x;
        den = 1;
    }
    Rational(const int64_t& x) {
        num = x;
        den = 1;
    }
    Rational(const Rational& x) {
        den = x.den;
        num = x.num;
    }
    ~Rational() = default;

    Rational& operator=(const Rational& x) = default;
    bool operator==(const Rational& x) const{
        if ((den == x.den) && (num == x.num)) {
            return true;
        } else {
            return false;
        }
    }
    bool operator!=(const Rational& x) const {
        return !(*this == x);
    }
    bool operator<(const Rational& x) const {
        if (*this == x) {
            return false;
        }
        if ((num < 0) && (x.num > 0)) {
            return true;
        } else if ((num > 0) && (x.num < 0)) {
            return false;
        } else {
            Rational a = *this;
            Rational b = x;
            a.num *= b.den;
            b.num *= a.den;
            return (a.num < b.num);
        }
    }
    bool operator<=(const Rational& x) const{
        return ((*this < x) || (*this == x));
    }
    bool operator>(const Rational& x) const{
        return (x < *this);
    }
    bool operator>=(const Rational& x) const{
        return ((*this > x) || (*this == x));
    }
    explicit operator double() const{
        std::string str;
        str = asDecimal(20);
        double d = std::stod(str);
        return d;
    }
    Rational operator-() const{
        Rational temp(*this);
        temp.num *= -1;
        return temp;
    }
    Rational& operator+=(const Rational& x) {
        Rational copy = x;
        sameDen(*this, copy);
        num += copy.num;
        normalise(*this);
        return *this;
    }
    Rational& operator-=(const Rational& x) {
        *this += -x;
        return *this;
    }
    Rational& operator*=(const Rational& x) {
        num *= x.num;
        den *= x.den;
        normalise(*this);
        return *this;
    }
    Rational& operator/=(const Rational& x) {
        BigInteger temp = num * x.den;
        den *= x.num;
        num = temp;
        normalise(*this);
        return *this;
    }

    std::string toString() const{
        std::string str = num.toString();
        if (den != 1) {
            str += "/";
            str += den.toString();
        }
        return str;
    }
    void clear() {
        den = 1;
        num = 0;
    }
    std::string asDecimal(size_t precision = 0) const{
        if (precision == 0) {
            return (num / den).toString();
        }
        std::string str;
        Rational copy = *this;
        for (size_t i = 0; i < precision; ++i) {
            copy *= 10;
        }
        str = (copy.num / copy.den).toString();
        int64_t i = str.length();
        i -= precision;
        bool f = false;
        if (i <= 1) {
            if (str[0] == '-') {
                f = true;
                str[0] = '0';
            }
            std::string s1(-i + 1, '0');
            i = 1;
            str = s1 + str;
        }
        char t = str[i];
        str[i] = '.';
        ++i;
        int64_t l = str.length();
        while (i <  l) {
            std::swap(t, str[i]);
            ++i;
        }
        str += t;
        if (f) {
            str = '-' + str;
        }
        return str;
    }
};
Rational operator+(const Rational& a, const Rational& b) {
    Rational copy = a;
    copy += b;
    return copy;
}
Rational operator-(const Rational& a, const Rational& b) {
    Rational copy = a;
    copy -= b;
    return copy;
}
Rational operator*(const Rational& a, const Rational& b) {
    Rational copy = a;
    copy *= b;
    return copy;
}
Rational operator/(const Rational& a, const Rational& b) {
    Rational copy = a;
    copy /= b;
    return copy;
}
std::istream& operator>>(std::istream& in, Rational& s) {
    s.clear();
    std::string str;
    in >> str;
    s = BigInteger(str);
    return in;
}
std::ostream& operator<<(std::ostream& out, const Rational& s) {
    out << s.toString();
    return out;
}
