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

std::vector< ll > v;
ll n, m;

int main()
{
    n = readf< ll >(), m = readf< ll >();

    for (ll i = 0; i < m; i++)
    {
        v.push_back(readf< ll >());
    }


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