#include <vector>
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <ctype.h>
#include <climits>
#include <stdint.h>
#include <stack>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< std::vector< ll > > graph;
std::vector< ll > vmin; //vmin[i] = min(v[i~n])
std::vector< ll > v; 
std::vector< int > colors; //colors[i]即为点i是否会和其他点存在冲突，即无法处于同一个栈内
std::stack< int > stack[2];
ll n;

//函数前向声明
inline void stack_push(ll value/*值*/, ll id/*所属栈*/);

inline bool stack_pop(ll id);

inline void stack_push(ll value/*值*/, ll id/*所属栈*/) {
    if (id == 1) {
        while (stack_pop(0));
    }
    while (!stack[id].empty() && stack[id].top() < value) {
        if (!stack_pop(id)) {
            stack_pop(id ^ 1);
        }
    }
    if (id == 1) {
        while (stack_pop(0));
    }
    printf("%c ", id ? 'c' : 'a');
    return;
}

inline bool stack_pop(ll id) {

}

int main() {
    freopen(".in", "r", stdin);

    n = readf< ll >();

    v.resize(n);
    for (size_t i = 0; i < n; i++) {
        v[i] = readf< ll >();
    }

    //计算vmin 
    vmin[n - 1] = v.back();
    for (int64_t i = n - 2; i >= 0; i--) {
        vmin[i] = std::min(v[i], vmin[i + 1]);
    }

    //构建二分图
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            if (vmin[j + 1] < v[i] && v[i] < v[j]) {
                graph[i].push_back(j);
                graph[j].push_back(i);
                colors[i] = -1, colors[j] = -1; /*标记，这两个点二分图染色*/
            }
        }
    }

    for (size_t i = 0; i < n; i++) {
        if (!~colors[i]) /*如果当前点已经被染色了*/ {
            std::queue< ll > que; 
            que.push(i);
            colors[i] = 0;
            while (!que.empty()) {
                ll u = que.front(); 
                que.pop();
                for (ll v : graph[u]) {
                    if (~colors[v] && colors[v] != (colors[u] ^ 1)) {
                        printf("0\n");
                        exit(0);
                    }
                    if (!~colors[v]) {
                        que.push(v);
                    }
                    colors[v] = colors[u] ^ 1;
                }
            }
        }
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