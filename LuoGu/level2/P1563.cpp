/*
 * 题目：玩具谜题
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int direct[2][2] = {
        {-1, 1},
        {1, -1}
    };
    int n, m, i, j, k, b;
    cin >> n >> m;
    vector<int> in_out(n);
    vector<string> job(n);
    for (i = 0; i < n; ++i) {
        cin >> in_out[i];
        cin >> job[i];
    }
    for (i = j = 0; i < m; ++i) {
        cin >> k >> b;
        b = (b % n) * direct[in_out[j]][k];
        j = (j + b + n) % n;
    }
    cout << job[j] << endl;
    return 0;
}