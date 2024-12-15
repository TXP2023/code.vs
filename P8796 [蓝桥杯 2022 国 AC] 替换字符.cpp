#pragma once
#include <vector>
#include <string>
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
#define MAX_INF 1e18
#define REPLACE_INIT {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}
#define WORD_NUM 26

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

std::string s;

class sgnment_tree {
public:
    sgnment_tree(std::string s);

    int _length;

    inline void up_data(ll left, ll right, int x, int y, ll p = 1, ll lp = 1, ll rp = -1);

    inline void show(ll p = 1, ll lp = 1, ll rp = -1);
private:

    struct tree_node {
        std::array< short, WORD_NUM > replace = REPLACE_INIT;
        bool tag = false;
    };

    std::vector< tree_node > tree;

    std::string str;

    inline void push_down(ll p);

    inline void add_tag(ll p, int x, int y);
};

sgnment_tree::sgnment_tree(std::string s) {
    _length = s.length();
    str = s;
    tree.resize((s.length() << 2) + 1);
    return;
}

inline void sgnment_tree::up_data(ll left, ll right, int x, int y, ll p, ll lp, ll rp) {
    if (rp == -1) {
        rp = _length;
    }

    if (left <= lp && right >= rp) {
        add_tag(p, x, y);
        return;
    }

    push_down(p);
    ll mid = (lp + rp) >> 1;
    if (left <= mid) {
        up_data(left, right, x, y, p * 2, lp, mid);
    }
    if (right > mid) {
        up_data(left, right, x, y, p * 2 + 1, mid + 1, rp);
    }
    return;
}

inline void sgnment_tree::show(ll p, ll lp, ll rp) {
    if (rp == -1) {
        rp = _length;
    }
    
    if (lp == rp) {
        printf("%c", tree[p].replace[str[lp - 1] - 'a'] + 'a');
        return;
    }

    push_down(p);
    ll mid = (lp + rp) >> 1;
    show(p * 2, lp, mid);
    show(p * 2 + 1, mid + 1, rp);
    return;
}

inline void sgnment_tree::push_down(ll p) /*这个代逻辑有问题*/ {
    if (tree[p].tag) {
        tree[p * 2].tag = true;
        for (size_t i = 0; i < WORD_NUM; i++) {
            tree[p * 2].replace[i] = tree[p].replace[tree[p * 2].replace[i]];
            tree[p * 2 + 1].replace[i] = tree[p].replace[tree[p * 2 + 1].replace[i]];
        }
        //tree[p * 2].replace = tree[p].replace; //不能直接赋值
        //for (size_t i = 0; i < WORD_NUM; i++) {
        //    if (tree[p].replace[i] != i) {
        //        for (size_t j = 0; j < WORD_NUM; j++) {
        //            if (tree[p * 2].replace[j] == i) {
        //                tree[p * 2].replace[j] = tree[p].replace[i];
        //            }
        //        }
        //    }
        //}
        tree[p * 2 + 1].tag = true;
        //tree[p * 2 + 1].replace = tree[p].replace;
        //for (size_t i = 0; i < WORD_NUM; i++) {
        //    if (tree[p].replace[i] != i) {
        //        for (size_t j = 0; j < WORD_NUM; j++) {
        //            if (tree[p * 2 + 1].replace[j] == i) {
        //                tree[p * 2 + 1].replace[j] = tree[p].replace[i];
        //            }
        //            if (tree[p * 2].replace[j] == i) {
        //                tree[p * 2].replace[j] = tree[p].replace[i];
        //            }
        //        }
        //    }
        //}
        tree[p].tag = false;
        tree[p].replace = REPLACE_INIT;
    }
    return;
}

inline void sgnment_tree::add_tag(ll p, int x, int y) {
    for (size_t i = 0; i < WORD_NUM; i++) {
        if (tree[p].replace[i] == x) {
            tree[p].replace[i] = y;
        }
    }
    tree[p].tag = true;
    return;
}

ll m;

int main() {
    freopen("input.txt", "r", stdin);

    std::cin >> s;
    
    sgnment_tree tree(s);

    readf(&m);
    while (m--) {
        ll left = readf< int >(), right = readf< int >();
        char x, y;
        std::cin >> x >> y;
        x -= 'a', y -= 'a';
        tree.up_data(left, right, x, y);
        if (m == 1) {
            //tree.show();
        }
        //puts("\n");
    }

    tree.show();
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


