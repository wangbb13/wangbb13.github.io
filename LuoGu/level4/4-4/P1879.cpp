/*
 * Name : Corn Fields
 * Target : Choose some some squares that are not adjacent to plant
 * Solution : 
 */
#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long long ull;

const int MOD = 1e8;
const int MN = 12;
const int UPP = 1 << MN;
vector<int> info;
int field[MN];
int m_curr[UPP];
int m_next[UPP];
bool visit[UPP];

bool legal(int n) {
    int vc = 1;
    while (vc < n) {
        if ((vc & n) && ((vc << 1) & n)) 
            return false;
        vc <<= 1;
    }
    return true;
}

void init() {
    for (int i = 0; i < UPP; ++i) {
        m_curr[i] = m_next[i] = 0;
        if (legal(i)) {
            info.push_back(i);
        }
    }
}

inline int add(int a, int b) {
    return (a % MOD + b % MOD) % MOD;
}

inline int mul(ull a, ull b) {
    return (a % MOD * b % MOD) % MOD;
}

void my_swap(int **a, int **b) {
    int *tmp = *a;
    *a = *b;
    *b = tmp;
}

template<typename T>
void clear(T **a, int n, int val = 0) {
    for (int i = 0; i < n; ++i)
        (*a)[i] = val;
}

int main() {
    int n, m, i, j, k, p, x, y, ans = 0, xyz, len;
    int *ptr_curr = m_curr, *ptr_next = m_next;
    bool *ptr_v = visit;
    cin >> n >> m;
    xyz = 1 << m;
    for (i = 0; i < n; ++i) {
        field[i] = 0;
        x = 1;
        for (j = 0; j < m; ++j) {
            cin >> y;
            if (y)
                field[i] |= x;
            x <<= 1;
        }
    }
    init();
    len = info.size();
    // row 1
    clear<bool>(&ptr_v, xyz, 1);
    for (i = 0; i < len && info[i] < xyz; ++i) {
        j = info[i] & field[0];
        if (ptr_v[j]) {
            ptr_curr[j]++;
            ptr_v[j] = 0;
        }
    }
    // other rows
    for (i = 1; i < n; ++i) {
        clear<int>(&ptr_next, xyz);
        clear<bool>(&ptr_v, xyz, 1);
        for (j = 0; j < len && info[j] < xyz; ++j) {
            k = info[j] & field[i];
            if (ptr_v[k]) {
                for (p = 0; p < xyz; ++p) {
                    if ((ptr_curr[p] > 0) && ((k & p) == 0)) {
                        ptr_next[k] = add(ptr_next[k], ptr_curr[p]);
                    }
                }
                ptr_v[k] = 0;
            }
            
        }
        my_swap(&ptr_curr, &ptr_next);
    }
    // statistic
    for (i = 0; i < xyz; ++i)
        ans = add(ans, ptr_curr[i]);
    cout << ans << endl;
    return 0;
}
