#include <vector>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <initializer_list>

#define READ false

typedef int64_t ll;
typedef unsigned long long int ull;

#if READ
//函数前向声明
//快读函数
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

ll t, k;
float r;

int main() {
    freopen("input.txt", "r", stdin);

    readf(&t);
    while (t--) {
        readf(&k);
        if (k == 0) {
            puts("NO!");
            continue;
        }
        if (k % 2 == 1) {
            puts("1");
            continue;
        }
        r = k + 0.5;
        ull ans = 0;
        while (true) {
            float a = (r * std::ceil(r));
            ll b = (r * std::ceil(r));
            r = r * std::ceil(r);
            ans++;
            if (a - b == 0) {
                break;
            }
        }
        printf("%lld\n", ans);
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