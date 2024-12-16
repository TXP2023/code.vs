#pragma once
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
#define MAX_INF 1e18

typedef long long int ll;
typedef unsigned long long int unill;

//¿ì¶Áº¯ÊýÉùÃ÷
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

std::vector< ll > v;
ll n, m;

int main() {
    freopen("input.txt", "r", stdin);

    readf(&n);
    v.resize(n);
    for (size_t i = 0; i < n; i++) {
        readf(&v[i]);
    }
    std::sort(v.begin(), v.end());

    readf(&m);

    while (m--) {
        std::string s;
        std::cin >> s;
        if (s == "mid") {
            if (v.size() % 2) {
                printf("%lld\n", v[(int(v.size() / 2))]);
            }
            else {
                printf("%lld\n", std::min(v[v.size() / 2 - 1], v[v.size() / 2]));
            }
        }
        else {
            ll x = readf< ll >();
            //std::vector< ll >::iterator it = lower_bound(v.begin(), v.end(), x);
            v.insert(lower_bound(v.begin(), v.end(), x), x);
        }
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