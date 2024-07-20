#define  _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <queue>

typedef long long ll;
typedef unsigned long long unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

//std::priority_queue< std::pair< ll, ll> > que;
std::priority_queue<std::pair< ll, ll>, 
                    std::vector< std::pair< ll, ll> >, 
                    std::greater< std::pair< ll, ll> > 
                    > que;
std::vector< bool > vbool;
std::vector< ll > v;
ll n, k, ans = 0;

int main()
{
    freopen(".in", "r", stdin);

    n = readf< ll >(), k = readf< ll >();

    //输入序列，计算差分数组
    ll* old = new ll(readf< ll >());
    v.push_back(0);
    vbool.push_back(false);
    for (size_t i = 1; i < n; i++)
    {
        v.push_back(readf< ll >() - *old);
        vbool.push_back(false); //false代表可以使用
        que.push({ v[i], i});
    }
    v.push_back(0);
    vbool.push_back(false);
    delete old;

    for (size_t i = 0; i < k; i++)
    {
        while (!que.empty(), vbool[que.top().second])
        {
            que.pop();
        }
        if (que.empty())
        {
            break;
        }

        ans += que.top().first;
        v[que.top().second] = v[que.top().second - 1] + v[que.top().second + 1] - v[que.top().second];
        vbool[que.top().second - 1] = true;
        vbool[que.top().second + 1] = true;
        que.push({ v[que.top().second], que.top().second });
        que.pop();
    }

    printf("%lld\n", ans);
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
    while (!isdigit(ch))
    {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    return sgn ? -ret : ret;
#endif
}