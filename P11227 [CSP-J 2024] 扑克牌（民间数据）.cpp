#include <vector>
#include <set>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <ctype.h>
#include <climits>
#include <stdint.h>
#include <string>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

inline std::string read_string();

std::set< std::string > set;
ll n;

int main()
{
    freopen(".in", "r", stdin);

    n = readf< ll >();

    for (size_t i = 0; i < n; i++){
        std::string s;
        std::getline(std::cin, s);
        set.insert(s);
    }

    printf("%lld\n", 52 - set.size());
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

inline std::string read_string() {
    std::string _s;
    std::getline(std::cin, _s);
    return _s;
}