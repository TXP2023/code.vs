#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <initializer_list>

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

std::vector< ll > flowers;
ll t;

int main() {
    freopen("input.txt", "r", stdin);

    t = readf< ll >();

    while (t--) {
        ll n = readf< ll >(), k = readf< ll >();
        flowers.resize(n);
        for (ll &i : flowers) {
            i = readf< ll >();
        }
        if (k == 0) {
            ll max = -1, sum = 0;
            for (size_t i = 0; i < flowers.size(); i++) {
                if (max > flowers[i]) {
                    sum += max;
                }
                else {
                    sum += flowers[i];
                    max = flowers[i];
                }
            }
            printf("%lld\n", sum);
        }
        else {
            ll max_p = 0;
            for (size_t i = 1; i < n; i++) {
                if (flowers[i] > flowers[0]) {
                    std::swap(flowers[i], flowers[0]);
                    max_p = i;
                }
            }
            if (max_p != 0) {
                if ((k - 1) % 2 == 1 && n == 2) {
                    std::swap(flowers[0], flowers[1]);
                    for (size_t i = 2; i < n; i++) {
                        if (flowers[i] > flowers[0]) {
                            std::swap(flowers[i], flowers[0]);
                        }
                    }
                    printf("%lld\n", flowers[0] + flowers[1] * (n - 1));
                }
                else {
                    printf("%lld\n", flowers[0] * n);
                }
            }
            else {
                if (k % 2 == 1 && n == 2) {
                    for (size_t i = 2; i < n; i++) {
                        if (flowers[i] > flowers[0]) {
                            std::swap(flowers[i], flowers[0]);
                        }
                    }
                    printf("%lld\n", flowers[0] + flowers[1] * (n - 1));
                }
                else {
                    printf("%lld\n", flowers[0] * n);
                }
            }
            
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