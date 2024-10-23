#include <vector>
#include <queue>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <stdint.h>
#include <cstdio>

typedef long long int ll;
typedef unsigned long long int  ull;
typedef long double lf;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< bool > ltag, rtag; //匹配
std::vector< ll > Lmatch, Rmatch; //匹配
std::vector< ll > Ltop, Rtop; //顶标
std::vector< ll > pre;
std::vector< ll > slack;
std::vector< std::vector< ll > > graph;
ull n, m;

inline void add_Augment(ll u); //增加增广路径
inline void Kuhn_Munkres(); //KM算法
inline void replace(ll u); //转移？

inline void Kuhn_Munkres() {
    std::fill(slack.begin(), slack.end(), LLONG_MAX);
    std::fill(pre.begin(), pre.end(), -1);
    std::fill(ltag.begin(), ltag.end(), false);
    std::fill(rtag.begin(), rtag.end(), false);
    for (size_t i = 0/*这里的i是枚举左部图点*/; i < n; i++) {
        add_Augment(i);
    }
    return;
}

inline void add_Augment(ll u) {
    std::queue< ll > que;//左部图点队列
    que.push(u);

    while (true) {
        while (!que.empty()) {
            ll v = que.front(); que.pop();
            ltag[v] = true;
            for (size_t i = 0/*这里的i是右部图点*/; i < n; i++) {
                if (!rtag[i]/*这个右部图点没有被匹配*/ && Ltop[u] + Rtop[i] - graph[u][i] < slack[i]) {
                    slack[i] = Ltop[u] + Rtop[i] - graph[u][i];
                    pre[i] = v;
                    if (slack[i] == 0)/*如果当前不存在差值, 添加增广路*/ {
                        rtag[i] = true;
                        if (Rmatch[i] == -1) {
                            replace(i);
                            return;
                        }
                        else {
                            que.push(Rmatch[i]);
                        }
                    }
                }
            }
        }
        ll Difference = LLONG_MAX/*找最小差值*/;
        for (size_t i = 0; i < n; i++) {
            if (!rtag[i]) {
                Difference = std::min(Difference, slack[i]);
            }
        }
    }
}


inline void replace(ll u) {
    ll t;
    while (u) {
        t = Rmatch[pre[u]];
        Rmatch[pre[u]] = u;
        Rmatch[u] = pre[u];
        u = t;
    }
    return;
}


int main() {
    n = readf< ull >(), m = readf< ull >();

    graph.resize(n, std::vector< ll >(m, 0));

    Ltop.resize(n, LLONG_MIN);
    Rtop.resize(n, 0);
    pre.resize(n, 0);
    Lmatch.resize(n, -1);
    Rmatch.resize(n, -1);
    ltag.resize(n, false);
    rtag.resize(n, false);

    for (size_t i = 0; i < m; i++) {
        ll u = readf< ll >(), //左部图
            v = readf< ll >(), //右部图
            w = readf< ll >(); //权值
        graph[u - 1][v - 1] = w;
        Ltop[u - 1] = std::max(Ltop[u - 1], w);
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