#define  _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <string.h>
#include <ctype.h>

typedef long long ll;
typedef unsigned long long unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< std::vector< ll > > dp;
ll n, ans = -922337203685477580;

int main()
{
    //freopen("D:\\code.vs\\SHU_RU.in", "r", stdin);

    n = readf< ll >();

    dp.resize(n, std::vector< ll >(n, 0));
    for (ll i = 0; i < n; i++)
    {
        dp[i][i] = readf< ll >();
        ans = std::max(ans, dp[i][i]);
    }

    for (ll len = 1; len < n; len++)
    {
        for (ll i = 0; i + len < n; i++)
        {
            ll j = i + len;
            for (ll k = i; k < j; k++)
            {
                if (dp[i][k] == dp[k + 1][j])
                {
                    dp[i][j] = std::max(dp[i][j], dp[i][k] << 1);
                    ans = std::max(ans, dp[i][j]);
                }
                for (ll q = k + 1; q < j; q++)
                {
                    if (dp[i][k] == dp[q + 1][j])
                    {
                        dp[i][j] = std::max(dp[i][j], (dp[i][k] << 1) + dp[k + 1][q]);
                        ans = std::max(ans, dp[i][j]);
                    }
                }
            }
        }
    }

    printf("%lld\n", ans);
    return 0;
}

//快读函数
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