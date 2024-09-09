#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <math.h>
#include <stdint.h>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< ll > begin, end;
ll n, m, ans = 0;

int main() {
    //freopen(".in", "r", stdin);

    n = readf< ll >(), m = readf< ll >(); //长度为m的栅栏上，有n头牛需要坐车前往别的地方

    begin.resize(n);
    end.resize(n);

    for (size_t i = 0; i < n; i++) {
        begin[i] = readf< ll >();
        end[i] = readf< ll >();
        ans += std::abs(begin[i] - end[i]);
    }
    begin.push_back(m);
    end.push_back(0);

    std::sort(begin.begin(), begin.end());
    std::sort(end.begin(), end.end());

    for (size_t i = 0; i <= n; i++) {
        ans += std::abs(begin[i] - end[i]);
    }

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