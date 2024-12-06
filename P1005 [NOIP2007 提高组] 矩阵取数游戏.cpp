#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <string>
#include <cstdarg>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <initializer_list>

#define READ false

typedef int64_t ll;
typedef uint64_t unill;

#if READ
//函数前向声明
//快读函数
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

class large_int
{
public:
    inline const char* show_to_const_char();

    inline void input();

    void operator =(const large_int other);

    large_int operator +(const large_int other);

    large_int operator *(const int other);

    inline ll length();

private:
    std::string number;

    
};

inline ll large_int::length() {
    return number.length();
}

//输入一个高精度类
inline void large_int::input() {
    std::string s;
    std::cin >> s;
    ll length = s.length();
    number.resize(length);
    for (size_t i = 0; i < s.length(); i++) {
        number[i] = s[length - i];
    }


    return;
}

//这个高精度类所代表的数字转化为字符串格式
inline const char* large_int::show_to_const_char() {
    const char* p = number.data();
    return p;
}

void large_int::operator=(const large_int other) {
    number = other.number;
    return;
}

large_int large_int::operator+(const large_int other) {
    large_int num1 = *this, num2 = other, summation;
    
    if (num1.length() < num2.length()) {
        std::swap(num1, num2);
    }
    summation.number.resize(num1.length() + 1);
    summation.number = num1.number;

    //加和
    for (size_t i = 0; i < num2.length(); i++) {
        summation.number[i] += num2.number[i];
    }

    //进位
    for (size_t i = 0; i < summation.length() - 1; i++) {
        if (summation.number[i] - '0' >= 10) {
            summation.number[i + 1]++;
            summation.number[i] -= ('9' + 1);
        }
    }
    if (summation.number.back() > '9') {
        summation.number.resize(summation.number.length() + 1);
        *(summation.number.end() - 1) = '1';
        *(summation.number.end() - 2) -= ('9' + 1);
    }
    return summation;
}

large_int large_int::operator*(const int other) {
    large_int num1 = *this;
    std::vector< ll > num(num1.length());
    for (size_t i = 0; i < num.size(); i++) {
        num[i] = num1.number[i] - '0';
        num[i] *= other;
    }

    for (size_t i = 0; i < num.size(); i++) {
        if (num[i] >= 10) {
            num[i + 1] +=  
        }
    }

    return large_int();
}

int main() {
    freopen("input.txt", "r", stdin);

    return 0;
}

#if READ
template< typename T >
inline T readf() {
#if false
    T sum = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0') ch = getchar();
    while (ch >= '0' && ch <= '9') sum = sum * 10 + ch - 48, ch = getchar();
    return sum;
#else
    T ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    return sgn ? -ret : ret;
#endif
}
#else
template< typename Type >
inline Type readf(Type* p) {
    Type ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    if (p != NULL) {
        *p = Type(sgn ? -ret : ret);
    }
    return sgn ? -ret : ret;
}
#endif