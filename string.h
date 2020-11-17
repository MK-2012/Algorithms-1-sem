#include <iostream>
#include <cstring>

class String {
private:
    char* str = nullptr;
    uint64_t len = 0;
    uint64_t size = 0;
    void swap(String& s) {
        std::swap(s.len, len);
        std::swap(s.size, size);
        std::swap(s.str, str);
    }
public:
    String() = default;
    String(uint64_t n, const char t = '\0') {
        len = n;
        size = len;
        str = new char[size];
        memset(str, t, len);
    }
    String(const char* string) {
        len = strlen(string);
        size = len;
        str = new char[size];
        memcpy(str, string, len);
    }
    String(const String& s) {
        len = s.len;
        size = s.size;
        str = new char[size];
        memcpy(str, s.str, s.len);
    }
    String(const char t) {
        len = 1;
        size = 1;
        str = new char[1];
        *str = t;
    }
    ~String() {
        if (len > 0)
        {
            delete[] str;
        }
    }

    bool operator==(const String& s) const{
        if (len != s.len) {
            return false;
        } else {
            uint64_t i = 0;
            while ((i < len) && (s[i] == str[i])) {
                ++i;
            }
            if (i < len) {
                return false;
            }
        }
        return true;
    }
    String& operator=(String s) {
        swap(s);
        return (*this);
    }
    char& operator[](uint64_t i) {
        return *(str + i);
    }
    const char& operator[](uint64_t i) const{
        return *(str + i);
    }
    String& operator+=(const String& b) {
        if (str == nullptr) {
            char* temp_string = new char[b.len];
            memcpy(temp_string, b.str, b.len);
            str = temp_string;
            len = b.len;
            size = b.size;
            return (*this);
        }
        if (len + b.len >= size) {
            size = std::max(size, b.size) * 2;
            char *temp_string = new char[size];
            memcpy(temp_string, str, len);
            if (len > 0) {
                delete[] str;
            }
            str = temp_string;
        }
        memcpy(str + len, b.str, b.len);
        len += b.len;
        return (*this);
    }
    String& operator+=(const char& b) {
        if (str == nullptr) {
            str = new char[1];
            *str = b;
            len = 1;
            size = 1;
            return (*this);
        }
        if (len + 1 >= size) {
            size *= 2;
            char *temp_string = new char[size];
            memcpy(temp_string, str, len);
            if (len > 0) {
                delete[] str;
            }
            str = temp_string;
        }
        *(str + len) = b;
        ++len;
        return (*this);
    }

    String substr(const uint64_t& start, const uint64_t& count) const{
        String temp_Str(count, '\0');
        memcpy(temp_Str.str, str + start, count);
        return temp_Str;
    }
    void push_back(const char& t) {
        *this += t;
    }
    void pop_back() {
        if (len == size / 4 && len != 0) {
            char *temp_str = new char[size / 2];
            --len;
            std::copy(str, str + len, temp_str);
            delete[] str;
            str = temp_str;
        } else {
            str[len - 1] = '\0';
            --len;
        }
    }
    bool empty() const {
        if (len == 0) {
            return true;
        } else {
            return false;
        }
    }
    void clear() {
        if (len > 0) {
            delete[] str;
            len = 0;
            size = 0;
        }
    }
    uint64_t length() const {
        return len;
    }
    char& front(){
        return *str;
    }
    const char& front() const {
        return *str;
    }
    char& back() {
        return *(str + len - 1);
    }
    const char& back() const{
        return *(str + len - 1);
    }
    uint64_t find(const String& sub) const {
        if (sub.len > len) {
            return len;
        }
        uint64_t i = 0;
        while (i < len - sub.len + 1) {
            while ((str[i] != sub.str[0]) && (i < len)) {
                ++i;
            }
            if (i >= len) {
                return len;
            }
            uint64_t k = 0;
            while ((i + k < len) && (k < sub.len)) {
                if ((i + k < len) && (sub.str[k] != str[i + k])) {
                    ++i;
                    break;
                }
                if (i >= len)
                    return len;
                ++k;
            }
            if (k == sub.len) {
                return i;
            }
        }
        return len;
    }
    uint64_t rfind(const String& sub) const {
        if (sub.len > len) {
            return len;
        }
        int64_t i = len - sub.len;
        while (i >= 0) {
            while ((str[i] != sub.str[0]) && (i >= 0)) {
                --i;
            }
            if (i < 0) {
                return len;
            }
            uint64_t k = 0;
            while ((i >= 0) && (k < sub.len)) {
                if (sub.str[k] != str[i + k]) {
                    --i;
                    break;
                }
                if (i < 0)
                    return len;
                ++k;
            }
            if (k == sub.len) {
                return i;
            }
        }
        return len;
    }
};

std::istream& operator>>(std::istream& in, String& s) {
    s.clear();
    char t;
    while ((in.get(t)) && !(isspace(t)) && !(t == '\0')) {
        s += t;
    }
    return in;
}
std::ostream& operator<<(std::ostream& out, const String& s) {
    for (uint64_t i = 0; i < s.length(); ++i) {
        out << s[i];
    }
    return out;
}
String operator+(const String& a, const String& b) {
    String copy = a;
    copy += b;
    return copy;
}
