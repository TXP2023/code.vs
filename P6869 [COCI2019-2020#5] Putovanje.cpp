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

struct data {
    ll to;
    std::pair< ll, ll >  ticket; //单程， 多程
};

std::vector< std::vector< data > > graph;
std::vector< std::vector< ll > > father;
std::vector< ll > depth;
std::vector< ll > sum;
std::vector< std::pair< ll, ll > > edge;
ll n, ans = 0;

inline void dfsDepth(ll u, ll fa)
{
    for (data i : graph[u]) {
        if (i.to == fa) {
            continue;
        }
        depth[i.to] = depth[u] + 1;
        father[i.to][0] = u;
        dfsDepth(i.to, u);
    }
    return;
}

inline void init()
{
    for (size_t j = 1; j <= 18; j++) {
        for (size_t i = 0; i < n; i++) {
            father[i][j] = father[father[i][j - 1]][j - 1];
        }
    }
    return;
}

inline ll lca(ll u, ll v)
{
    if (depth[u] < depth[v]) {
        std::swap(u, v);
    }

    for (ll i = 18; i >= 0; i--) {
        if (depth[u] - depth[v] >= (1 << i)) {
            u = father[u][i];
        }
    }

    if (u == v) {
        return u;
    }

    for (ll i = 18; i >= 0; i--) {
        if (father[u][i] != father[v][i]) {
            u = father[u][i], v = father[v][i];
        }
    }

    return father[u][0];
}

inline void updateAns(ll u)
{
    for (data i : graph[u]) {
        if (i.to != father[u][0]) {
            updateAns(i.to);
            sum[u] += sum[i.to];
        }
    }
}

int main()
{
    freopen(".in", "r", stdin);

    n = readf< ll >();
    for (size_t i = 0; i < n - 1; i++) {
        ll from = readf< ll >(), to = readf< ll >(), c1 = readf< ll >(), c2 = readf< ll >();
        graph[--from].push_back(data{ --to, {c1, c2} });
        graph[to].push_back(data{ from, {c1, c2} });
    }
    
    for (size_t i = 0; i < n - 1; i++) {
        sum[i]++;
        sum[i + 1]++;
        sum[lca(i, i + 1)] -= 2;
    }

    updateAns(0);

    for (size_t i = 0; i < n; i++) {
        
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
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    return sgn ? -ret : ret;
#endif
}