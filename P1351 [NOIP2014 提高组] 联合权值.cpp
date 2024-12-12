#pragma once
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
#define inf 1e18
#define mod ll(1e4 + 7)

typedef long long int ll;
typedef unsigned long long int unill;

//快读函数声明
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

std::vector< std::vector< ll > > graph;
std::vector< ll > w;
ll n, ans, ans_max = 0;

inline void add_edge(ll u, ll v) {
    graph[--v].push_back(--u);
    graph[u].push_back(v);
    return;
}

int main() {
    freopen("input.txt", "r", stdin);

    readf(&n);

    graph.resize(n);
    for (size_t i = 0; i < n - 1; i++){
        add_edge(readf< ll >(), readf< ll >());
    }

    w.resize(n);
    for (size_t i = 0; i < n; i++) {
        readf(&w[i]);
    }

    for (size_t i = 0; i < n; i++) /*枚举所以中转点*/ {
        ll max1 =  0, max2 = 0;
        ll summation1 = 0, summation2 = 0;
        for (size_t u = 0; u < graph[i].size(); u++) {
            if (w[graph[i][u]] > max1) {
                max2 = max1;
                max1 = w[graph[i][u]];
            }
            else {
                if (w[graph[i][u]] > max2) {
                    max2 = w[graph[i][u]];
                }
            }
            summation1 = (summation1 + w[graph[i][u]]) % mod;
            summation2 = (summation2 + w[graph[i][u]] * w[graph[i][u]]) % mod;
        }
        summation1 = summation1 * summation1 % mod;
        ans = (ans + summation1 + mod - summation2) % mod;
        if (ans_max < max1 * max2) {
            ans_max = max1 * max2;
        }
    }

    printf("%lld %lld", ans_max, ans);

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