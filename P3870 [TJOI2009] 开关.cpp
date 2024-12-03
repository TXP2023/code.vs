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

typedef long long int ll;
typedef uint64_t unill;

#if READ
//函数前向声明
//快读函数
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

class Segment_Tree {
public:
    Segment_Tree(ll size) {
        tag.resize(1 + (size << 2), false);
        tree.resize(1 + (size << 2));
    }

    inline void up_data(ll left, ll right, ll p, ll lp, ll rp);

    inline ll query(ll left, ll right, ll p, ll rp, ll lp);
private:

    std::vector< bool > tag;
    std::vector< std::array<ll, 2> > tree;

    inline void build_tree(ll p, ll lp, ll rp);

    inline void add_tag(ll p, ll lp, ll rp);

    inline void push_down(ll p, ll lp, ll rp);
};

inline void Segment_Tree::build_tree(ll p, ll lp, ll rp) {
    if (lp == rp) {
        tree[p] = std::array<ll, 2>({ 1, 0 });
    }
}

inline void Segment_Tree::up_data(ll left, ll right, ll p, ll lp, ll rp) {
    if (left <= lp && rp <= right) {
        Segment_Tree::add_tag(p, lp, rp);
        return;
    }

    push_down(p, lp, rp);
    ll mid = (lp + rp) >> 1;

    if (left <= mid) {
        Segment_Tree::up_data(left, right, p * 2, lp, mid);
    }
    if (right > mid) {
        Segment_Tree::up_data(left, right, p * 2 + 1, mid + 1, rp);
    }

    tree[p][0] = tree[p * 2][0] + tree[p * 2 + 1][0];
    return;
}

inline void Segment_Tree::add_tag(ll p, ll lp, ll rp) {
    tag[p] = true;
    //tree[p] = (rp - lp + 1) - tree[p];
    std::swap(tree[p][0], tree[p][1]);
    return;
}

inline void Segment_Tree::push_down(ll p, ll lp, ll rp) {
    if (tag[p]) {
        tag[p] = false;
        ll mid = (lp + rp) >> 1;
        add_tag(p * 2, lp, mid);
        add_tag(p * 2 + 1, mid + 1, rp);
        return;
    }
}

inline ll Segment_Tree::query(ll left, ll right, ll p, ll lp, ll rp) {
    if (left <= lp && rp <= right) {
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

ll n, m;

int main() {
    freopen("input.txt", "r", stdin);

    readf(&n), readf(&m);

    Segment_Tree tree(n);

    for (size_t i = 0; i < m; i++) {
        ll begin, end;
        switch (readf< int >()) {
        case 0: /*修改操作*/
            readf(&begin), readf(&end);
            tree.up_data(begin, end, 1, 1, n);
            break;
        case 1: /*查询*/
            readf(&begin), readf(&end);
            printf("%lld\n", tree.query(begin, end, 1, 1, n));
            break;
        }
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