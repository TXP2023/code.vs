#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <iostream>
#include <stdint.h>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

template< typename T >
inline void inputf(T* p);

std::pair< short int, short int > match[]{
    {0, 6},
    {1, 2},
    {2, 5},
    {4, 4},
    {6, 6},
    {7, 3},
    {8, 7}
};
ll n, t, ans;

inline ll fast_pow(ll base, ll index) {
    ll result = 1;   //用于存储项累乘与返回最终结果，由于要存储累乘所以要初始化为1
    while (index > 0)           //指数大于0说明指数的二进制位并没有被左移舍弃完毕
    {
        if (index & 1)          //指数的当前计算二进制位也就是最末尾的位是非零位也就是1的时候
            //例如1001的当前计算位就是1， 100*1* 星号中的1就是当前计算使用的位
            result *= base;     //累乘当前项并存储
        base *= base;           //计算下一个项，例如当前是n^2的话计算下一项n^2的值
        //n^4 = n^2 * n^2;
        index >>= 1;            //指数位右移，为下一次运算做准备
        //一次的右移将舍弃一个位例如1011(2)一次左移后变成101(2)
    }
    return result;              //返回最终结果
}

inline void minMatch(std::vector< short > v) {
    ll sum = 0;
    std::sort(v.begin(), v.end());
    if (v.front() != 0) {
        
        for (ll i = v.size() - 1; i >= 0; i--) {
            sum += v[i] * fast_pow(10, v.size() - i - 1);
        }
    }
    else {
        bool b = false;
        for (size_t i = 0; i < v.size(); i++) {
            if (v[i] != 0) {
                b = true;
                std::swap(v[0], v[i]);
                break;
            }
        }
        if (!b) {
            return;
        }
        else {
            for (ll i = v.size() - 1; i >= 0; i--) {
                sum += v[i] * fast_pow(10, v.size() - i - 1);
            }
        }
    }
    if (ans == -1) {
        ans = sum;
    }
    else {
        ans = std::min(ans, sum);
    }
    return;
}

inline void dfs(ll Stick, std::vector< short > v) {
    for (std::pair< short int, short int > i : match) {
        if (Stick - i.second == 0) {
            v.push_back(i.first);
            minMatch(v);
            v.pop_back();
        }
        else {
            if (Stick - i.second > 0) {
                v.push_back(i.first);
                dfs(Stick - i.second, v);
                v.pop_back();
            }
        }
    }
    
}

int main() {
    freopen("input.txt", "r", stdin);

    inputf(&t);
    while (t--) {
        inputf(&n);
        ans = -1;
        dfs(n, {});
        printf("%lld\n", ans);
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

template< typename T >
inline void inputf(T* p) {
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
    //return sgn ? -ret : ret;
    *p = (sgn) ? -ret : ret;
    return;
#endif
}