#if  true

#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <list>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::list< ll > list;
ll n, k, ans = 0;

inline std::list< ll >::iterator list_min(std::list< ll > &_l) {
    std::list< ll >::iterator it = _l.begin();
    for (std::list< ll >::iterator i = _l.begin(); i != _l.end(); i++) {
        if (*i < *it) {
            it = i;
        }
    }
    return it;
}



int main() {
    freopen("input.txt", "r", stdin);

    n = readf< ll >(), k = readf< ll >();
    ll* old = new ll;
    *old = readf< ll >();
    for (size_t i = 0; i < n - 1; i++) {
        ll now = readf< ll >();
        //roud.push_back(now - *old);
        list.push_back(now - *old);
        *old = now;
    }
    delete old;

    for (size_t i = 0; i < k; i++) {
        std::list< ll >::iterator min_it = list_min(list);
        ans += *min_it;
        *min_it = 0 - *min_it;
        if (min_it != list.begin()) {
            std::list< ll >::iterator next = min_it;
            next--;
            *min_it += *next;
            list.erase(next);
        }
        if (min_it != list.end()) {
            std::list< ll >::iterator next = min_it;
            next++;
            *min_it += *next;
            list.erase(next);
        }
    }

    printf("%lld\n", ans);
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

#else


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

std::vector< ll > roud;
ll n, k, ans;

inline ll vecor_min(std::vector< ll > _v) {
    ll min = LLONG_MAX;
    ll p = -1;
    for (size_t i = 0; i < _v.size(); i++) {
        if (_v[i] < min) {
            p = i;
            min = _v[i];
        }
    }
    return p;
}

int main() {
    freopen("input.txt", "r", stdin);

    n = readf< ll >(), k = readf< ll >();

    ll* old = new ll;
    *old = readf< ll >();
    
    for (size_t i = 0; i < n - 1; i++) {
        ll now = readf< ll >();
        roud.push_back(now - *old);
        *old = now;
    }
    delete old;

    for (size_t i = 0; i < k; i++) {
        ll min_p = vecor_min(roud);
        ans += roud[min_p];
        roud[min_p] = 0 - roud[min_p];
        if (min_p > 0) {
            roud[min_p] += roud[min_p - 1];
            roud.erase(roud.begin() + min_p - 1);
            min_p--;
        }
        if (min_p < roud.size() - 1) {
            roud[min_p] += roud[min_p + 1];
            roud.erase(roud.begin() + min_p + 1);
        }
    }

    printf("%lld\n", ans);

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

#endif 