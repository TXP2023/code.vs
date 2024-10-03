#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <stdint.h>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< ll > tree;
std::vector< ll > v;
ll n, t, ans = 0;

inline void buildTree(ll p, ll lp, ll rp) 
{
    if (lp == rp) {
        tree[p] = v[lp - 1];
        if (tree[p] < t) {
            ans++;
        }
        return;
    }
    ll mid = (lp + rp) >> 1;
    buildTree(p * 2, lp, mid);
    buildTree(p * 2 + 1, mid + 1, rp);
    tree[p] = tree[p * 2] + tree[p * 2 + 1];
    if (tree[p] < t) {
        ans++;
    }
    return;
}

int main() {
    //freopen(".in", "r", stdin);

    n = readf< ll >(), t = readf< ll >();

    v.resize(n);
    for (size_t i = 0; i < n; i++) {
        v[i] = readf< ll >();
    }

    tree.resize(n << 2 + 1);
    buildTree(1, 1, n);

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