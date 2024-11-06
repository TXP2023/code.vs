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

ll t, n;

inline void def() {
    switch (n) {
    case 1:
        printf("-1\n");
        break;
    case 2:
        printf("1\n");
        break;
    case 3:
        printf("7\n");
    case 4:
        printf("4\n");
        break;
    case 5:
        printf("2\n");
        break;
    case 6:
        printf("6\n");
        break;
    default:
        switch (n % 7) {
        case 0:
            for (size_t i = 0; i < n; i += 7) {
                printf("8");
            }
            puts("\n");
            break;
        case 1:
            printf("16");
            for (size_t i = 8; i < n; i += 7) {
                printf("8");
            }
            printf("\n");
            break;
        case 2:
            printf("1");
            for (size_t i = 2; i < n; i += 7) {
                printf("8");
            }
            printf("\n");
            break;
        case 3:
            printf("7");
            for (size_t i = 3; i < n; i += 7) {
                printf("8");
            }
            printf("\n");
            break;
        case 4:
            printf("20");
            for (size_t i = 12; i < n; i += 7) {
                printf("8");
            }
            printf("\n");
            break;
        case 5:
            printf("2");
            for (size_t i = 5; i < n; i += 7) {
                printf("8");
            }
            printf("\n");
            break;
        case 6:
            printf("6");
            for (size_t i = 6; i < n; i += 7) {
                printf("8");
            }
            printf("\n");
            break;
        }
        break;
    }
    return;
}

int main() {
    freopen("input.txt", "r", stdin);

    inputf(&t);

    while (t--) {
        inputf(&n);
        def();
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