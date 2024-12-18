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

//快读函数声明
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

class segment_tree {
public:
    segment_tree(ll size);
    
    inline ll query(ll x, ll p = 1);

private:
    struct tree_node {
        ll max_length;
        ll left_length, right_length;
        int lp, rp;
    };

    std::vector< tree_node > tree;

    inline void build_tree(ll p, ll lp, ll rp);
};

segment_tree::segment_tree(ll size) {
    tree.resize((size << 2) + 1);
    build_tree(1, 1, size);
    return;
}

inline ll segment_tree::query(ll x, ll p) {
    if (tree[p].max_length < x) {
        return -1;
    }

    if (tree[p].left_length >= x) {
        return tree[p].lp;
    }

    //五种可能
    if (tree[p].left_length >= x) /*这个点的左端点连续x个*/ {
        return tree[p].lp;
    }
    //在左子节点的内部
    if (tree[p * 2].max_length >= x) {
        return query(x, p * 2);
    }
    /*在左右节点中间*/
    if (tree[p * 2].right_length + tree[p * 2 + 1].left_length >= x) {
        return tree[p * 2].rp - tree[p * 2].right_length + 1;
    }
    //在右子节点内部有
    if (tree[p * 2 + 1].max_length >= x) {
        return query(x, p * 2 + 1);
    }
    //在当前节点的最左边
    if (tree[p].right_length >= x) {
        return tree[p].rp - tree[p].right_length + 1;
    }
}

inline void segment_tree::build_tree(ll p, ll lp, ll rp) {
    tree[p].lp = lp, tree[p].rp = rp;
    
    if (lp == rp) {
        tree[p].max_length = 1;
        tree[p].left_length = 1;
        tree[p].right_length = 1;
        return;
    }

    ll mid = (lp + rp) >> 1;
    build_tree(p * 2, lp, mid);
    build_tree(p * 2 + 1, mid, rp);
    tree[p].max_length = rp - lp + 1;
    tree[p].right_length = rp - lp + 1;
    tree[p].left_length = rp - lp + 1;
    return;
}

ll n, m;

int main() {
    freopen("input.txt", "r", stdin);

    readf(&n), readf(&m);

    segment_tree tree(n);
    while (m--) {

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

