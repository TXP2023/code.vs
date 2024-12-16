#pragma once
#include <vector>
#include <set>
#include <stdio.h>
#include <algorithm>
#include <time.h>
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

class chtholly_tree {
public:
    chtholly_tree(ll size, ll data);

    struct tree_data {
        ll left, right;
        ll data;

        bool operator <(const tree_data other) const {
            return left < other.left;
        }
    };

    inline std::set<tree_data>::iterator split(ll p);

    inline void assign(ll left, ll right, ll data);

    inline unsigned long long int length();

    //inline unsigned long long int number();

    inline ll find(ll x);

private:

    std::set<tree_data> tree;
};

chtholly_tree::chtholly_tree(ll size, ll data) {
    tree.insert(tree_data{ 1, size, data });
    return;
}

inline std::set<chtholly_tree::tree_data>::iterator chtholly_tree::split(ll p) {
    std::set<chtholly_tree::tree_data>::iterator it = tree.lower_bound(tree_data{ p, 0, 0 });
    //printf("%d %d\n", it, tree.end());
    if (it != tree.end() && it->left == p) {
        return it;
    }
    --it;
    //printf("%d\n", (it == tree.end()));
    ll l = it->left, r = it->right, data = it->data;
    tree.erase(it);
    tree.insert(tree_data{ l, p - 1, data });
    return tree.insert(tree_data{ p, r, data }).first;
}

inline void chtholly_tree::assign(ll left, ll right, ll data) {
    std::set<tree_data>::iterator itr = split(right + 1), itl = split(left);
    tree.erase(itl, itr);
    tree.insert(tree_data{ left, right, data });
    return;
}

inline unsigned long long int chtholly_tree::length() {
    return tree.size();
}

inline ll chtholly_tree::find(ll x) {
    std::set<tree_data>::iterator it;
    //ll old_length = 0;
    std::pair< ll, std::set<tree_data>::iterator > old_length;
    old_length.first = 0;
    old_length.second = tree.end();
    for (it = tree.begin(); it != tree.end(); it++) {
        if (it->right - it->left + 1 + old_length.first >= x && it->data == 0) {
            if (old_length.first == 0) {
                return it->left;
            }
            return old_length.second->left;
        }
        if (it->data == 0) {
            old_length.first += it->right - it->left + 1;
            if (old_length.second == tree.end()) {
                old_length.second = it;
            }
        }
        if (it->data == 1) {
            old_length.first = 0;
            old_length.second = tree.end();
        }
    }
    return -1;
}


ll n, m;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    clock_t start = clock();

    readf(&n), readf(&m);

    chtholly_tree tree(n, 0);

    while (m--) {
        int operate = readf< int >();
        if (operate == 1) /*查询*/ {
            ll x = readf< int >();
            ll p = tree.find(x);
            if (p == -1) {
                printf("%lld\n", 0);
            }
            else {
                printf("%lld\n", p);
                tree.assign(p, p + x - 1, 1);
            }
        }
        else {
            ll left = readf< int >(), right = readf< int >();
            tree.assign(left, left + right - 1, 0);
        }
    }

    printf("%lld\n", (clock() - start));
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


