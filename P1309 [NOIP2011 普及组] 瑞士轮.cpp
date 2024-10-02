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

struct  player {
    ll score;
    ll ability;
    ll cnt;
    bool operator <(const player other)const {
        //return score > other.score;
        if (score != other.score) {
            return score > other.score;;
        }
        else {
            return cnt < other.cnt;
        }
    }
};

std::vector< player > players;
ll n, r, q;

int main() {
    freopen(".in", "r", stdin);

    n = readf< ll >(), r = readf< ll >(), q = readf< ll >();

    players.resize(n << 1);

    for (size_t i = 0; i < n << 1; i++) {
        players[i].score = readf< ll >();
        players[i].cnt = i + 1;
    }

    for (player& i : players) {
        i.ability = readf< ll >();
    }
    
    std::sort(players.begin(), players.end());

    for (size_t i = 0; i < r; i++) {
        for (int j = 0; j < n << 1; j += 2) {
            if (players[j].ability > players[j + 1].ability) {
                players[j].score++;
            }
            else {
                players[j + 1].score++;
            }
        }
        std::sort(players.begin(), players.end());
    }
    printf("%lld\n", players[q - 1].cnt);

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