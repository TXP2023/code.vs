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

#define size 6

ll vis[size], tree[size << 2];
std::pair< ll, ll> tag[size << 2];
ll n, q;

inline void buildTree(ll p, ll lp, ll rp)
{
    if (lp == rp) {
        tree[p] = vis[lp - 1];
    }
    ll mid = (lp + rp) >> 1;
    buildTree(p * 2, lp, mid);
    buildTree(p * 2 + 1, mid + 1, rp);
    tree[p] = std::max(tree[p * 2], tree[p * 2 + 1]);
    return;
}

inline void addTag(ll p, ll change) //将区间统一增加为同一个数
{
    tag[p].first = change;
    tree[p] += change;
}

inline void reviseTag(ll p, ll change)
{
    tag[p].second = change;
    tree[p] = change;
}

inline void push_down_first(ll p, ll lp, ll rp)
{
    if (tag[p].first) {
        ll mid = (lp + rp) >> 1;
        addTag(p * 2, tag[p].first);
        addTag(p * 2 + 1, tag[p].first);
        tag[p].first = 0;
    }
    return;
}

inline void push_down_second(ll p, ll lp, ll rp)
{
    if (tag[p].second) {
        ll mid = (lp + rp) >> 1;
        reviseTag(p * 2, tag[p].second);
        reviseTag(p * 2 + 1, tag[p].second);
        tag[p].second = 0;
    }
    return;
}

inline void updata_revise(ll left/*左区间*/, ll right/*右区间*/,
    ll p/*当前操作的线段树数组下标*/, ll lp/*当前操作的线段树的左端点*/, ll rp/*当前操作的线段树的右端点*/,
    ll change/*修改的值*/)
{
    if (left <= lp && right >= rp) { //目标修改区间  完全覆盖当前区间
        reviseTag(p, change); //更新tag 不继续递归
        return;
    }
    //如果不能完全覆盖
    push_down_second(p, rp, lp);  //向子节点转移tag标记
    ll mid = (lp + rp) >> 1;
    if (left <= mid) {
        updata_revise(left, right, p * 2, lp, mid, change);
    }
    if (mid < right) {
        updata_revise(left, right, p * 2 + 1, mid + 1, rp, change);
    }
    tree[p] = std::max(tree[p * 2], tree[p * 2 + 1]);
    return;
}

inline void updata_add(ll left/*左区间*/, ll right/*右区间*/,
    ll p/*当前操作的线段树数组下标*/, ll lp/*当前操作的线段树的左端点*/, ll rp/*当前操作的线段树的右端点*/,
    ll change/*修改的值*/)
{
    if (left <= lp && right >= rp) { //目标修改区间  完全覆盖当前区间
        addTag(p, change); //更新tag 不继续递归
        return;
    }
    //如果不能完全覆盖
    push_down_first(p, rp, lp);  //向子节点转移tag标记
    ll mid = (lp + rp) >> 1;
    if (left <= mid) {
        updata_add(left, right, p * 2, lp, mid, change);
    }
    if (mid < right) {
        updata_add(left, right, p * 2 + 1, mid + 1, rp, change);
    }
    tree[p] = std::max(tree[p * 2], tree[p * 2 + 1]);
    return;
}

inline ll query(ll left/*目标查询左端点*/, ll right/*目标查询右端点*/, ll p/*目前正在被查询的树数组下标*/, ll lp, ll rp)
{
    if (left <= lp && right >= rp) { //如果当前被查看的线段树区间刚好全部位于目标查询区间以内 返回当前区间最值
        return tree[p];
    }
    push_down_first(p, lp, rp);
    push_down_second(p, lp, rp);
    ll ret = 0;
    ll mid = (rp + lp) >> 1;
    if (left <= lp) { //如果分割后的左半边完全处于目标区域内
        ret += query(left, right, p * 2, lp, mid);
    }
    if (mid < right) {
        ret += query(left, right, p * 2 + 1, mid + 1, rp);
    }
    return ret;
}

int main()
{
    freopen(".in", "r", stdin);

    n = readf< ll >(), q = readf< ll >();

    for (size_t i = 0; i < n; i++) {
        vis[i] = readf< ll >();
    }

    buildTree(1, 1, n);

    while (q--) {
        switch (readf< ll >()) {
            case 1:
                //修改为x
                ll left = readf< ll >(), right = readf< ll >(), x = readf< ll >();
                updata_revise(left, right, 1, 1, n, x);
                break;
            case 2:
                //增加x
                left = readf< ll >(), right = readf< ll >(), x = readf< ll >();
                updata_add(left, right, 1, 1, n, x);
                break;
            case 3:
                left = readf< ll >(), right = readf< ll >();
                printf("%lld\n", query(left, right, 1, 1, n));
                break;
        }
    }

    return 0;
}

template< typename T >
inline T readf()
{
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