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

typedef long long int ll;
typedef unsigned long long int ull;

//¿ì¶Áº¯ÊýÉùÃ÷
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

ll flag;

class segment_tree {
public:
    segment_tree(unsigned long long size);

    inline void up_data(ll left, ll right, ll p, ll lp, ll rp, ll color);

    inline ll query(ll left, ll right, ll p, ll lp, ll rp);

    inline void add_tag(ll p, ll lp, ll rp);

    inline void push_down(ll p, ll rp, ll lp);

private:
    std::vector< bool > tree;
    std::vector< bool > tag;
    ll size;
};

segment_tree::segment_tree(unsigned long long _size) {
    size = _size;
    tree.resize((size << 2) + 1, 0);
    tag.resize((size << 2) + 1, false);
    return;
}

inline void segment_tree::up_data(ll left, ll right, ll p, ll lp, ll rp, ll color) {
    if (left <= lp && rp <= right) {
        add_tag(p, lp, rp);
        return;
    }

    push_down(p, lp, rp);
    uint64_t mid = (rp + lp) >> 1;
    if (left <= mid) {
        up_data(left, right, p * 2, lp, mid, color);
    }
    if (right > mid) {
        up_data(left, right, p * 2 + 1, mid + 1, rp, color);
    }
    tree[p] = (tree[p * 2] || tree[p * 2 + 1]);
    return;
}

inline void segment_tree::add_tag(ll p, ll lp, ll rp) {
    if (tree[p] == 0) {
        if (query(lp, rp, 1, 1, size) < rp - lp + 1) {
            flag = true;
        }
        tree[p] = true;
        tag[p] = true;
    }
    return;
}

inline void segment_tree::push_down(ll p, ll lp, ll rp) {
    if (tag[p]) {
        ll mid = (lp + rp) >> 1;
        add_tag(p * 2, lp, mid);
        add_tag(p * 2 + 1, mid + 1, rp);
        tag[p] = 0;
        tree[p] = 0;
    }
    return;
}

inline ll segment_tree::query(ll left, ll right, ll p, ll lp, ll rp) {
    if (left <= lp && rp >= right) {
        return tree[p];
    }

    push_down(p, lp, rp);
    ll sum = 0, mid = (lp + rp) >> 1;
    if (left <= mid) {
        sum += query(left, right, p * 2, lp, mid);
    }
    if (right > mid) {
        sum += query(left, right, p * 2 + 1, mid + 1, rp);
    }
    return sum;
}

ll n, m, ans;

int main() {
    freopen("input.txt", "r", stdin);

    readf(&n), readf(&m);

    segment_tree tree(n);

    while (m--) {
        ll left, right;
        readf(&left), readf(&right);
        tree.up_data(left, right, 1, 1, n, m);
        if (flag) {
            ans++;
        }
        flag = false;
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