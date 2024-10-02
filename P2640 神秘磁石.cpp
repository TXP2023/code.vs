#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <stdint.h>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< bool > vis;
bool b = false;
ll n, m;

int main() {
    freopen(".in", "r", stdin);

    n = readf< ll >(), m = readf< ll >();

    vis.resize(n + 1, true);

    for (size_t i = 2; i <= n; i++) {
        if (vis[i]) {
            for (size_t j = 2; j * i <= n; j++) {
                vis[j * i] = false;
            }
        }
    }

    for (size_t i = 2; i + m <= n; i++) {
        if (vis[i] && vis[i + m]) {
            printf("%u %u\n", i, i + m);
            b = true;
        }
    }
    if (b == false) {
        printf("empty");
    }
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