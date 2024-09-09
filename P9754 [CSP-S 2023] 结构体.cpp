#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <stdint.h>
#include <string>
#include <iostream>
#include <map>


typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

struct data {
    std::string name;
    std::map< std::string, int > typ;
    int max = 0;
};

std::map< std::string, data> _map;
std::map< std::string, int > typenames{
    {"byte", 1},
    {"short", 2},
    {"int", 4},
    {"long", 8}
};
std::vector< data > v;
int n, cntp = 0;

inline int dfs_find(std::string name, std::string s) {
    
}

inline int find(std::string s) {
    std::string name;
    while (s[0] != '.') {
        name += s[0];
        s.erase(0, 1);
    }
    s.erase(0, 1);
    
    
}



int main() {
    freopen(".in", "r", stdin);

    n = readf< ll >();

    for (size_t i = 0; i < n; i++) {
        char ch;
        std::string str;
        std::string name, typ;
        scanf("\r\n%c", &ch);
        switch (ch) {
        case '1':
            int k = readf< ll >();
            std::cin >> str;
            for (size_t i = 0; i < k; i++) {
                std::cin >> typ >> name;
                _map[str].typ[name] = typenames[typ];
                _map[str].max = std::max(_map[str].max, typenames[typ]);
            }
            break;
        case 2:
            std::cin >> typ >> name;
            v.push_back({name, _map[typ].typ, _map[typ].max});
            break;
        case 3:
            std::cin >> str;

            break;
        }


    }

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