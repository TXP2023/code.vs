#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <stdint.h>

typedef int64_t ll;
typedef uint64_t unill;

const ll inf = std::numeric_limits< ll >::min();

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< std::vector< ll > >  graph;
std::vector< ll >  object; // object[i]为右部点i所匹配的左部点
std::vector< ll > ltag, rtag;// 左部点顶标 left-tag 右部点顶标 right-tag
std::vector< ll > pre; //?
std::vector< ll > slack;
std::vector< bool > rb; // right-bool 即右部点i是否已经分配
ll n, m;

inline void match(ll u/*左部图点u*/) /*给右部图的节点u匹配做节点*/ {
    ll l, r = 0, min_match_v = 0, min_match;
    std::fill(pre.begin(), pre.end(), 0);
    std::fill(slack.begin(), slack.end(), inf);
    std::fill(rb.begin(), rb.end(), false);

    object[r] = u;
    while (true) {
        ll v = object[u] /* v为当前考虑的右部图的节点的已分配左节点 */, delta = inf;
        rb[u] = true;
        for (size_t i = 0/*右部图的点i*/; i < n; i++) {
            if (rb[i]) {
                continue;
            }
            if (slack[i] > ltag[v] + rtag[i] - graph[v][i]) {
                slack[i] = ltag[v] + rtag[i] - graph[v][i];
                rb[i] = v;
            }
            if (slack[i] < delta) {
                delta = slack[i];
                min_match_v = i;
            }
        }
        for (size_t i = 0; i < length; i++) {

        }
    }
}

inline ll Kuhn_Munkres() {
    //初始化
    object.resize(n, -1);
    ltag.resize(n, 0);
    rtag.resize(n, 0);
    pre.resize(n, -1);
    rb.resize(n, 0);
    for (size_t i = 0; i < n; i++) {

    }
}

int main() {
    freopen(".in", "r", stdin);

    n = readf< ll >(), m = readf< ll >();

    graph.resize(n, std::vector< ll >(n, 0)); //graph[i][j]为左部点i与右部点j之间的权值
    for (size_t i = 0; i < m; i++){
        ll u1 = readf< ll >(), v2 = readf< ll >(), w = readf< ll >();
        graph[u1 - 1][v2 - 1] = w;
    }


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