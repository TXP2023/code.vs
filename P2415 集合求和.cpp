#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <iostream>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector < ll > v;
ll ans;


inline void sum(unill i, unill s)
{
    if (i == v.size())
    {
        ans += s;
        return;
    }
    if (i == v.size()-1)
    {
        //ans += s;
        sum(i + 1, s + v[i]);
        return;
    }
    sum(i + 1, s + v[i]);
    sum(i + 1, s);
    return;
}

int main()
{
    freopen(".in", "r", stdin);

    unill* n = new unill;
    while (scanf("%lld", n) != EOF)
    {
        v.push_back(*n);
    }
    sum(0, 0);

    printf("%llu\n", ans);
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