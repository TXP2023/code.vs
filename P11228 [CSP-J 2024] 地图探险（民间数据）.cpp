#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <iostream>
#include <stdint.h>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

template< typename T >
inline void inputf(T* p);

std::vector< std::vector< bool > > map;
std::vector< std::vector< bool > > tag;
unill t, n, m, k, ans = 1;

struct robot {
    ll x, y, d;
};

inline void runing(robot now) {
    for (size_t i = 0; i < k; i++) {
        robot next = now;
        switch (now.d) {
        case 0:
            next.y++;
            break;
        case 1:
            next.x++;
            break;
        case 2:
            next.y--;
            break;
        case 3:
            next.x--;
            break;
        }
        if (next.x >= 0 && next.x < n && next.y >= 0 && next.y < m && !map[next.x][next.y]) {
            ans += tag[next.x][next.y] ^ 1;
            tag[next.x][next.y] = true;
            now = next;
        }
        else {
            now.d = (now.d + 1) % 4;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    //t = readf< unill >();
    inputf(&t);

    while (t--) {
        inputf(&n), inputf(&m), inputf(&k);
        map.resize(n, std::vector< bool >(m));
        map.shrink_to_fit();
        tag.resize(n, std::vector< bool >(m, false));
        tag.shrink_to_fit();
        ans = 1;
        
        
        robot begin;
        inputf(&begin.x), inputf(&begin.y), inputf(&begin.d);

        begin.x--, begin.y--;
        tag[begin.x][begin.y] = true;


        //读入地图
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++) {
                char a;
                std::cin >> a;
                map[i][j] = (a == '.') ? false : true;
            }
        }

        runing(begin);
        printf("%lld\n", ans);

        //结束 清空数组
        map.clear();
        tag.clear();
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