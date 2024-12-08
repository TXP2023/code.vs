#include <vector>
#include <array>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <initializer_list>

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

std::vector < std::pair < int16_t/*值*/, bool/*是否可以变换*/ > > s1, s2;
ll t, n, ans;


inline void slove() {
    readf(&n);
    s1.resize(n), s2.resize(n);
    for (size_t i = 0; i < n; i++) {
        char ch;
        std::cin >> ch;
        s1[i].first = ch - '0';
    }
    for (size_t i = 0; i < n; i++) {
        char ch;
        std::cin >> ch;
        s2[i].first = ch - '0';
    }
    for (size_t i = 0; i < n; i++) {
        char ch;
        std::cin >> ch;
        s1[i].second = (ch - '0');
    }
    for (size_t i = 0; i < n; i++) {
        char ch;
        std::cin >> ch;
        s2[i].second = (ch - '0');
    }

    std::array< std::array< ll, 2 >, 2 > cnt = {
        std::array< ll, 2 >{0, 0},
        std::array < ll, 2 >{0, 0}
    };

    ll p1 = -1, p2 = -1;
    while (p1 < n && p2 < n) {
        while (p1 + 1 < n && s1[p1 + 1].second) {
            p1++;
            ++cnt[0][s1[p1].first];
        }
        while (p2 + 1 < n && s2[p2 + 1].second) {
            p2++;
            ++cnt[1][s2[p2].first];
        }

        ans += std::min(cnt[1][0], cnt[0][0]) + std::min(cnt[1][1], cnt[0][1]);
    
        if (p1 == p2) {
            cnt = { std::array< ll, 2 >{0, 0}, std::array< ll, 2 >{0, 0} };
            if (p1 + 1 < n && s1[p1 + 1].first == s2[p1 + 1].first) {
                ans++;
            }
            ++p1, ++p2;
        }
        else {
            if (p1 > p2) {
                cnt[0][0] = std::max(ll(0), cnt[0][0] - cnt[1][0]);
                cnt[0][1] = std::max(ll(0), cnt[0][1] - cnt[1][1]);
                if (p2 + 1 < n && cnt[0][s2[p2 + 1].first] > 0) {
                    --cnt[0][s2[p2 + 1].first];
                    ++ans;
                }
                cnt[0][1] = std::min(cnt[0][1], p1 - p2 - 1);
                cnt[0][0] = std::min(cnt[0][0], p1 - p2 - 1);
                cnt[1] = std::array< ll, 2 >{ 0, 0 };
                ++p2;
            }
            else {
                cnt[1][1] = std::max(ll(0), cnt[1][1] - cnt[0][1]);
                cnt[1][0] = std::max(ll(0), cnt[1][0] - cnt[0][0]);
                if (p1 + 1 < n && cnt[1][s1[p1 + 1].first] > 0) {
                    --cnt[1][s1[p1 + 1].first];
                    ++ans;
                }
                cnt[1][0] = std::min(cnt[1][0], p2 - p1 - 1);
                cnt[1][1] = std::min(cnt[1][1], p2 - p1 - 1);
                cnt[0] = std::array< ll, 2 >{ 0, 0 };
                ++p1;
            }
        }


    }
    printf("%lld\n", ans);
    s1.clear();
    s2.clear();
    ans = 0;
    return;
}

int main() {
    freopen("input.txt", "r", stdin);

    readf(&t);
    while (t--) {
        slove();
    }


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