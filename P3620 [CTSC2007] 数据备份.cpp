#define  _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <queue>
#include <limits.h>

typedef long long ll;
typedef unsigned long long unill;

struct data
{
    ll d;
    ll l, r; //left 和 right
};

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::priority_queue<std::pair< ll, ll>, std::vector< std::pair< ll, ll> >, std::greater< std::pair< ll, ll> > > que;
std::vector< bool > vbool;
std::vector< data > v;
ll n, k, ans = 0;

inline void del(ll x)
{
    v[x].l = v[v[x].l].l;
    v[v[x].l].r = x;
    v[x].r = v[v[x].r].r;
    v[v[x].r].l = x;
}

int main()
{
    freopen(".in", "r", stdin);

    n = readf< ll >(), k = readf< ll >();

    //输入序列，计算差分数组
    ll* old = new ll(readf< ll >());
    v.resize(n + 1);
    v[0].d = LONG_MAX;
    vbool.resize(n+1, false);
    for (ll i = 1; i <= n-1; i++)
    {
        ll input = readf< ll >();
        v[i] = { input - *old, i - 1,i + 1 };
        *old = input;
        que.push({ v[i].d, i});
    }
    v[n].d = LONG_MAX;
    delete old;

    for (size_t i = 0; i < k; i++)
    {
        while (vbool[que.top().second])
        {
            que.pop();
        }

        ans += que.top().first;
        vbool[v[que.top().second].l] = vbool[v[que.top().second].r] = true;
        v[que.top().second].d = v[v[que.top().second].r].d + v[v[que.top().second].l].d - v[que.top().second].d;
        que.push({ v[que.top().second].d, que.top().second });
        del(que.top().second);
        que.pop();
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
