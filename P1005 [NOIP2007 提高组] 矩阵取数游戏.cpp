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

std::vector< std::vector< ll > > matrix;
std::vector< std::vector< ll > > dp;
ll n, m;

inline ll sum(ll x) {
    ll sum = 0;
    for (size_t i = 0; i < n; i++) {
        sum += matrix[i][x];
    }
    return sum;
}

int main() {
    freopen("input.txt", "r", stdin);
    
    readf(&n), readf(&m);
    
    matrix.resize(n, std::vector< ll >(m));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            readf(&matrix[i][j]);
        }
    }

    dp.resize(m, std::vector< ll >(m, 0));
    for (size_t i = 0; i < m; i++) {
        dp[i][i] = sum(i) * m;
    }
    for (size_t i = 0; i + 1 < m; i++) {
        ll sum_big = 0, sum_small = 0;
        for (size_t j = 0; j < n; j++) {
            sum_big += std::max(matrix[i][j], matrix[i + 1][j]);
            sum_small += std::min(matrix[i][j], matrix[i + 1][j]);
        }
        dp[i][i + 1] = sum_big * m + sum_small * (m - 1);
    }

    for (size_t len = 2; len < m; len++) {
        for (size_t i = 0; i + len < n; i++) {
            uint64_t j = i + len;
            ll sum_big = 0, sum_small = 0;
            for (size_t k = 0; k < n; k++) {
                sum_big += std::max(matrix[i][k], matrix[j][k]);
                sum_small += std::min(matrix[i][k], matrix[j][k]);
            }
            dp[i][i + 1] = sum_big * (m - len) + sum_small * (m - len - 1) + dp[i - 1][j - 1];
        }
    }

    printf("%lld\n", dp[m][m]);
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