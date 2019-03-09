/*
 * 题目：换页算法
 */
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int M, N;
    cin >> M >> N;
    int first = 0, last = 0, page, ans = 0;
    bool full = false;
    vector<bool> hash(1001, false);
    vector<int> list(N + 3);
    for (int i = 0; i < N; ++i) {
        cin >> page;
        if (!hash[page]) {
            list[last++] = page;
            if (full) {
                hash[list[first++]] = false;
            } else {
                full = (last - first == M);
            }
            hash[page] = true;
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}