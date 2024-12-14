#pragma once
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
#define MAX_INF 1e18

typedef long long int ll;
typedef unsigned long long int unill;

//¿ì¶Áº¯ÊýÉùÃ÷
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

std::vector< ll > v;
std::vector< std::pair< ll, ll > > pos;
std::vector< ll > ans;
ll n;

int main() {
    freopen("input.txt", "r", stdin);

    readf(&n);

    v.resize(n);
    pos.resize(n);
    for (size_t i = 0; i < n; i++) {
        readf(&v[i]);
        pos[i] = { v[i], i };
    }

    std::sort(pos.begin(), pos.end(), std::less< std::pair< ll, ll > >());
    
    while (!v.empty()) {
        ll min_p = 0;
        for (size_t i = 0; i < v.size(); i++) {
            if (v[i] < v[min_p]) {
                min_p = i;
            }
        }
        ans.push_back(v[min_p]);
        ll l = min_p - 1, r = min_p + 1;
        if (l >= 0 && r < v.size()) {
            if (v[l] > v[r]) {
                for (; l >= 0 && v[l] > v[l + 1]; l--) {
                    ans.push_back(v[l]);
                }
                v.erase(v.begin() + l, v.begin() + min_p);
            }
            else {
                for (; r < v.size() && v[r] > v[r - 1]; r++) {
                    ans.push_back(v[r]);
                }
                v.erase(v.begin() + min_p, v.begin() + r);
            }
        }
        else {
            if (v.size() == 1) {
                ans.push_back(v[0]);
                break;
            }
            else {
                if (l >= 0) {
                    for (; l >= 0 && v[l] > v[l + 1]; l--) {
                        ans.push_back(v[l]);
                    }
                    if (l == -1) {
                        l++;
                    }
                    v.erase(v.begin() + l, v.begin() + min_p + 1);
                }
                else {
                    for (; r < v.size() && v[r] > v[r - 1]; r++) {
                        ans.push_back(v[r]);
                    }
                    v.erase(v.begin() + min_p, v.begin() + r);
                }
            }
        }
    }

    for (size_t i = 0; i < n; i++) {
        printf("%lld ", ans[i]);
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