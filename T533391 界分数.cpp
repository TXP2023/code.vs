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
#define inf 1e18
#define mod 998244353

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

std::vector< uint64_t > v;
ll n, ans = 0;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

bool dfs(ll up, ll down, ll depth, ll max_depth) {
    if (depth >= max_depth) {
        return false;
    }
    if (up + 1 == down) {
        return true;
    }

    ll up1 = up + 1, down1 = down;
    ll _gcd = gcd(up1, down1);
    if (_gcd != 1) {
        up1 /= _gcd;
        down1 /= _gcd;
    }
    if (dfs(up1, down1, depth + 1, max_depth)) {
        return true;
    }
    up++, down++;
    _gcd = gcd(up, down);
    if (_gcd != 1) {
        up /= _gcd;
        down /= _gcd;
    }
    if (dfs(up, down, depth + 1, max_depth)) {
        return true;
    }
    return false;
}

ll IDDFS(ll n, ll max_depth) {
    for (size_t i = 0; i < max_depth; i++) {
        if (dfs(0, n, 0, i)) {
            return i % mod;
        }
    }
}



int main() {
    freopen("input.txt", "r", stdin);

    readf(&n);

    ans++;
    for (size_t i = 2; i <= n; i++) {
        ans += IDDFS(i, i);
        ans %= mod;
    }

    printf("%lld\n", ans);
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