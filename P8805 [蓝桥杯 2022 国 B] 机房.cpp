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

std::vector< std::vector< ll > > edge;
std::vector< std::vector< ll > > father;
std::vector< ll > depth, vis, sum;
ll n, m;

inline void addEdge(ll from, ll to)
{
    edge[from].push_back(to);
    edge[to].push_back(from);
}

//处理父节点数组 和深度数组
inline void dfsDepth(ll v/*当前查看的父节点*/, ll fa/*当前查看的父节点的父节点*/)
{
    for (size_t i = 0; i < edge[v].size(); i++)
    {
        ll child = edge[v][i];
        if (child == fa)
        {
            continue;
        }
        depth[child] = depth[v] + 1; //更新子节点权值为父节点+1
        father[child][0] = v; //记录父节点 2的0次方为1
        sum[child] = sum[v] + vis[child];
        dfsDepth(child, v);
    }
    return;
}

inline void init()
{
    for (size_t j = 1; j <= 18; j++)
    {
        for (size_t i = 0; i < n; i++)
        {
            father[i][j] = father[father[i][j - 1]][j - 1];
        }
    }
    return;
}


inline ll LCA(ll u, ll v)
{
    if (u == v)
    {
        return u;
    }
    if (depth[u] < depth[v])
    {
        std::swap(u, v);
    }

    for (ll i = 18; i >= 0; i--)
    {
        if (depth[u] - depth[v] >= (1 << i)) //如果目前的差距大于2的i次方，那么要更新u，并计算2的i+1次方
        {
            u = father[u][i]; //往上提
        }
    }

    if (u == v)
    {
        return u;
    }

    for (ll i = 18; i >= 0; i--)
    {
        if (father[u][i] != father[v][i])
        {
            u = father[u][i], v = father[v][i]; //往上提
        }
    }
    return father[u][0];
}

int main()
{
    freopen(".in", "r", stdin);

    n = readf< ll >(), m = readf< ll >();

    edge.resize(n);
    sum.resize(n, 0);
    vis.resize(n, 0);
    for (size_t i = 1; i <= n-1; i++)
    {
        ll from = readf< ll >(), to = readf< ll >();
        vis[--from]++, vis[--to]++;
        addEdge(from, to);
    }

    for (size_t i = 0; i < n; i++)
    {
        vis[i] = edge[i].size(), sum[i] = edge[i].size();
    }

    father.resize(n, std::vector< ll >(19, 0));
    depth.resize(n, 0);
    depth[0] = 1;
    dfsDepth(0, 0);

    init();
    while (m--)
    {
        ll u = readf< ll >(), v = readf< ll >();
        ll uvLca = LCA(--u, --v);
        printf("%lld\n", sum[u] + sum[v] - sum[uvLca] * 2 + vis[uvLca]);
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