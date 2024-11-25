#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <initializer_list>

#define READ true

typedef int64_t ll;
typedef uint64_t unill;

#if READ
//函数前向声明
//快读函数
template< typename T >
inline T readf();
#else
template< typename T >
inline T readf(std::initializer_list< T* > li);
#endif

std::vector< ll > graph[10000];
ll vis[10000];
std::vector< ll > match;
ll n, ans = 0;

inline bool add_match(ll u, ll u2) /*尝试给右部图点u匹配*/ {
    if (vis[u] == u2) {
        return false;
    }
    vis[u] = u2;
    for (ll v : graph[u]) {
        if (match[v] == -1 || add_match(match[v], u2)) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);

    n = readf< ll >();

    for (size_t i = 0; i < n; i++){
        //graph[i] = { readf< ll >() - 1, readf< ll >() - 1};
        ll u = readf< ll >() - 1, v = readf< ll >() - 1;
        graph[u].push_back(i);
        graph[v].push_back(i);
    }

    //vis.resize(10000, -1);
    std::fill(vis, vis + 10000, -1);
    match.resize(n, -1);
    for (size_t i = 0; i < 10000; i++) {
        if (add_match(i, i)) {
            ans++;
        }
        else {
            break;
        }
    }
    printf("%lld\n", ans);
    return 0;
}

#if READ
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
#else
template< typename T >
inline T readf(std::initializer_list< T* > li) {
    T ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    //va_list args;
    //va_start(args, num_arge);
    for (auto i = li.begin(); i != li.end(); i++) {
        *i = sgn ? -ret : ret;
    }
    //va_end(args);
    return sgn ? -ret : ret;
}
#endif