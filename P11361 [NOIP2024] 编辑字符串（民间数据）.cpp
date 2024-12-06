#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <initializer_list>

#define READ false

typedef long long int ll;
typedef unsigned long long int unill;

#if READ
//函数前向声明
//快读函数
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

std::vector < std::pair < int16_t/*值*/, bool/*是否可以变换*/ > > s1, s2;
ll t, n;


inline void slove() {
    readf(&n);
    s1.resize(n), s2.resize(n);
    for (size_t i = 0; i < n; i++) {
        readf(&s1[i].first);
    }
    for (size_t i = 0; i < n; i++) {
        readf(&s2[i].first);
    }
    for (size_t i = 0; i < n; i++) {
        s1[i].second = readf< int16_t >();
    }
    for (size_t i = 0; i < n; i++) {
        s2[i].second = readf< int16_t >();
    }

    std::vector< std::vector< ll > > num;
    num.resize(, std::vector< ll >(2, 0)); 
}

int main() {
    freopen("input.txt", "r", stdin);

    readf(&t);
    while (t--) {
        slove();
    }


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