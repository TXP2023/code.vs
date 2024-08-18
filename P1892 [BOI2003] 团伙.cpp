#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <numeric>
#include <stdint.h>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

ll set[10000];
ll vis[10000]; //存每个人的敌人是谁
ll vfriends[10000]; //储存每个人的朋友数量
ll n, m, ans = 0;

inline ll findSet(ll x)
{
    if (set[x] == x) {
        return x;
    }
    else {
        return set[x] = findSet(set[x]);
    }
}



int main()
{
    freopen(".in", "r", stdin);

    n = readf< ll >(), m = readf< ll >();

    //vis.resize(n, -1);
    std::fill(vis, vis + n, -1);
    std::iota(set, set + n, 0);

    while (m--) {
        char ch = getchar();
        ll p = readf< ll >() - 1, q = readf< ll >() - 1;
        switch (ch) {
        case 'F':
            set[findSet(p)] = findSet(q);
            break;
        case 'E':
            if (vis[q] == -1) {
                vis[q] = findSet(p);
            }
            else {
                set[findSet(p)] = findSet(vis[q]);
            }

            if (vis[p] == -1) {
                vis[p] = findSet(q);
            }
            else {
                set[findSet(q)] = findSet(vis[p]);
            }
            break;
        }
    }

    std::fill(vfriends, vfriends + n, 0);
    for (size_t i = 0; i < n; i++) {
        vfriends[findSet(i)]++;
    }

    for (ll i : vfriends) {
        if (i) {
            ans++;
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
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    return sgn ? -ret : ret;
#endif
}