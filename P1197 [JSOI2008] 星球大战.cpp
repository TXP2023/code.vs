#include <stdio.h>
#include <ctype.h>
#include <climits>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <numeric>

typedef long long int ll;
typedef unsigned long long int unill;

#define size 14

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< ll > graph[size];
std::pair< ll, ll > edge[size];
ll set[size], damage[size], ans[size];
bool cities[size];
ll n, m, k;

inline ll findSet(ll x)
{
    return (set[x] == x) ? x : set[x] = findSet(set[x]);
}

int main()
{
    freopen(".in", "r", stdin);
    
    n = readf< ll >(), m = readf< ll >();
    
    for (size_t i = 0; i < m; i++) {
        ll u = readf< ll >(), v = readf< ll >();
        graph[u].push_back(v);
        graph[u].push_back(u);
        edge[i].first = u, edge[i].second = v;
    }

    k = readf< ll >();
    std::fill(cities, cities + n, false);
    for (size_t i = 0; i < k; i++) {
        damage[i] = readf< ll >();
        cities[damage[i]] = true;
    }

    ll total = n - k;
    std::iota(set, set + n, 0);
    for (size_t i = 0; i < m; i++) {
        if (!cities[edge[i].first] && !cities[edge[i].second] && findSet(edge[i].second) != findSet(edge[i].first)) {
            total--;
            set[findSet(edge[i].second)] = findSet(edge[i].first);
        }
    }
    ans[k] = total;

    for (ll i = k - 1; i >= 0; i--) {
        total++;
        cities[damage[i]] = false;
        for (ll j : graph[damage[i]]) {
            if (!cities[j] && findSet(set[j]) != findSet(set[damage[i]])) {
                total--;
                set[findSet(set[j])] = findSet(set[damage[i]]);
            }
        }
        ans[i] = total;
    }

    for (size_t i = 0; i < k + 1; i++) {
        printf("%lld\n", ans[i]);
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