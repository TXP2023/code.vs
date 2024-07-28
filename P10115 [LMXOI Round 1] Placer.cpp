#define  _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <string>

typedef long long ll;
typedef unsigned long long unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< std::vector< bool > > vbool; //vbool[i,j]为区间i~j是否为合法序
std::vector< std::vector< ll > > dp; 
std::vector< ll > v;
//std::string str;
std::vector< char > str;
ll n, ans = 0;

int main(void)
{
    freopen(".in", "r", stdin);

    n = readf< ll >();

    for (ll i = 0; i < n; i++)
    {
        char input; 
    }
    for (ll i = 0; i < n; i++)
    {
        v.push_back(readf< ll >());
    }

    dp.resize(n, std::vector< ll >(n, 0));
    vbool.resize(n, std::vector< bool >(n, false));
    for (ll i = 0; i < n-1; i++)
    {
        if (str[i] == '(' && str[i + 1] == ')')
        {
            vbool[i][i + 1] = true;
            vbool[i + 1][i] = true;
            dp[i][i + 1] = std::max(dp[i][i + 1], v[i + 1] - v[i]);
            ans = std::max(dp[i][i + 1], ans);
        }
    }

    for (ll len = 2; len  < n; len++)
    {
        for (ll i = 0; i + len < n; i++)
        {
            ll j = i + len;
            //可以分为两种情况，第一种为由多个合法的序列扩展而来，第二种为由1个合法的括号序列再由1对括号包裹而来
            for (ll k = i; k < j; k++) //情况1
            {
                if (vbool[i][k] && vbool[k+1][j])
                {
                    vbool[i][j] = true;
                }
                //vbool[i][j] = true;
                dp[i][j] = std::max(dp[i][k] + dp[k + 1][j], dp[i][j]);
                if (vbool[i][k] && !vbool[k + 1][j])
                {
                    dp[i][j] = std::max(dp[i][k], dp[i][j]);
                }
                if (!vbool[i][k] && vbool[k + 1][j])
                {
                    dp[i][j] = std::max(dp[k+1][j], dp[i][j]);
                }
            }
            //情况2 
            if (vbool[i+1][j-1] && str[i] == '(' && str[j] == ')') //判断更小的括号序列是否合法
            {
                vbool[i][j] = true;
                dp[i][j] = std::max(dp[i][j], v[j] - v[i]);
            }
            ans = std::max(ans, dp[i][j]);
        }
    }

    printf("%lld\n", ans);
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