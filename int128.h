#pragma once
#include <string>
#include <iostream>
#include <vector>

typedef long long int ll;

class large_int {
public:
    inline const char* show_to_const_char();

    inline std::string show_to_string();

    inline void input();

    void operator =(const large_int other);

    large_int operator +(const large_int other);

    large_int operator *(const int other);

private:
    std::string number;

    inline ll length();
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
        number[i] = s[length - i - 1];
    }
    return;
}

//这个高精度类所代表的数字转化为字符串格式
inline const char* large_int::show_to_const_char() {
    const char* p = number.data();
    return p;
}

inline std::string large_int::show_to_string() {
    std::string s;
    s.resize(number.length());
    for (size_t i = 0; i < number.length(); i++) {
        s[i] = number[number.length() - i - 1];
    }
    return s;
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