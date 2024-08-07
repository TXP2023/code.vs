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

std::vector< ll > depth;
std::vector< std::vector< ll > > edge;
std::vector< std::vector< ll > > father;
std::vector< ll > vis;
ll n, m, ans = 0;

inline void dfsDepth(ll u, ll fa)
{
    for (ll v : edge[u])
    {
        if (v == fa)
        {
            continue;
        }
        depth[v] = depth[u] + 1;
        father[v][0] = u;
        dfsDepth(v, u);
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

inline ll lca(ll u, ll v)
{
    if (depth[u] < depth[v])
    {
        std::swap(u, v);
    }
    for (ll i = 18; i >= 0; i--)
    {
        if (depth[u] - depth[v] >= (1 << i)) 
        {
            u = father[u][i];
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
            u = father[u][i], v = father[v][i];
        }
    }
    return father[u][0];
}

int main()
{
    freopen(".in", "r", stdin);
    
    n = readf< ll >();

    edge.resize(n);
    for (ll i = 0; i < n-1; i++)
    {
        ll u = readf< ll >(), v = readf< ll >();
        edge[--u].push_back(--v);
        edge[v].push_back(u);
    }

    m = readf< ll >();
    vis.resize(m);
    for (ll &i : vis)
    {
        scanf("%lld", &i);
    }

    father.resize(n, std::vector< ll >(19, 0));
    depth.resize(n, 0);
    depth[0] = 1;
    dfsDepth(0, 0);
    init();


    for (size_t i = 0; i < m-1; i++)
    {
        ll uvlca = lca(vis[i] - 1, vis[i + 1] - 1);
        ans += depth[vis[i] - 1] - depth[uvlca] + depth[vis[i + 1] - 1] - depth[uvlca];
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