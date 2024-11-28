#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <initializer_list>

#define READ false

typedef int64_t ll;
typedef uint64_t unill;

#if READ
//函数前向声明
//快读函数
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL) {
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

ll t, n;
//ll (*graph);
std::vector< std::vector< bool > > graph;
std::vector< std::pair< bool, bool > > peoples; //i是否为在校学生
std::vector< ll > right_match, left_match;

inline bool add_match(ll u, ll u2) /*尝试给右部图点u匹配*/ {
    if (right_match[u] == u2) {
        return false;
    }
    right_match[u] = u2;
    for (ll v : graph[u]) {
        if (left_match[v] == -1 || add_match(left_match[v], u2)) {
            left_match[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);

    readf(&t);

    while (t--) {
        readf(&n);

        ll bed_num = 0, peoples_in_school = n;// 学生数量
        peoples.resize(n, {false, false});
        for (size_t i = 0; i < n; i++) {
            peoples[i].first = readf< int >();
            bed_num += peoples[i].first;
        }

        std::vector< ll > in_sch(n, -1)/*i是第几个在校的学生*/;
        ll cnt = 0;
        for (size_t i = 0; i < n; i++) {
            if (!peoples[i].first) {
                readf< int >();
                in_sch[i] = cnt++;
                continue;
            }
            if (readf< int >() == 1) {
                peoples[i].second = 1;
                peoples_in_school--;
            }
            else {
                in_sch[i] = cnt++;
            }
        }

        graph.resize(bed_num, std::vector< bool >(peoples_in_school, false));
        if (bed_num < peoples_in_school) {
            puts("T_T");
            continue;
        }
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                ll u = (peoples[i].first) ? i : -1; //床
                bool edge = readf< int >();
                if (u != -1 && /*这个人在假期里头会在学校*/(/*是学校学生，但是跑了*/(peoples[j].first && !peoples[j].second) || /*不是学校学生*/!peoples[j].first)) {
                    graph[u][in_sch[j]] = true;
                    graph[in_sch[j]][u] = true;
                }
            }
        }

        ll ans = 0;
        right_match.resize(bed_num, -1); 
        left_match.resize(peoples_in_school, -1);
        for (size_t i = 0; i < bed_num; i++) {
            if (add_match(i, i)) {
                ans++;
            }
            else {
                break;
            }
        }
        puts((ans == peoples_in_school) ? "^_^" : "T_T");

        right_match.clear();
        left_match.clear();
        peoples.clear();
        graph.clear();
        in_sch.clear();
    }

    return 0;
}
