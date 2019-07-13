/*
ID: wangbb21
LANG: C++
TASK: inflate
 */
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
    ofstream fout("inflate.out");
    ifstream fin("inflate.in");
    int total_time, kinds;
    fin >> total_time >> kinds;
    int *points = new int[kinds];
    int *times = new int[kinds];
    int *dp = new int[total_time + 1];
    for (int i = 0; i < total_time + 1; ++i)
        dp[i] = 0;
    for (int i = 0; i < kinds; ++i) 
        fin  >> points[i] >> times[i];
    for (int i = 0; i < kinds; ++i) {
        for (int j = times[i]; j <= total_time; ++j) {
            dp[j] = max(dp[j], dp[j - times[i]] + points[i]);
        }
    }
    fout << dp[total_time] << endl;
    return 0;
}
