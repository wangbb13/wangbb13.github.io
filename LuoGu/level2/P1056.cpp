/*
 * 题意：排座椅
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int kth(vector<int>& num, int l, int r, int k) {
    int key = num[l], temp;
    int i = l, j;
    for (j = l + 1; j < r; ++j) {
        if (num[j] > key) {
            temp = num[++i];
            num[i] = num[j];
            num[j] = temp;
        }
    }
    temp = num[i];
    num[i] = num[l];
    num[l] = temp;
    temp = i - l + 1;
    if (temp < k) {
        return kth(num, i + 1, r, k - temp);
    } else if (temp == k) {
        return key;
    } else {
        return kth(num, l, i, k);
    }
}

int main() {
    int M, N, K, L, D;
    int x, y, p, o;
    cin >> M >> N >> K >> L >> D;
    vector<int> row(M, 0);
    vector<int> col(N, 0);
    for (int i = 0; i < D; ++i) {
        cin >> x >> y >> p >> o;
        if (y == o) {
            row[min(x, p)]++;
        }
        if (x == p) {
            col[min(y, o)]++;
        }
    }
    vector<int> temp(max(M, N), 0);
    // row
    int j = 0;
    for (int i = 0; i < M; ++i) {
        if (row[i] > 0) {
            temp[j++] = row[i];
        }
    }
    int row_k = kth(temp, 0, j, K);
    j = 0;
    for (int i = 0; i < M; ++i) {
        if (row[i] >= row_k) {
            cout << i;
            j++;
            if (j < K) {
                cout << " ";
            } else {
                break;
            }
        }
    }
    cout << endl;
    // column
    j = 0;
    for (int i = 0; i < N; ++i) {
        if (col[i] > 0) {
            temp[j++] = col[i];
        }
    }
    int col_k = kth(temp, 0, j, L);
    j = 0;
    for (int i = 0; i < N; ++i) {
        if (col[i] >= col_k) {
            cout << i;
            j++;
            if (j < L) {
                cout << " ";
            } else {
                break;
            }
        }
    }
    cout << endl;
    // end
    return 0;
}