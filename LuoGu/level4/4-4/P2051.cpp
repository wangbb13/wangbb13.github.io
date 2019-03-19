// (a + b) % c = (a % c + b % c) % c
// (a * b) % c = ((a % c) * (b % c)) % c
/*
 * name: AHOI2009 Chinese Chess
 * solution: DP
 */
#include <iostream>
using namespace std;

typedef unsigned long long ull;

const int MAXN = 100 + 1;
const int GUN = 2 + 1;
const ull MOD = 9999973;

int comm[MAXN][GUN];

inline ull add(ull a, ull b) {
    return ((a % MOD) + (b % MOD)) % MOD;
}

inline ull mul(ull a, ull b) {
    return ((a % MOD) * (b % MOD)) % MOD;
}

void init() {
    for (int i = 0; i < MAXN; ++i)
        comm[i][0] = 1;
    for (int i = 1; i < GUN; ++i) {
        for (int j = 0; j < i; ++j)
            comm[j][i] = 0;
        for (int j = i; j < MAXN; ++j)
            comm[j][i] = comm[j - 1][i] + comm[j - 1][i - 1];
    }
}

void clear(ull **p, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            p[i][j] = 0;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    if (n > m) {
        n = n + m;
        m = n - m;
        n = n - m;
    }
    if (m == 0 || n == 0) {
        cout << 0 << endl;
        return 0;
    } else if (m == 1) {
        cout << 2 << endl;
        return 0;
    }
    init();
    ull **curr = new ull*[m + 1];  // 1st dimension: 1
    ull **next = new ull*[m + 1];  // 2nd dimension: 0
    for (int i = 0; i < m + 1; ++i) {
        curr[i] = new ull[m + 1];
        next[i] = new ull[m + 1];
    }
    clear(curr, m + 1, m + 1);
    // clear(next, m + 1, m + 1);
    curr[0][m] = comm[m][0];
    curr[1][m - 1] = comm[m][1];
    curr[2][m - 2] = comm[m][2];
    int k, len = m + 1, x;
    ull ans = 0;
    for (int i = 1; i < n; ++i) {
        clear(next, len, len);
        k = std::min(i * 2, m);
        for (int j = 0; j <= k; ++j) {
            for (int p = m - j; p >= 0; --p) {
                x = curr[j][p];
                if (x) {
                    // 0
                    next[j][p] = add(next[j][p], x);
                    // 1
                    if (p > 0) {
                        next[j + 1][p - 1] = add(next[j + 1][p - 1], mul(p, x));
                    }
                    if (j > 0) {
                        next[j - 1][p] = add(next[j - 1][p], mul(j, x));
                    }
                    // 2
                    if (p > 1) {
                        next[j + 2][p - 2] = add(next[j + 2][p - 2], mul(comm[p][2], x));
                    }
                    if (j > 0 && p > 0) {
                        next[j][p - 1] = add(next[j][p - 1], mul(j * p, x));
                    }
                    if (j > 1) {
                        next[j - 2][p] = add(next[j - 2][p], mul(comm[j][2], x));
                    }
                }
            }
        }
        ull **temp = curr;
        curr = next;
        next = temp;
    }
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            ans = add(ans, curr[i][j]);
        }
    }
    cout << ans << endl;
    return 0;
}