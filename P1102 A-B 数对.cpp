#include <vector>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <ctype.h>
#include <climits>
#include <stdint.h>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< ll > v;
ll n, c, ans = 0;

int main()
{
    freopen(".in", "r", stdin);

    n = readf< ll >(), c = readf< ll >();
    
    v.resize(n);
    for (size_t i = 0; i < n; i++){
        v[i] = readf< ll >();
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            if (i - j == c || j - i == c ) {
                ans++;
            }
        }
    }

    printf("%lld", ans);
    return 0;
}

template< typename T >
inline T readf()
{
#if false
    T sum = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0') ch = getchar();
    while (ch >= '0' && ch <= '9') sum = sum * 10 + ch - 48, ch = getchar();
    return sum;
#else
    T ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch))
    {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    return sgn ? -ret : ret;
#endif
}