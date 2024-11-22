#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <map>

#define READ true

typedef int64_t ll;
typedef uint64_t unill;

#if READ
//函数前向声明
//快读函数
template< typename T >
inline T readf();
#else
template< typename T >
inline T readf(std::initializer_list< T* > li);
#endif

std::vector< ll > dp;
std::vector< ll > last;
std::vector< ll > v;
std::vector< ll > sum;
ll t, n;

int main() {
    freopen("input.txt", "r", stdin);

    //readf({ &t });
    t = readf< ll >();

    while (t--) {
        //readf({ &n });
        n = readf< ll >();
        v.resize(n);
        sum.resize(n, 0);
        last.resize(1e6 + 5, -1);
        dp.resize(n, 0);
        for (size_t i = 0; i < n; i++) {
            //readf({ &v[i] });
            v[i] = readf< ll >();
        }
        for (size_t i = 1; i < n; i++) {
            sum[i] = (v[i] == v[i - 1]) ? sum[i - 1] + v[i] : sum[i - 1];
        }
        for (size_t i = 0; i < n; i++) {
            if (i > 0) {
                dp[i] = dp[i - 1];
            }
            if (last[v[i]] != -1) {
                dp[i] = std::max(dp[i], dp[last[v[i]] + 1] + v[i] + sum[i] - sum[last[v[i]] + 1]);
            }
            last[v[i]] = i;
        }
        printf("%lld\n", dp.back());
        v.clear();
        sum.clear();
        last.clear();
        dp.clear();
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
template< typename T >
inline T readf(std::initializer_list< T* > li) {
    T ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    //va_list args;
    //va_start(args, num_arge);
    for (auto i = li.begin(); i != li.end(); i++) {
        *i = sgn ? -ret : ret;
    }
    //va_end(args);
    return sgn ? -ret : ret;
}
#endif