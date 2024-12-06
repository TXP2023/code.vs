#include <vector>
#include <queue>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <stdint.h>

#define READ false

typedef long long int ll;
typedef unsigned long long int unill;

#if READ
//函数前向声明
//快读函数
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

struct point {
    double x, y;
};

std::vector< point > junctions;
std::vector< std::vector< double > > graph;
point home, dock;
double d_road, r_road;
ll n;

inline double distance(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline double djstl(ll s, ll t) {
    struct point_que {
        ll u;
        double w;
        bool operator <(const point_que other) const {
            return w > other.w;
        }
    };
    
    std::priority_queue< point_que > que;
    que.push({s, 0});
    
    std::vector< double > dits(n + 2, 1e18);
    dits[s] = 0;
    
    std::vector< bool > tag(n + 2, false);

    while (!que.empty()) {
        point_que u = que.top();
        que.pop();
        if (tag[u.u]) {
            continue;
        }
        tag[u.u] = true;
        
        if (tag[t]) {
            break;
        }

        for (size_t i = 0; i < n + 2; i++) {
            if (dits[u.u] + graph[u.u][i] < dits[i]) {
                dits[i] = dits[u.u] + graph[u.u][i];
                que.push({ ll(i), dits[i] });
            }
        }
    }

    return dits[t];
}

int main() {
    freopen("input.txt", "r", stdin);

    scanf("%lf%lf", &d_road, &r_road);
    //std::cin >> d_road >> r_road;
    readf(&n);

    junctions.resize(n);
    for (size_t i = 0; i < n; i++) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        junctions[i] = { x, y };
    }

    graph.resize(n + 2, std::vector< double >(n + 2, -1));

    ll u, v;
    while (true) {
        readf(&u), readf(&v);
        if (u == 0) {
            break;
        }
        u--, v--;
        graph[u][v] = distance(junctions[u], junctions[v]) * r_road;
        graph[v][u] = distance(junctions[u], junctions[v]) * r_road;
    }

    double x, y;
    scanf("%lf%lf", &x, &y);
    junctions.push_back({ x,y });
    scanf("%lf%lf", &x, &y);
    junctions.push_back({ x,y });

    for (size_t i = 0; i < n + 2; i++) {
        for (size_t j = 0; j < n + 2; j++) {
            if (graph[i][j] == -1) {
                graph[i][j] = distance(junctions[i], junctions[j]) * d_road;
                graph[j][i] = distance(junctions[i], junctions[j]) * d_road;
            }
        }
    }

    printf("%.4lf", djstl(n, n + 1));
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
template< typename Type >
inline Type readf(Type* p) {
    Type ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    if (p != NULL) {
        *p = Type(sgn ? -ret : ret);
    }
    return sgn ? -ret : ret;
}
#endif