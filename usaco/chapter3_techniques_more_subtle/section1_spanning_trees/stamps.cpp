/*
ID: wangbb21
LANG: C++
TASK: stamps
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ofstream fout("stamps.out");
    ifstream fin("stamps.in");
    int K, N, MXV, length, ans;
    fin >> K >> N;
    vector<int> cents(N);
    MXV = 0;
    for (int i = 0; i < N; ++i) {
        fin >> cents[i];
        MXV = std::max(MXV, cents[i]);
    }
    length = MXV * K + 5;
    // N * length = 50 * 10000 * 200 = 1 yi
    vector<int> dp(length, 0);
    for (int i = 0; i < N; ++i) {
        int val = cents[i];
        dp[val] = 1;
        for (int j = 0; j < length - val; ++j) {
            if (dp[j] > 0 && dp[j] < K) {
                if (dp[j + val] == 0) {
                    dp[j + val] = dp[j] + 1;
                } else {
                    dp[j + val] = std::min(dp[j + val], dp[j] + 1);
                }
            }
        }
    }
    ans = 1;
    while (dp[ans]) {
        ans++;
    }
    fout << (ans - 1) << endl;
	fin.close();
	fout.close();
    return 0;
}
