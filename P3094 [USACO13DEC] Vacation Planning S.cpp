#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

inline ll Read() {
    ll X = 0, F = 1;
    char Ch = getchar();
    while (Ch < '0' || Ch > '9') {
        if (Ch == '-') {
            F = -1;
        }
        Ch = getchar();
    }
    while (Ch >= '0' && Ch <= '9') {
        X = (X << 3) + (X << 1) + (Ch - '0');
        Ch = getchar();
    }
    return X * F;
}

ll N, M, K, Q, U, V, D, A, B;
ll Ans_1, Ans_2;
ll F[1005][1005];

void Floyd() {
    for (ll k = 1; k <= N; k++) {
        for (ll i = 1; i <= N; i++) {
            for (ll j = 1; j <= N; j++) {
                F[i][j] = min(F[i][j], F[i][k] + F[k][j]);
            }
        }

    }

}

int main() {
    // freopen ("IN.in","r",stdin);
    // freopen ("OUT.out","w",stdout);
    N = Read(), M = Read(), K = Read(), Q = Read();
    memset(F, 0x3f, sizeof(F));
    for (ll i = 1; i <= N; i++) {
        F[i][i] = 0;
    }
    for (ll i = 1; i <= M; i++) {
        U = Read(), V = Read(), D = Read();
        F[U][V] = min(F[U][V], D);
    }
    Floyd();
    while (Q--) {
        A = Read(), B = Read();
        D = 0x3f3f3f3f3f;
        for (ll i = 1; i <= K; i++) {
            D = min(D, F[A][i] + F[i][B]);
        }
        if (D != 0x3f3f3f3f3f) {
            Ans_1++;
            Ans_2 += D;
        }
    }
    cout << Ans_1 << endl << Ans_2;
    // fclose (stdin);
    // fclose (stdout);
    return 0;
}