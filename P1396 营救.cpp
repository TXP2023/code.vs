#include <vector>
#include <queue>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <set>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

template< typename T >
inline void inputf(T* p);

std::vector< std::vector< std::pair< ll/*点*/, ll/*边权*/ > > > graph;
std::vector< ll > edges;
ll n, m, s, t, ans;

inline bool djstl(ll max_w) {
    std::vector< bool > tag(n, false);
    tag[s] = true;
    
    std::queue< ll > que;
    que.push(s);
    while (!que.empty()) {
        ll u = que.front();
        que.pop();
        for (std::pair< ll/*点*/, ll/*边权*/ > i : graph[u]) {
            if (!tag[i.first] && i.second <= max_w) {
                tag[i.first] = true;
                que.push(i.first);
            }
        }
    }

    return tag[t];
}

int main() {
    freopen("input.txt", "r", stdin);

    inputf(&n), inputf(&m), inputf(&s), inputf(&t);
    s--, t--;

    graph.resize(n);
    for (size_t i = 0; i < m; i++) {
        ll u = readf< ll >(), 
            v = readf< ll >(), 
            w = readf< ll >();
        graph[--u].push_back({ --v, w });
        graph[v].push_back({ u, w });
        edges.push_back(w);
    }

    std::sort(edges.begin(), edges.end());
    edges.erase(std::unique(edges.begin(), edges.end()), edges.end());

    ll begin = 0, end = edges.size() - 1;
    while (begin <= end) {
        ll mid = (begin + end) >> 1;
        if (djstl(edges[mid])) {
            end = mid - 1;
            ans = edges[mid];
        }
        else {
            begin = mid + 1;
        }
    }

    printf("%lld\n", ans);

    return 0;
}

template< typename T >
inline T readf() {
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

template< typename T >
inline void inputf(T* p) {
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
    //return sgn ? -ret : ret;
    *p = (sgn) ? -ret : ret;
    return;
#endif
}