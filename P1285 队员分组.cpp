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

std::vector< std::vector< bool > > graph;
std::vector< ll > color;
ll n;

inline void stain() {
    ll col_cnt = 0;
    std::vector< bool > tag(n, false);
    tag[0] = true, color[0] = col_cnt;
    
    return;
}

int main() {
    freopen("input.txt", "r", stdin);

    n = readf< ll >();
    for (size_t u = 0; u < n; u++) {
        ll v;
        while (true) {
            v = readf< ll >();
            if (v == 0) {
                break;
            }
            graph[u][v] = true;
        }
    }
    for (size_t u = 0; u < n; u++) {
        for (size_t v = 0; v < n; v++) {
            if (!(graph[u][v] && graph[v][u])) {
                graph[u][v] = false;
                graph[v][u] = false;
            }
        } 
    }

    color.resize(n, -1);
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