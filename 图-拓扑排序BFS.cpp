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

template< typename T1, typename T2, typename T3 >
inline void Topological_Sort_BFS(T1 _n, std::vector< std::vector< T2 > > _edge, std::vector< T3 > _v)
{
    std::queue< ll > que;
    for (ll i = 0; i < _n; i++)
    {
        if (!_v[i])
        {
            que.push(i);
        }
    }
    while (!que.empty())
    {
        for (ll i = 0; i < _edge[que.front()].size(); i++)
        {
            _v[_edge[que.front()][i]]--;
            if (!_v[_edge[que.front()][i]])
            {
                que.push(_edge[que.front()][i]);
            }
        }
    }
    return; 
}

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