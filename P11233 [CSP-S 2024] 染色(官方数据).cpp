#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <iostream>
#include <stdint.h>

#define READ false

typedef int64_t ll;
typedef uint64_t unill;

#if READ
//函数前向声明
//快读函数
template< typename T >
inline T readf();
#else
template< typename T >
inline T readf(int num_arge, ...);
#endif

int main() {
    freopen("input.txt", "r", stdin);
    ll n = 0;

    std::cout << readf< ll >(0);
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
inline T readf(int num_arge, ...) {
    T ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    va_list args;
    va_start(args, num_arge);
    //*num_input = sgn ? -ret : ret;
    for (size_t i = 0; i < num_arge; i++) {
        //*args = sgn ? -ret : ret;
        *(va_arg(args, T*)) = sgn ? -ret : ret;
    }
    va_end(args);
    return sgn ? -ret : ret;
}
#endif