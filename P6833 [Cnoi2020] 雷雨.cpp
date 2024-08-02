#include <vector>
#include <queue>
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

std::vector< std::vector< ll > > dits[3]; //3位 分别表示雷电， 红馆， 竹林
std::vector< std::vector< ll > > v;
ll n, m, a, b, c, ans = LLONG_MAX;

inline void dijkstra(ll _from, ll _to, std::vector< std::vector< ll > >& _dit)
{
    struct queData
    {
        ll x, y;
        ll val;
        bool operator <(const queData &other)const{
            return val > other.val;
        }
    };

    const short cx[4]{ -1,1,0,0 }, cy[4]{0,0,1,-1};
    std::vector< std::vector< bool > > vis(n, std::vector< bool >(m, false));
    _dit[_from][_to] = v[_from][_to];
    std::priority_queue< queData > que;
    que.push({ _from, _to, v[_from][_to] });
    while (!que.empty())
    {
        queData now = que.top();
        que.pop();
        if (vis[now.x][now.y])
        {
            continue;
        }
        vis[now.x][now.y] = true;
        for (size_t i = 0; i < 4; i++)
        {
            ll x = now.x + cx[i], y = now.y + cy[i];
            if (x >= 0 && x < n && y >= 0 && y < m && !vis[x][y] && now.val + v[x][y] < _dit[x][y])
            {
                _dit[x][y] = now.val + v[x][y];
                que.push({ x, y, _dit[x][y] });
            }
        }
    }
    return;
}

int main()
{
    freopen(".in", "r", stdin);

    n = readf< ll >(), m = readf< ll >(), a = readf< ll >(), b = readf< ll >(), c = readf< ll >();

    v.resize(n, std::vector< ll >(m));
    for (ll i = n-1; i >= 0; i--)
    {
        for (size_t j = 0; j < m; j++) 
        {
            v[i][j] = readf< ll >();
        }
    }
    
    for (std::vector< std::vector< ll > >& i : dits)
    {
        i.resize(n, std::vector< ll >(m, LLONG_MAX));
    }
    dijkstra(n - 1, --a, dits[0]), dijkstra(0, --b, dits[1]), dijkstra(0, --c, dits[2]);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        { 
            ans = std::min(ans, dits[0][i][j] + dits[1][i][j] + dits[2][i][j] - v[i][j]*2);
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