#pragma once
#include <vector>
#include <set>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <initializer_list>

typedef long long ll;

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

    inline unsigned long long int number();

private:

    std::set<tree_data> tree;
};

chtholly_tree::chtholly_tree(ll size, ll data) {
    tree.insert(tree_data{ 1, size + 1, data });
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

inline unsigned long long int chtholly_tree::number() {
    std::set< ll > s;
    for (std::set<tree_data>::iterator it = tree.begin(); it != tree.end(); ++it) {
        if (it->data != 0) {
            s.insert(it->data);
        }
    }

    return s.size();
}