/*
 * 题目：多项式输出
 */
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, exp;
    bool first = true;
    cin >> n;
    vector<int> coeff(n + 1);
    for (int i = 0; i <= n; ++i) 
        cin >> coeff[i];
    exp = n;
    for (int i = 0; i <= n; ++i, --exp) {
        if (coeff[i] > 0) {
            if (first) {
                if (coeff[i] > 1 || (i == n))
                    cout << coeff[i];
                if (exp > 1) {
                    cout << "x^" << exp;
                } else if (exp == 1) {
                    cout << "x";
                }
                first = false;
            } else {
                cout << "+";
                if (coeff[i] > 1 || (i == n))
                    cout << coeff[i];
                if (exp > 1) {
                    cout << "x^" << exp;
                } else if (exp == 1) {
                    cout << "x";
                }
            }
        } else if (coeff[i] == 0) {
            continue;
        } else {
            if (first) 
                first = false;
            if (coeff[i] < -1 || (i == n))
                cout << coeff[i];
            else
                cout << "-";
            if (exp > 1) {
                cout << "x^" << exp;
            } else if (exp == 1) {
                cout << "x";
            }
        }
    }
}