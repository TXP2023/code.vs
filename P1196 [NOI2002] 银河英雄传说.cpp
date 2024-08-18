#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <stdint.h>
#include <numeric>
#include <cmath>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

#define SIZE 30000

int set[SIZE], rank[SIZE] = {0}, num[SIZE] = {1};
ll t;

inline ll findSet(ll x)
{
    if (set[x] == x) {
        return x;
    }
    else {
        ll findx = findSet(set[x]);
        rank[x] += rank[set[x]];
        return set[x] = findx;
    }
}

int main()
{
    freopen(".in", "r", stdin);

    t = readf< ll >();

    std::iota(set, set + SIZE, 0);
    std::fill(num, num + SIZE, 1);


    while (t--) {
        if (getchar() == 'M') {
            //合并舰队
            ll i = readf< ll >(), j = readf< ll >();
            ll findi = findSet(i - 1), findj = findSet(j - 1);
            rank[findi] += num[findj];
            set[findi] = findj;
            num[findj] += num[findi];
            num[findi] = 0;
        }
        else {
            //查询舰队
            ll i = readf< ll >() - 1, j = readf< ll >() - 1;
            if (findSet(i) != findSet(j)) {
                printf("-1\n");
            }
            else {
                printf("%d\n", abs(rank[i] - rank[j]) - 1);
            }
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