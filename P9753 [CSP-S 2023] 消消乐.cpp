#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <string>
#include <stdint.h>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< std::vector< bool > > dp;
std::vector< char > str;
ll n, ans = 0;

int main() {
    freopen(".in", "r", stdin);

    n = readf< ll >();
    
    scanf("\r\n");
    str.resize(n);
    for (char &ch : str) {
        scanf("%c", &ch);
    }

    dp.resize(n, std::vector< bool >(n, false));
    for (size_t i = 0; i < n - 1; i++) {
        if (str[i] == str[i + 1]) {
            dp[i][i + 1] = true;
            ans++;
        }
    }

    for (size_t len = 3; len < n; len++) {
        for (size_t i = 0; i + len < n; i++) {
            ll j = i + len;
            if (str[i] == str[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                ans++;
                continue;
            }
            for (size_t k = i + 1; k < j; k += 2) {
                if (dp[i][k] && dp[k + 1][j]) {
                    dp[i][j] = true;
                    ans++;
                    break;
                }
            }
        }
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