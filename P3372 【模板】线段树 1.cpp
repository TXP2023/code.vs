//区间最值
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
std::vector< ll > vis; //初始数组
std::vector< ll > tag;
ll n, m;


//函数前向声明

//建树
inline void buildTree(ll p/*对应tree数组的下标*/, ll left/*左端点*/, ll right/*右端点*/);

//查询区间和
inline ll query(ll left/*目标查询左端点*/, ll right/*目标查询右端点*/, ll p/*目前正在被查询的树数组下标*/, ll lp, ll rp);

//增加tag标记
inline void addTag(ll p, ll lp, ll rp, ll d);

//转移tagz转移到子节点
inline void push_down(ll p, ll lp, ll rp);

//区间修改
inline void updata(ll left/*左区间*/, ll right/*右区间*/,
    ll p/*当前操作的线段树数组下标*/, ll lp/*当前操作的线段树的左端点*/, ll rp/*当前操作的线段树的右端点*/,
    ll change/*增加的值*/);

inline void buildTree(ll p/*对应tree数组的下标*/, ll left/*左端点*/, ll right/*右端点*/)
{
    if (left == right) {
        tree[p] = vis[left - 1];
        return;
    }
    ll mid = (left + right) >> 1;
    buildTree(p * 2, left, mid);
    buildTree(p * 2 + 1, mid + 1, right);
    tree[p] = tree[p * 2] + tree[p * 2 + 1];
    return;
}

inline ll query(ll left/*目标查询左端点*/, ll right/*目标查询右端点*/, ll p/*目前正在被查询的树数组下标*/, ll lp, ll rp)
{
    if (left <= lp && right >= rp) { //如果当前被查看的线段树区间刚好全部位于目标查询区间以内 返回当前区间和
        return tree[p];
    }
    push_down(p, lp, rp);
    ll ret = 0;
    ll mid = (rp + lp) >> 1;
    if (left <= mid) { //如果分割后的左半边完全处于目标区域内
        ret += query(left, right, p * 2, lp, mid);
    }
    if (mid < right) {
        ret += query(left, right, p * 2 + 1, mid + 1, rp);
    }
    return ret;
}

inline void addTag(ll p, ll lp, ll rp, ll d)
{
    tag[p] += d;
    tree[p] += d * (rp - lp + 1);
}

inline void push_down(ll p, ll lp, ll rp) //将tag标记转移到子节点
{
    if (tag[p]) { //如果以前存在标记 
        ll mid = (lp + rp) >> 1;
        addTag(p * 2, lp, mid, tag[p]);
        addTag(p * 2 + 1, mid + 1, rp, tag[p]);
        tag[p] = 0;
    }
}

inline void updata(ll left/*左区间*/, ll right/*右区间*/,
    ll p/*当前操作的线段树数组下标*/, ll lp/*当前操作的线段树的左端点*/, ll rp/*当前操作的线段树的右端点*/,
    ll change/*增加的值*/)
{
    if (left <= lp && right >= rp) { //目标修改区间  完全覆盖当前区间
        addTag(p, lp, rp, change); //更新tag 不继续递归
        return;
    }
    //如果不能完全覆盖
    push_down(p, lp, rp);  //向子节点转移tag标记
    ll mid = (lp + rp) >> 1;
    if (left <= mid) {
        updata(left, right, p * 2, lp, mid, change);
    }
    if (mid < right) {
        updata(left, right, p * 2 + 1, mid + 1, rp, change);
    }
    tree[p] = tree[p * 2] + tree[p * 2 + 1];
    return;
}


int main()
{
    freopen(".in", "r", stdin);

    n = readf< ll >(), m = readf< ll >();

    vis.resize(n);
    for (ll& i : vis) {
        i = readf< ll >();
    }

    tree.resize((n << 2) + 1, 0);
    tag.resize((n << 2) + 1, 0);

    buildTree(1, 1, n);

    for (size_t i = 0; i < m; i++) {
        ll q = readf< ll >(), left, right, change;
        switch (q) {
        case 1:
            left = readf< ll >(), right = readf< ll >(), change = readf< ll >();
            updata(left, right, 1, 1, n, change);
            break;
        case 2:
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