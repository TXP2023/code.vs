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
    //for (ll v : graph[u]) {
    //    if (left_match[v] == -1 || add_match(left_match[v], u2)) {
    //        left_match[v] = u;
    //        return true;
    //    }
    //}
    for (size_t i = 0; i < graph[u].size(); i++) {
        if (graph[u][i] && (left_match[i] == -1 || add_match(left_match[i], u2))) {
            left_match[i] = u;
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
        std::vector< ll > in_sch(n, -1)/*i是第几个在校的学生*/;
        std::vector< ll > get_bed(n, -1);/*i是第几个有床的人*/
        peoples.resize(n, {false, false});
        ll sch_cnt = 0, bed_cnt = 0;
        for (size_t i = 0; i < n; i++) {
            peoples[i].first = readf< int >();
            bed_num += peoples[i].first;
            if (peoples[i].first) {
                get_bed[i] = bed_cnt++;
            }
        }

        
        
        for (size_t i = 0; i < n; i++) {
            if (!peoples[i].first) {
                readf< int >();
                in_sch[i] = sch_cnt++;
                continue;
            }
            if (readf< int >() == 1) {
                peoples[i].second = 1;
                peoples_in_school--;
            }
            else {
                in_sch[i] = sch_cnt++;
            }
        }

        graph.resize(bed_num, std::vector< bool >(peoples_in_school, false));
        for (size_t i = 0; i < n; i++) {
            ll u = (peoples[i].first) ? i : -1; //床
            for (size_t j = 0; j < n; j++) {
                bool edge = readf< int >();
                if (u != -1 && /*这个人在假期里头会在学校*/(/*是学校学生，人没跑*/(peoples[j].first && !peoples[j].second) || /*不是学校学生*/!peoples[j].first)) {
                    if (get_bed[u] != -1 && in_sch[j] != -1) {
                        graph[get_bed[u]][in_sch[j]] = (i == j) ? true : edge;
                    }
                    if (get_bed[j] != -1 && in_sch[u] != -1) {
                        //graph[get_bed[j]][in_sch[u]] = (i == j) ? true : edge;
                    }
                }
            }
        }
        
        if (bed_num < peoples_in_school) {
            puts("T_T");
            right_match.clear();
            left_match.clear();
            peoples.clear();
            graph.clear();
            in_sch.clear();
            get_bed.clear();
            continue;
        }
        

        ll ans = 0;
        right_match.resize(bed_num, -1); 
        left_match.resize(peoples_in_school, -1);
        for (size_t i = 0; i < bed_num; i++) {
            if (add_match(i, i)) {
                ans++;
            }
            //else {
            //    break;
            //}
        }
        puts((ans == peoples_in_school) ? "^_^" : "T_T");

        right_match.clear();
        left_match.clear();
        peoples.clear();
        graph.clear();
        in_sch.clear();
        get_bed.clear();
    }

    return 0;
}
