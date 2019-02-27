#include <iostream>
using namespace std;

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

static int speedup = []() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    return 0;
}();

int lowbit(int x) {
    return (x & (-x));
}

void update(int *number, int *tree, int *flag, int N, int size) {
    int p, d, e;
    for (int j = 0; j < size; ++j) {
        e = number[j];
        // tree[e] += 1;
        if (e == 0) {
            continue;
        }
        p = e;
        while (p <= N) {
            tree[p] = flag[p];
            d = lowbit(p);
            for (int i = 1; i < d; i <<= 1) {
                tree[p] += tree[p - i];
            }
            p += d;
            // tree[p] += 1;
            // d = lowbit(p);
        }
    }
}

int query(int *flag, int *tree, int l, int r) {
    int ans = 0;
    while (l <= r) {
        ans += flag[r];
        for (--r; r - lowbit(r) >= l; r -= lowbit(r)) {
            ans += tree[r];
        }
    }
    return ans;
}

void set_zero(int *array, int n) {
    for (int i = 0; i < n; ++ i)
        array[i] = 0;
}

int main() {
    int n, m, l, r, max_val = 0;
    cin >> n >> m;
    int *number = new int[n + 1];
    for (int i = 0; i < n; ++i) {
        cin >> number[i];
        max_val = max(max_val, number[i]);
    }
    int *tree = new int[max_val + 1];
    int *flag = new int[max_val + 1];
    set_zero(tree, max_val + 1);
    set_zero(flag, max_val + 1);
    for (int i = 0; i < n; ++i) {
        flag[number[i]] = 1;
    }
    update(number, tree, flag, max_val, n);
    for (int i = 0; i < m; ++i) {
        cin >> l >> r;
        if (l > max_val) 
            cout << 0 << endl;
        else {
            r = min(r, max_val);
            if (l == 0) {
                l = 1;
                cout << (query(flag, tree, l, r) + flag[0]) << endl;
            } else {
                cout << query(flag, tree, l, r) << endl;
            }
        }
    }
    return 0;
}