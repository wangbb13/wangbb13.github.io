/*
 * 题目：生活大爆炸版石头剪刀布
 */
#include <iostream>
using namespace std;

int table[5][5] = {
    {0, 0, 1, 1, 0},
    {1, 0, 0, 1, 0},
    {0, 1, 0, 0, 1},
    {0, 0, 1, 0, 1},
    {1, 1, 0, 0, 0}
};

int main() {
    int N, Na, Nb, i, j, k, sa, sb;
    cin >> N >> Na >> Nb;
    int *A = new int[Na];
    int *B = new int[Nb];
    for (i = 0; i < Na; ++i)
        cin >> A[i];
    for (i = 0; i < Nb; ++i)
        cin >> B[i];
    i = j = sa = sb = 0;
    for (k = 0; k < N; ++k) {
        sa += table[A[i]][B[j]];
        sb += table[B[j]][A[i]];
        i = (i + 1) % Na;
        j = (j + 1) % Nb;
    }
    cout << sa << " " << sb << endl;
}