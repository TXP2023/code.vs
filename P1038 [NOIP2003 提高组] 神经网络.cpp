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

struct neuron {
    ll state; //神经元状态
    ll u; //神经元阈值
};

std::vector< neuron > neurons;
ll n, p;

int main() {
    freopen(".in", "r", stdin);

    n = readf< ll >(), p = readf< ll >();

    neurons.resize(n);
    for (neuron &i : neurons) {
        i = neuron{ readf< ll >(), readf< ll >() };
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