#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <queue>
#include <climits>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< std::vector< unill > > edge, revGraph;
std::vector< unill > v; //储存每个城市的市场价
std::vector< unill > dits; //储存到达每个城市时进口水晶球的最低价格
std::vector< bool > ditb;
ll n, m, ans = 0;

inline void spfa()
{
    std::priority_queue< std::pair< unill, unill > > que;
    que.push({ v.front(), 0 });
    while (!que.empty())
    {
        std::pair< unill, unill > now = que.top();
        que.pop();
        for (size_t i = 0; i < edge[now.second].size(); i++)
        {
            if (now.first < dits[edge[now.second][i]])
            {
                dits[edge[now.second][i]] = now.first;
                que.push({ std::min(now.first, v[edge[now.second][i]]), edge[now.second][i] });
            }
        }
    }
    return;
}

inline void  ConnectivityJudgment()
{
    std::queue< ll > que;
    que.push(n - 1);
    while (!que.empty())
    {
        ll now = que.front();
        que.pop();
        for (size_t i = 0; i < revGraph[now].size(); i++)
        {
            if (!ditb[revGraph[now][i]])
            {
                ditb[revGraph[now][i]] = true;
                que.push(revGraph[now][i]);
            }
        }
    }
    return;
}

int main()
{
    //freopen(".in", "r", stdin);

    n = readf< ll >(), m = readf< ll >();

    v.resize(n);
    for (size_t i = 0; i < n; i++)
    {
        v[i] = readf< ll >();
    }

    edge.resize(n);
    revGraph.resize(n);
    for (size_t i = 0; i < m; i++)
    {
        unill from = readf< unill >(), to = readf< unill >(), z = readf< unill >();
        switch (z)
        {
        case 1:
            edge[--from].push_back(--to);
            revGraph[to].push_back(from);
            break;
        case 2:
            edge[--from].push_back(--to);
            edge[to].push_back(from);
            revGraph[from].push_back(to);
            revGraph[to].push_back(from);
            break;
        }
    }

    dits.resize(n, LLONG_MAX);
    spfa();

    ditb.resize(n, false);
    ditb[n - 1] = true;
    ConnectivityJudgment();

    for (size_t i = 0; i < n; i++)
    {
        if (v[i] > dits[i] && ditb[i])
        {
            ans = std::max(ans, ll(v[i] - dits[i]));
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

