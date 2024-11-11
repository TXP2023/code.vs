#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <iostream>
#include <stdint.h>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< ll > v;
ll n, cnt = 0;

int main() {
    freopen("input.txt", "r", stdin);

    n = readf< ll >();

    v.resize(n);
    for (ll &i : v) {
        i = readf< ll >();
    }

    std::sort(v.begin(), v.end());

    for (size_t i = 0; i < n; i++) {
        if (v[cnt] >= v[i]) {
            continue;
        }
        cnt++;
    }

    printf("%lld\n", n - cnt);
    return 0;
}

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