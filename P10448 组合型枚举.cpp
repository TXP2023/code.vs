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

ll n, m;

inline void dfs(ll k, ll cnt, const std::vector< int > v) {
    if (cnt == m) {
        for (int i : v) {
            printf("%d ", i);
        }
        printf("\n");
        return;
    }
    if (k == n + 1) {
        return;
    }
    std::vector< int > v2 = v;
    v2.push_back(k);
    dfs(k + 1, cnt + 1, v2); //要这个
    if (cnt + (n - k) >= m) {
        dfs(k + 1, cnt, v); //不要这个
    }
    return;
}

int main() {
    freopen(".in", "r", stdin);

    n = readf< ll >(), m = readf< ll >();

    dfs(1, 0, {});

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