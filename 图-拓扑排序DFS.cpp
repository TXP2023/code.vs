#include <stdio.h>
#include <vector>
#include <ctype.h>
#include <queue>

typedef long long ll;
typedef unsigned long long unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< std::vector< ll > > edge; //邻接链表存图
std::vector< ll > v; //入度
ll n, m; //n个点 m个边



int main()
{
    n = readf< ll >(), m = readf< ll >();

    //输入
    edge.resize(n);
    for (ll i = 0; i < m; i++)
    {
        edge[readf< ll >() - 1].push_back(readf< ll >() - 1);
    }

    //计算入度
    v.resize(n, 0);
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < edge[i].size(); j++)
        {
            v[edge[i][j]]++;
        }
    }


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