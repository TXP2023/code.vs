#define  _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>

typedef long long ll;
typedef unsigned long long unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< std::vector< ll > > v;
ll n, ans = 0; //n个武将

int main()
{
    freopen(".in", "r", stdin);

    n = readf< ll >();
    
    v.resize(n, std::vector< ll >(n));
    for (ll i = 0; i < n; i++)
    {
        for (ll j = i + 1; j < n; j++)
        {
            v[i][j] = readf< ll >();
            v[j][i] = v[i][j];
        }
    }

    for (ll i = 0; i < n; i++)
    {
        std::sort(v[i].begin(), v[i].end());
        ans = std::max(ans, v[i][n - 2]);
    }
    printf("1\n%lld\n", ans);
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