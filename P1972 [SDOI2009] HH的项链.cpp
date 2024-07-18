#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>

typedef long long ll;

struct question
{
    ll begin;
    ll end;
    ll id;

    bool operator <(const question& other)const {
        return id < other.id;
    }
};

std::vector< ll > tree, vis; //树状数组
std::vector< ll > ans, v; //储存答案   储存序列 
std::vector< question > qs;
ll n, m;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

template< typename T >
inline T lowbit(T x)
{
    return ((x) & -(x));
}

//树状数组 -增加函数
template< typename T, typename T2>
inline void TreeAdd(T change, T2 x, std::vector< T >& _tree) //参数 增加量 下标
{
#if false
    while (x <= _tree->size() - 1)
    {
        (*_tree)[x] += change;
    }
#else
    for (ll i = x; i <= _tree.size() - 1; i += lowbit(i))
    {
        _tree[i] += change;
    }
#endif
    return;
}

//树状数组 -前缀和函数
template< typename T, typename T2 >
inline T TreeSum(T2 x, std::vector< T >& _tree)
{
    T sum = 0;
    for (T2 i = x; i >= i; i -= lowbit(i))
    {
        sum += _tree[i];
    }
    return sum;
}

//  TODO 
int main()
{
    n = readf< ll >();
    v.resize(n);
    for (size_t i = 0; i < n; i++)
    {
        v[i] = readf< ll >();
    }

    m = readf< ll >();
    qs.resize(m);
    for (ll i = 0; i < m; i++)
    {
        qs[i].begin = readf< ll >() - 1, qs[i].end = readf< ll >() - 1;
        qs[i].id = i;
    }
    std::sort(qs.begin(), qs.end());

    ll pow = 0;
    ans.resize(m);
    vis.resize(n, 0);
    for (ll i = 0; i < m; i++)
    {
        for (ll j = pow; j <= qs[i].begin; j++)
        {
            if (vis[v[j]])
            {
                TreeAdd(vis[v[j]], -1, tree);
            }
            TreeAdd(j, 1, tree);
            vis[v[j]] = j;
        }
        pow = qs[i].end + 1;
        ans[qs[i].id] = TreeSum(qs[i].end+1, tree) - TreeSum(qs[i].begin, tree);
    }

    for (size_t i = 0; i < m; i++)
    {
        printf("%lld\n", ans[i]);
    }
    return 0;
}

//快读函数
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
    while (!isdigit(ch))
    {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    return sgn ? -ret : ret;
#endif
}