#include <iostream>
#include <vector>
#include <algorithm>

const int64_t BASE = 10;

bool operator>(const std::vector<int16_t>& a, const std::vector<int16_t>& b) {
    if (a.size() > b.size()) {
        return true;
    } else if (a.size() < b.size()) {
        return false;
    } else {
        for (int64_t i = static_cast<int64_t>(a.size()) - 1; i >= 0; --i) {
            if (a[i] > b[i]) {
                return true;
            } else if (a[i] < b[i]) {
                return false;
            }
        }
        return false;
    }
}
class BigInteger {
private:
    std::vector<int16_t> number;
    mutable bool negative = false;
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
        int16_t n = s1.size();
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
    BigInteger(const std::vector<int16_t>& v) {
        number.resize(v.size());
        number = v;
    }
    BigInteger(BigInteger&& x) noexcept {
        negative = x.negative;
        number = std::move(x.number);
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
    BigInteger& operator=(BigInteger&& right) noexcept {
        negative = right.negative;
        number = std::move(right.number);
        return *this;
    }
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
    BigInteger operator-() const {
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
                if (number > right.number) {
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
                if (number > right.number) {
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
        if (right.negative != negative) {
            for (uint64_t i = 0; i < right.number.size(); ++i) {
                number[i] += right.number[i];
            }
        } else {
            if (negative) {
                if (number > right.number) {
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
                if (number > right.number) {
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
        if (number.size() < right.number.size()) {
            *this = BigInteger(0);
            return *this;
        }
        if (right == 2) {
            for (uint64_t i = 0; i < number.size(); ++i) {
                if ((i > 0) && (number[i] % 2)) {
                    number[i - 1] += 5;
                }
                number[i] /= 2;
                if ((i == number.size() - 1) && (number[i] == 0)) {
                    number.pop_back();
                }
            }
            return *this;
        }
        BigInteger res(0);
        BigInteger remainder(0);
        BigInteger divider(right.number);
        bool flag1 = false;
        bool flag2 = false;
        std::vector<BigInteger> dividers(11);
        dividers[0] = BigInteger(0);
        for (size_t i = 1; i < 11; ++i) {
            dividers[i] = dividers[i - 1] + divider;
        }
        size_t pos = number.size();
        while (true) {
            flag2 = false;
            while (pos > 0 && divider.number > remainder.number) {
                remainder.pushFront(number[pos - 1]);
                --pos;
                if (flag1 && flag2) {
                    res.pushFront(0);
                }
                flag2 = true;
            }
            flag1 = true;
            if (pos == 0 && remainder < divider) {
                if (flag2) {
                    res.pushFront(0);
                }
                break;
            } else {
                size_t l = 0, r = 10;
                while (r - l > 1) {
                    if (dividers[(r + l) / 2].number > remainder.number) {
                        r = (r + l) / 2;
                    } else {
                        l = (r + l) / 2;
                    }
                }
                remainder -= dividers[l];
                res.pushFront(l);
            }
        }
        negative = (negative != right.negative);
        number = res.number;
        return *this;
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
    int16_t lastDigit() const {
        return number[0];
    }
    void pushFront(const uint16_t x) {
        if (number.size() == 1 && number[0] == 0) {
            number[0] = x;
            return;
        }
        number.push_back(0);
        for (size_t i = number.size(); i > 0; --i) {
            number[i - 1] = number[i - 2];
        }
        number[0] = x;
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
    BigInteger GCD(BigInteger &a, BigInteger &b) {
        if (a == 0) {
            return b;
        } else if (b == 0) {
            return a;
        } else if (a == b) {
            return a;
        } else if (a == 1 || b == 1) {
            return 1;
        }
        if (a.lastDigit() % 2 == 0 && b.lastDigit() % 2 == 0) {
            a /= 2;
            b /= 2;
            return 2 * GCD(a, b);
        }
        if (a.lastDigit() % 2 == 0 && b.lastDigit() % 2 != 0) {
            a /= 2;
            return GCD(a, b);
        }
        if (a.lastDigit() % 2 != 0 && b.lastDigit() % 2 == 0) {
            b /= 2;
            return GCD(a, b);
        }
        if (a < b) {
            b -= a;
            b /= 2;
            return GCD(b, a);
        } else {
            a -= b;
            a /= 2;
            return GCD(a, b);
        }
    }
    void normalise(Rational& x) {
        BigInteger den_copy = x.den.abs();
        BigInteger num_copy = x.num.abs();
        BigInteger d = GCD(den_copy, num_copy);
        x.den /= d;
        x.num /= d;
        if (x.den < 0) {
            x.den = -x.den;
            x.num = -x.num;
        }
    }
    void toSameDen(Rational& x, Rational& y) {
        BigInteger x_copy = x.den.abs();
        BigInteger y_copy = y.den.abs();
        BigInteger temp = GCD(x_copy, y_copy);
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
    Rational(BigInteger&& x) noexcept {
        num = std::move(x);
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
    Rational(Rational&& x) noexcept {
        den = std::move(x.den);
        num = std::move(x.num);
    }
    Rational(const std::string& s) {
        int16_t k = s.find('/');
        if (k != -1) {
            num = BigInteger(s.substr(0, k));
            den = BigInteger(s.substr(k + 1, s.length() - k - 1));
        } else {
            num = BigInteger(s);
            den = 1;
        }
    }
    ~Rational() = default;

    Rational& operator=(const Rational& right) = default;
    Rational& operator=(Rational&& right) noexcept {
        num = std::move(right.num);
        den = std::move(right.den);
        return *this;
    }
    bool operator==(const Rational& right) const {
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
    s = Rational(str);
    return in;
}
std::ostream& operator<<(std::ostream& out, const Rational& s) {
    out << s.toString();
    return out;
}











template <int64_t N>
class Finite {
private:

public:
    int64_t val = 0;

    Finite() = default;
    Finite(const Finite& a) = default;
    Finite(const int64_t a) {
        if (a >= 0) {
            val = a % N;
        } else if (a % N == 0) {
            val = 0;
        } else {
            val = N + a % N;
        }
    }
    ~Finite() = default;

    Finite<N>& operator=(const Finite<N>& b) = default;
    bool operator==(const Finite<N>& b) const {
        if (val == b.val) {
            return true;
        } else {
            return false;
        }
    }
    bool operator!=(const Finite<N>& b) const {
        return !(*this == b);
    }
    Finite<N>& operator+=(const Finite<N>& b) {
        val += b.val;
        val %= N;
        return *this;
    }
    Finite<N>& operator-=(const Finite<N>& b) {
        val -= b.val;
        if (val >= 0) {
            val = val % N;
        } else if (val % N == 0) {
            val = 0;
        } else {
            val = N + val % N;
        }
        return *this;
    }
    Finite<N>& operator*=(const Finite<N>& b) {
        val *= b.val;
        val %= N;
        return *this;
    }
    Finite<N>& operator/=(const Finite<N>& b) {
        int64_t temp = pow(b.val, N - 2);
        val *= temp;
        val %= N;
        return *this;
    }
    bool operator<(const Finite<N>& b) = delete;
    bool operator<=(const Finite<N>& b) = delete;
    bool operator>(const Finite<N>& b) = delete;
    bool operator>=(const Finite<N>& b) = delete;
    Finite<N> operator-() const {
        Finite temp(*this);
        temp = N - temp;
        temp %= N;
        return temp;
    }
    Finite<N>& operator++() {
        *this +=1;
        return *this;
    }
    Finite<N> operator++(int) {
        Finite<N> copy = *this;
        ++*this;
        return copy;
    }
    Finite<N>& operator--() {
        *this -= 1;
        return *this;
    }
    Finite<N> operator--(int) {
        Finite<N> copy = *this;
        --*this;
        return copy;
    }

    int64_t pow(const int64_t& a, const int64_t& b) {
        if (b == 0) {
            return 1;
        }
        if (b == 1) {
            return a;
        }
        if (b % 2 == 0) {
            int64_t temp = pow(a, b / 2);
            return temp * temp % N;
        } else {
            return (a * pow(a, b - 1)) % N;
        }
    }
};
template<int64_t N>
Finite<N> operator+(const Finite<N>& a, const Finite<N>& b) {
    Finite<N> copy = a;
    copy += b;
    return copy;
}
template<int64_t N>
Finite<N> operator-(const Finite<N>& a, const Finite<N>& b) {
    Finite<N> copy = a;
    copy -= b;
    return copy;
}
template<int64_t N>
Finite<N> operator*(const Finite<N>& a, const Finite<N>& b) {
    Finite<N> copy = a;
    copy *= b;
    return copy;
}
template<int64_t N>
Finite<N> operator/(const Finite<N>& a, const Finite<N>& b) {
    Finite<N> copy = a;
    copy /= b;
    return copy;
}
template<int64_t NN>
std::ostream& operator<<(std::ostream& out, const Finite<NN>& s) {
    out << s.val;
    return out;
}

template <size_t M, size_t N, typename Field = Rational>
class Matrix {
protected:
    std::vector <std::vector <Field>> mat;
public:
    void addRow(const size_t& n, const size_t& m, const Field& coeff) {
        for (size_t i = 0; i < N; ++i) {
            mat[n][i] += mat[m][i] * coeff;
        }
    }
    void subtractRow(const size_t& n, const size_t& m, const Field& coeff) {
        for (size_t i = 0; i < N; ++i) {
            mat[n][i] -= mat[m][i] * coeff;
        }
    }
    void divideRow(const size_t& n, const Field& coeff) {
        for (size_t i = 0; i < N; ++i) {
            mat[n][i] /= coeff;
        }
    }
    Matrix() {
        mat.resize(M);
        for (size_t i = 0; i < M; ++i) {
            mat[i].resize(N);
        }
    }
    Matrix(const Matrix& x) = default;
    Matrix(const std::vector<std::vector<Field>>& vec) {
        mat.resize(vec.size());
        for (size_t i = 0; i < M; ++i) {
            mat[i].resize(vec[i].size());
            for (size_t j = 0; j < N; ++j) {
                mat[i][j] = vec[i][j];
            }
        }
    }
    Matrix(Matrix&& x) noexcept: mat(std::move(x.mat)) {}
    Matrix(std::vector<std::vector<Field>>&& x): mat(std::move(x)) {}
    template<typename F>
    Matrix(const std::vector<std::vector<F>>& vec) {
        mat.resize(vec.size());
        for (size_t i = 0; i < M; ++i) {
            mat[i].resize(vec[i].size());
            for (size_t j = 0; j < N; ++j) {
                mat[i][j] = static_cast<Field>(vec[i][j]);
            }
        }
    }
    ~Matrix() = default;

    Matrix<M, N, Field>& operator=(const Matrix<M, N, Field>& B) = default;
    template<size_t MM, size_t NN, typename FF = Rational>
    bool operator==([[maybe_unused]]const Matrix<MM, NN, FF>& B) const {
        return false;
    }
    bool operator==(const Matrix<M, N, Field>& B) const {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                if (mat[i][j] != B[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    template<size_t MM, size_t NN, typename FF = Rational>
    bool operator!=(const Matrix<MM, NN, FF>& B) const {
        return !(*this == B);
    }
    std::vector<Field>& operator[](const uint64_t& i) {
        return mat[i];
    }
    const std::vector<Field>& operator[](const uint64_t& i) const {
        return mat[i];
    }
    Matrix<M, N, Field>& operator+=(const Matrix<M, N, Field>& B) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                mat[i][j] += B[i][j];
            }
        }
        return *this;
    }
    Matrix<M, N, Field>& operator-=(const Matrix<M, N, Field>& B) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                mat[i][j] -= B[i][j];
            }
        }
        return *this;
    }
    Matrix<M, N, Field>& operator*=(const Field& b) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                mat[i][j] *= b;
            }
        }
        return *this;
    }
    Matrix<M, N, Field>& operator/=(const Field& b) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                mat[i][j] /= b;
            }
        }
        return *this;
    }
    Matrix operator*=(const Matrix& b) = delete;
    Matrix<M, N, Field> operator-(const Matrix<M, N, Field>& B) const {
        Matrix<M, N, Field> copy = *this;
        copy -= B;
        return copy;
    }
    Matrix<M, N, Field> operator+(const Matrix<M, N, Field>& B) const {
        Matrix<M, N, Field> copy = *this;
        copy += B;
        return copy;
    }

    std::vector<Field> getRow(const size_t& m) const {
        std::vector <Field> temp;
        for (size_t i = 0; i < mat[m].size(); ++i) {
            temp.push_back(mat[m][i]);
        }
        return temp;
    }
    std::vector<Field> getColumn(const size_t& n) const {
        std::vector <Field> temp;
        for (size_t i = 0; i < mat.size(); ++i) {
            temp.push_back(mat[i][n]);
        }
        return temp;
    }
    Matrix<N, M, Field> transposed() const {
        Matrix<N, M, Field> temp;
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                temp[j][i] = mat[i][j];
            }
        }
        return temp;
    }
    Matrix<M, N, Field> eulerStair() const {
        Matrix<M, N, Field> temp(*this);
        size_t i = 0;
        for (size_t j = 0; j < N; ++j) {
            if (i >= M) {
                break;
            }
            if (temp.mat[i][j] == 0) {
                size_t k;
                for (k = i; (k < M) && (temp.mat[k][j] == 0); ++k) {}
                if (k == M) {
                    continue;
                } else {
                    temp.addRow(i, k, 1);
                }
            }
            for (size_t k = 0; k < i; ++k) {
                temp.subtractRow(k, i, (temp.mat[k][j] / temp.mat[i][j]));
            }
            for (size_t k = i + 1; k < M; ++k) {
                temp.subtractRow(k, i, (temp.mat[k][j] / temp.mat[i][j]));
            }
            ++i;
        }
        return temp;
    }
    int64_t rank() const {
        Matrix<M, N, Field> temp = eulerStair();
        int64_t res = 0;
        size_t m = 0;
        size_t n = 0;
        while (m < M) {
            while ((temp[m][n] == 0) && (n < N)) {
                ++n;
            }
            if (n < N) {
                ++res;
                ++m;
            } else {
                return res;
            }
        }
        return res;
    }

    Matrix<M, N, Field> invert() = delete;
    Matrix<M, N, Field> inverted() = delete;
    Field det() = delete;
    Field trace() = delete;
};

template <size_t M, typename Field>
class Matrix<M, M, Field> {
protected:
    std::vector <std::vector <Field>> mat;
public:
    void addRow(const size_t& n, const size_t& m, const Field& coeff) {
        for (size_t i = 0; i < M; ++i) {
            mat[n][i] += mat[m][i] * coeff;
        }
    }
    void subtractRow(const size_t& n, const size_t& m, const Field& coeff) {
        for (size_t i = 0; i < M; ++i) {
            mat[n][i] -= mat[m][i] * coeff;
        }
    }
    void divideRow(const size_t& n, const Field& coeff) {
        for (size_t i = 0; i < M; ++i) {
            mat[n][i] /= coeff;
        }
    }
    Matrix() {
        mat.resize(M);
        for (size_t i = 0; i < M; ++i) {
            mat[i].resize(M);
            mat[i][i] = 1;
        }
    }
    Matrix(const Matrix& x) = default;
    Matrix(const std::vector<std::vector<Field>>& vec) {
        mat.resize(vec.size());
        for (size_t i = 0; i < M; ++i) {
            mat[i].resize(vec[i].size());
            for (size_t j = 0; j < M; ++j) {
                mat[i][j] = vec[i][j];
            }
        }
    }
    Matrix(Matrix&& x) noexcept: mat(std::move(x.mat)) {}
    Matrix(std::vector<std::vector<Field>>&& x): mat(std::move(x)) {}
    template<typename F>
    Matrix(const std::vector<std::vector<F>>& vec) {
        mat.resize(vec.size());
        for (size_t i = 0; i < M; ++i) {
            mat[i].resize(vec[i].size());
            for (size_t j = 0; j < M; ++j) {
                mat[i][j] = static_cast<Field>(vec[i][j]);
            }
        }
    }
    ~Matrix() = default;

    Matrix<M, M, Field>& operator=(const Matrix<M, M, Field>& B) = default;
    template<size_t MM, size_t NN, typename FF = Rational>
    bool operator==([[maybe_unused]]const Matrix<MM, NN, FF>& B) const {
        return false;
    }
    bool operator==(const Matrix<M, M, Field>& B) const {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < M; ++j) {
                if (mat[i][j] != B[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    template<size_t MM, size_t NN, typename FF = Rational>
    bool operator!=(const Matrix<MM, NN, FF>& B) const {
        return !(*this == B);
    }
    std::vector<Field>& operator[](const uint64_t& i) {
        return mat[i];
    }
    const std::vector<Field>& operator[](const uint64_t& i) const {
        return mat[i];
    }
    Matrix<M, M, Field>& operator+=(const Matrix<M, M, Field>& B) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < M; ++j) {
                mat[i][j] += B[i][j];
            }
        }
        return *this;
    }
    Matrix<M, M, Field>& operator-=(const Matrix<M, M, Field>& B) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < M; ++j) {
                mat[i][j] -= B[i][j];
            }
        }
        return *this;
    }
    Matrix<M, M, Field>& operator*=(const Field& b) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < M; ++j) {
                mat[i][j] *= b;
            }
        }
        return *this;
    }
    Matrix<M, M, Field>& operator/=(const Field& b) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < M; ++j) {
                mat[i][j] /= b;
            }
        }
        return *this;
    }
    Matrix<M, M, Field>& operator*=(const Matrix<M, M, Field>& right) {
        Matrix<M, M, Field> copy = *this;
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < M; ++j) {
                Field temp_sum = 0;
                for (size_t k = 0; k < M; ++k) {
                    temp_sum += copy[i][k] * right[k][j];
                }
                mat[i][j] = temp_sum;
            }
        }
        return *this;
    }
    Matrix<M, M, Field> operator-(const Matrix<M, M, Field>& B) const {
        Matrix<M, M, Field> copy = *this;
        copy -= B;
        return copy;
    }
    Matrix<M, M, Field> operator+(const Matrix<M, M, Field>& B) const {
        Matrix<M, M, Field> copy = *this;
        copy += B;
        return copy;
    }

    std::vector<Field> getRow(const size_t& m) const {
        std::vector <Field> temp;
        for (size_t i = 0; i < mat[m].size(); ++i) {
            temp.push_back(mat[m][i]);
        }
        return temp;
    }
    std::vector<Field> getColumn(const size_t& n) const {
        std::vector <Field> temp;
        for (size_t i = 0; i < mat.size(); ++i) {
            temp.push_back(mat[i][n]);
        }
        return temp;
    }
    Matrix<M, M, Field> eulerStair() const {
        Matrix<M, M, Field> temp(*this);
        size_t i = 0;
        for (size_t j = 0; j < M; ++j) {
            if (i >= M) {
                break;
            }
            if (temp.mat[i][j] == 0) {
                size_t k;
                for (k = i; (k < M) && (temp.mat[k][j] == 0); ++k) {}
                if (k == M) {
                    continue;
                } else {
                    temp.addRow(i, k, 1);
                }
            }
            for (size_t k = 0; k < i; ++k) {
                temp.subtractRow(k, i, (temp.mat[k][j] / temp.mat[i][j]));
            }
            for (size_t k = i + 1; k < M; ++k) {
                temp.subtractRow(k, i, (temp.mat[k][j] / temp.mat[i][j]));
            }
            ++i;
        }
        return temp;
    }
    Matrix<M, M, Field> transposed() const {
        Matrix<M, M, Field> temp;
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < M; ++j) {
                temp[j][i] = mat[i][j];
            }
        }
        return temp;
    }
    int64_t rank() const {
        Matrix<M, M, Field> temp = eulerStair();
        int64_t res = 0;
        size_t m = 0;
        size_t n = 0;
        while (m < M) {
            while ((temp[m][n] == 0) && (n < M)) {
                ++n;
            }
            if (n < M) {
                ++res;
                ++m;
            } else {
                return res;
            }
        }
        return res;
    }
    void invert() {
        Matrix<M, 2 * M, Field> temp;
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < M; ++j) {
                temp[i][j] = mat[i][j];
            }
        }
        for (size_t i = 0; i < M; ++i) {
            temp[i][i + M] = 1;
        }
        temp = temp.eulerStair();
        for (size_t i = 0; i < M; ++i) {
            Field coeff = temp[i][i];
            temp.divideRow(i, coeff);
        }
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < M; ++j) {
                mat[i][j] = temp[i][j + M];
            }
        }
    }
    Matrix<M, M, Field> inverted() {
        Matrix<M, 2 * M, Field> temp;
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < M; ++j) {
                temp[i][j] = mat[i][j];
            }
        }
        for (size_t i = 0; i < M; ++i) {
            temp[i][i + M] = 1;
        }
        temp = temp.eulerStair();
        for (size_t i = 0; i < M; ++i) {
            Field coeff = temp[i][i];
            temp.divideRow(i, coeff);
        }
        Matrix<M, M, Field> res;
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < M; ++j) {
                res[i][j] = temp[i][j + M];
            }
        }
        return res;
    }
    Field det() const {
        Field res = 1;
        Matrix<M, M, Field> temp = eulerStair();
        for (size_t i = 0; i < M; ++i) {
            res *= temp[i][i];
        }
        return res;
    }
    Field trace() const {
        Field sum = 0;
        for (uint64_t i = 0; i < M; ++i) {
            sum += mat[i][i];
        }
        return sum;
    }
};

template <size_t M, size_t N, typename Field = Rational>
Matrix<M, N, Field> operator*(const Matrix<M, N, Field>& A, const Field& b) {
    Matrix<M, N, Field> copy = A;
    copy *= b;
    return copy;
}
template <size_t M, size_t N, typename Field = Rational>
Matrix<M, N, Field> operator*(const Field& b, const Matrix<M, N, Field>& A) {
    Matrix<M, N, Field> copy = A;
    copy *= b;
    return copy;
}
template <size_t M, size_t N, typename Field = Rational>
Matrix<M, N, Field> operator/(const Matrix<M, N, Field>& A, const Field& b) {
    Matrix<M, N, Field> copy = A;
    copy /= b;
    return copy;
}
template <size_t M, size_t N, typename Field = Rational>
Matrix<M, N, Field> operator/(const Field& b, const Matrix<M, N, Field>& A) {
    Matrix<M, N, Field> copy = A;
    copy /= b;
    return copy;
}
template <size_t M, size_t N, size_t K, typename Field = Rational>
Matrix<M, K, Field> operator*(const Matrix<M, N, Field>& A, const Matrix<N, K, Field>& B) {
    Matrix<M, K, Field> temp;
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < K; ++j) {
            Field temp_sum = 0;
            for (size_t k = 0; k < N; ++k) {
                temp_sum += A[i][k] * B[k][j];
            }
            temp[i][j] = temp_sum;
        }
    }
    return temp;
}
template <size_t M, size_t N, typename Field = Rational>
std::ostream& operator<<(std::ostream& out, const Matrix<M, N, Field>& s) {
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            out << s[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}

template <size_t N, typename Field = Rational>
using SquareMatrix = Matrix<N, N, Field>;
