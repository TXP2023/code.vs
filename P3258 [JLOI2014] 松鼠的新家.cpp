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
std::vector< ll > depth;
std::vector< ll > vis; //储存顺序
std::vector< ll > sum; //前缀和
ll n, m, ans = 0;

inline void dfsDepth(ll u, ll fa)
{
    for (ll i : edge[u])
    {
        if (i == fa)
        {
            continue;
        }
        depth[i] = depth[u] + 1;
        father[i][0] = u;
        dfsDepth(i, u);
    }
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

inline void dfs(ll u, ll fa)
{
    for (ll i : edge[u])
    {
        if (i == fa)
        {
            continue;
        }
        dfs(i, u);
        sum[u] += sum[i];
    }
}


int main()
{
    freopen(".in", "r", stdin);

    n = readf< ll >();

    vis.resize(n);
    for (ll &i : vis)
    {
        scanf("%lld", &i);
    }

    edge.resize(n);
    for (size_t i = 0; i < n-1; i++)
    {
        ll u = readf< ll >(), v = readf< ll >();
        edge[--v].push_back(--u);
        edge[u].push_back(v);
    }

    sum.resize(n, 0);
    depth.resize(n, 0);
    father.resize(n, std::vector< ll >(19, 0));
    depth[0] = 1;
    dfsDepth(0, 0);
    init();
    for (size_t i = 0; i < n - 1; i++)
    {
        ll uvlca = lca(vis[i] - 1, vis[i + 1]-1);
        sum[vis[i + 1] - 1]++;
        sum[vis[i] - 1]++;
        sum[uvlca]--;
        if (uvlca != 0)
        {
            sum[father[uvlca][0]]--;
        }
    }
    dfs(0, 0);
    for (size_t i = 1; i < n; i++)
    {
        sum[vis[i]-1]--;
    }

    for (ll i : sum)
    {
        printf("%lld\n", i);
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