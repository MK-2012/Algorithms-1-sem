#include <iostream>
#include <vector>
#include <string>

const int64_t BASE = 10;

class BigInteger {
private:
    std::vector <int> number;
    bool negative = false;
    void normalize(BigInteger& x) {
        int64_t delta = 0;
        for (uint64_t i = 0; i < x.number.size(); ++i) {
            x.number[i] += delta;
            delta = x.number[i] / BASE;
            x.number[i] = x.number[i] % BASE;
            if (x.number[i] < 0) {
                --delta;
                x.number[i] += BASE;
            }
        }
        if (delta < 0) {
            x.negative = !x.negative;
            delta = -delta;
        }
        while (delta > 0) {
            x.number.push_back(delta % BASE);
            delta /= BASE;
        }
        while ((x.number[x.number.size() - 1] == 0) && (x.number.size() > 1)) {
            x.number.pop_back();
        }
        if ((x.number.size() == 1) && (x.number[0] == 0)) {
            x.negative = false;
        }
    }
public:
    BigInteger() {
        number.resize(0);
        number.push_back(0);
    }
    BigInteger(const int64_t& x) {
        number.resize(0);
        int64_t temp = x;
        if (temp == 0) {
            number.push_back(0);
        } else {
            if (temp < 0) {
                temp = -temp;
                negative = true;
            }
            while (temp > 0) {
                number.push_back(temp % BASE);
                temp /= BASE;
            }
        }
    }
    BigInteger(const std::string& s) {
        number.resize(0);
        std::string s1;
        uint64_t i = 0;
        while (i < s.size() && (s[i] == 0 || s[i] == '-'))
            ++i;
        for (; i < s.size(); ++i)
            s1 += s[i];
        int n = s1.size();
        number.resize(n);
        if (s[0] == '-')
            negative = true;
        for (int64_t j = 0 ; j < n; ++j)
            number[j] = s1[n - 1 - j] - '0';
    }
    BigInteger(const BigInteger& x) {
        negative = x.negative;
        number = x.number;
    }
    ~BigInteger() {
        number.clear();
    }

    friend BigInteger operator-(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator+(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator*(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator/(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator%(const BigInteger& a, const BigInteger& b);
    BigInteger& operator=(const BigInteger& right) = default;
    bool operator==(const BigInteger& right) const{
        return ((right.number == number) && (right.negative == negative));
    }
    bool operator!=(const BigInteger& right) const{
        return !(right == *this);
    }
    bool operator<(const BigInteger& right) const {
        if (right == *this) {
            return false;
        }
        if ((right.negative) && (!this->negative)) {
            return false;
        } else if ((!right.negative) && (this->negative)) {
            return true;
        } else if ((!right.negative) && (!this->negative)) {
            if (right.number.size() > number.size()) {
                return true;
            } else if (right.number.size() < number.size()) {
                return false;
            } else {
                int64_t i = number.size() - 1;
                while (i >= 0) {
                    if (number[i] < right.number[i]) {
                        return true;
                    } else if (number[i] > right.number[i]) {
                        return false;
                    } else {
                        --i;
                    }
                }
                return false;
            }
        } else {
            if (right.number.size() > number.size()) {
                return false;
            } else if (right.number.size() < number.size()) {
                return true;
            } else {
                int64_t i = number.size() - 1;
                while (i >= 0) {
                    if (number[i] < right.number[i])
                        return false;
                    else if (number[i] > right.number[i])
                        return true;
                    else
                        --i;
                }
                return false;
            }
        }
    }
    bool operator<=(const BigInteger& right) const{
        return ((*this < right) || (*this == right));
    }
    bool operator>(const BigInteger& right) const{
        return (right < *this);
    }
    bool operator>=(const BigInteger& right) const{
        return ((*this > right) || (*this == right));
    }
    explicit operator bool() {
        bool f;
        if ((number.size() > 1) || (number[0] != 0)) {
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
    BigInteger& operator+=(const BigInteger& right) {
        int64_t n = std::max(right.number.size(), number.size());
        number.resize(n);
        if (right.negative == negative) {
            for (uint64_t i = 0; i < right.number.size(); ++i) {
                number[i] += right.number[i];
            }
        } else {
            if (!negative) {
                if (*this > -right) {
                    for (uint64_t i = 0; i < right.number.size(); ++i) {
                        number[i] -= right.number[i];
                    }
                } else {
                    for (uint64_t i = 0; i < right.number.size(); ++i) {
                        number[i] = right.number[i] - number[i];
                    }
                    negative = !negative;
                }
            } else {
                if (-*this > right) {
                    for (uint64_t i = 0; i < right.number.size(); ++i) {
                        number[i] -= right.number[i];
                    }
                } else {
                    for (uint64_t i = 0; i < right.number.size(); ++i) {
                        number[i] = right.number[i] - number[i];
                    }
                    negative = !negative;
                }
            }
        }
        normalize(*this);
        return *this;
    }
    BigInteger& operator-=(const BigInteger& right) {
        int64_t n = std::max(right.number.size(), number.size());
        number.resize(n);
        *this += -right;
        return *this;
    }
    BigInteger& operator*=(const BigInteger& right) {
        BigInteger temp;
        temp.negative = (negative xor right.negative);
        temp.number.resize(right.number.size() + number.size());
        for (uint64_t i = 0; i < number.size(); ++i) {
            for (uint64_t j = 0; j < right.number.size(); ++j) {
                temp.number[i + j] += number[i] * right.number[j];
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
    BigInteger& operator/=(const BigInteger& right) {
        BigInteger temp = right;
        temp.negative = false;
        uint64_t x_size = right.number.size();
        int64_t des = 0;
        BigInteger copy = *this;
        copy.negative = false;
        BigInteger res;
        if ((right.number.size() > number.size()) || ((right.number.size() == number.size()) && (right.number[number.size() - 1] > number[number.size() - 1]))) {
            *this = 0;
            return *this;
        } else {
            for (uint64_t i = 0; i < number.size() - right.number.size(); ++i) {
                temp *= BASE;
                ++des;
            }
            if (copy - temp < 0) {
                for (uint64_t i = 0; i < temp.number.size() - 1; ++i) {
                  temp.number[i] = temp.number[i + 1];
                }
                temp.number.pop_back();
                --des;
            }
            while ((copy > 0) && (temp.number.size() >= x_size)) {
                int64_t k = 1;
                BigInteger mem = temp;
                while (copy - temp >= 0) {
                    temp += mem;
                    ++k;
                }
                temp -= mem;
                --k;
                copy -= temp;
                res.number.push_back(k);
                temp = mem;
                int64_t delta = 0;
                while ((copy - temp < 0) && (temp.number.size() >= x_size)) {
                    for (uint64_t i = 0; i < temp.number.size() - 1; ++i) {
                        temp.number[i] = temp.number[i + 1];
                    }
                    temp.number.pop_back();
                    ++delta;
                }
                if (temp.number.size() < x_size) {
                    for (int64_t i = 0; i < des; ++i) {
                        res.number.push_back(0);
                    }
                    std::vector <int> temp_vector;
                    for (int64_t i = res.number.size() - 1; i >= 0; --i) {
                        temp_vector.push_back(res.number[i]);
                    }
                    res.number = temp_vector;
                    res.negative = (negative xor right.negative);
                    normalize(res);
                    if (res == 0) {
                        res.negative = false;
                    }
                    *this = res;
                    return *this;
                } else {
                    des -= delta;
                    for (int64_t i = 0; i < delta - 1; ++i) {
                        res.number.push_back(0);
                    }
                }
            }
            std::vector<int> temp_vector;
            for (int64_t i = res.number.size() - 1; i >= 0; --i) {
                temp_vector.push_back(res.number[i]);
            }
            res.number = temp_vector;
            res.negative = (negative xor right.negative);
            normalize(res);
            *this = res;
            return *this;
        }
    }
    BigInteger& operator%=(const BigInteger& right) {
        bool f = negative xor right.negative;
        negative = false;
        BigInteger copy = *this / right;
        copy *= right;
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
        if (number.empty()) {
            s = "0";
            return s;
        }
        if (!negative) {
            for (int64_t i = number.size() - 1; i >= 0; --i) {
                s += static_cast<char>(number[i] + 48);
            }
            return s;
        } else {
            s = "-";
            for (int64_t i = number.size() - 1; i >= 0; --i) {
                s += static_cast<char>(number[i] + 48);
            }
            return s;
        }
    }
    void clear() {
        number.clear();
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
    /*BigInteger GCD(const BigInteger& x, const BigInteger& y) const {
        if (x == y) {
            return x;
        }
        if (x == 0) {
            return y;
        }
        if (y == 0) {
            return x;
        }
        if (x % 2 == 0) {
            if (y % 2 == 1) {
                return GCD(x / 2, y);
            } else {
                return 2 * GCD(x / 2, y / 2);
            }
        } else {
            if (y % 2 == 0) {
                return GCD(x, y / 2);
            }
            if (x > y) {
                return GCD((x - y) / 2, y);
            }
            else {
                return GCD((y - x) / 2, x);
            }
        }
    } */
    BigInteger GCD(const BigInteger& x, const BigInteger& y) const {
        if (y == 0)
            return x;
        BigInteger temp = x % y;
        return GCD(y, temp);
    }
    void normalise(Rational& x) {
        BigInteger d = GCD(x.den, x.num);
        d = d.abs();
        x.den /= d;
        x.num /= d;
        if (x.den < 0) {
            x.den = -x.den;
            x.num = -x.num;
        }
    }
    void toSameDen(Rational& x, Rational& y) {
        BigInteger temp = GCD(x.den, y.den).abs();
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

    Rational& operator=(const Rational& right) = default;
    bool operator==(const Rational& right) const{
        if ((den == right.den) && (num == right.num)) {
            return true;
        } else {
            return false;
        }
    }
    bool operator!=(const Rational& right) const {
        return !(*this == right);
    }
    bool operator<(const Rational& right) const {
        if (*this == right) {
            return false;
        }
        if ((num < 0) && (right.num > 0)) {
            return true;
        } else if ((num > 0) && (right.num < 0)) {
            return false;
        } else {
            Rational a = *this;
            Rational b = right;
            a.num *= b.den;
            b.num *= a.den;
            return (a.num < b.num);
        }
    }
    bool operator<=(const Rational& right) const{
        return ((*this < right) || (*this == right));
    }
    bool operator>(const Rational& right) const{
        return (right < *this);
    }
    bool operator>=(const Rational& right) const{
        return ((*this > right) || (*this == right));
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
    Rational& operator+=(const Rational& right) {
        Rational copy = right;
        toSameDen(*this, copy);
        num += copy.num;
        normalise(*this);
        return *this;
    }
    Rational& operator-=(const Rational& right) {
        *this += -right;
        return *this;
    }
    Rational& operator*=(const Rational& right) {
        num *= right.num;
        den *= right.den;
        normalise(*this);
        return *this;
    }
    Rational& operator/=(const Rational& right) {
        BigInteger temp = num * right.den;
        den *= right.num;
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
            copy *= BASE;
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
