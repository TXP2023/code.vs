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

struct  point {
    float x, y;
};

std::vector< point > junctions;
std::vector< std::vector< float > > graph;
point home, dock;
float d_road, r_road;
ll n;

inline float distance(point a, point b) {
    return fabs(sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

inline float djstl(ll s, ll t) {
    struct point_que {
        ll u;
        float w;
        bool operator <(const point_que other) const {
            return w > other.w;
        }
    };
    
    std::priority_queue< point_que > que;
    que.push({s, 0});
    
    std::vector< float > dits(n + 2, std::numeric_limits< float >::max());
    dits[s] = 0;
    
    std::vector< bool > tag(n + 2, false);

    
    
    
    while (!que.empty()) {
        point_que u = que.top();
        que.pop();
        if (tag[t]) {
            break;
        }
        if (tag[u.u]) {
            continue;
        }
        tag[u.u] = true;
        
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

    scanf("%f%f", &d_road, &r_road);
    //std::cin >> d_road >> r_road;
    readf(&n);

    junctions.resize(n);
    for (size_t i = 0; i < n; i++) {
        float x, y;
        scanf("%f%f", &x, &y);
        junctions[i] = { x, y };
    }

    graph.resize(n + 2, std::vector< float >(n + 2, -1));

    /*std::vector< float > input;
    float* p = new float;
    while (std::cin >> *p) {
        input.push_back(*p);
    }*/
    ll u, v;
    while (true) {
        readf(&u), readf(&v);
        if (u == 0) {
            break;
        }
        graph[--u][--v] = distance(junctions[u], junctions[v]) * r_road;
        graph[v][u] = distance(junctions[u], junctions[v]) * r_road;
    }

    float x, y;
    scanf("%f%f", &x, &y);
    junctions.push_back({ x,y });
    scanf("%f%f", &x, &y);
    junctions.push_back({ x,y });

    for (size_t i = 0; i < n + 2; i++) {
        for (size_t j = 0; j < n + 2; j++) {
            if (graph[i][j] == -1) {
                graph[i][j] = distance(junctions[i], junctions[j]) * d_road;
                graph[j][i] = distance(junctions[i], junctions[j]) * d_road;
            }
        }
    }

    printf("%.4f", djstl(n, n + 1));
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