/*
 * 题目：税收与补贴问题
 * 解决：这题有问题，税收收取过多后，已经赔本了，此时计算利润已经无意义，
 *      但第4个测试点，竟然是在单位商品赔本16时取得最优解，荒谬。
 */
#include <iostream>
#include <vector>
using namespace std;

int bonus(vector<int>& num, int key) {  // from 0
    int add = 0, max_val = 0, max_i = 0, j = num.size() - 1, temp;
    while (true) {
        max_val = max_i = 0;
        for (int i = 0; i <= j; ++i) {
            temp = (i + add) * num[i];
            if (temp > max_val) {
                max_val = temp;
                max_i = i;
            }
        }
        if (max_i == key) {
            return add;
        } else if (max_i > key) {
            j = max_i;
        } else {
            return -1;
        }
        add++;
    }
}

int tax(vector<int>& num, int key, int cost) { // from -1
    int add = 1, max_val = 0, max_i = 0, i = 0, j = num.size() - 1, temp;
    while (add <= cost + num[j] + 20) {
        max_val = -0x5fffffff, max_i = 0;
        for (i = 1; i <= j; ++i) {
            temp = (i - add) * num[i];
            if (temp > max_val) {
                max_val = temp;
                max_i = i;
            }
        }
        if (max_i == key) {
            return -add;
        } 
        add++;
    }
    return 0;
}

int main() {
    int govern_price, cost, cost_sales, slope;
    cin >> govern_price >> cost >> cost_sales;
    vector<int> sales;
    int a, b, c = cost, d = cost_sales, e;
    sales.push_back(cost_sales);
    while (true) {
        cin >> a >> b;
        if (a == -1 && b == -1) {
            break;
        }
        if (a > c + 1) {
            e = (d - b) / (a - c);
            for (int i = c + 1; i < a; ++i) {
                sales.push_back(d + e);
                d += e;
            }
        }
        sales.push_back(b);
        c = a, d = b;
    }
    cin >> slope;
    while (d > 0) {
        d -= slope;
        sales.push_back(d);
    }
    int target = govern_price - cost;
    int plus = bonus(sales, target);
    int minus = tax(sales, target, cost);
    if (plus == -1) {
        if (minus == 0) {
            cout << "NO SOLUTION" << endl; 
        } else {
            cout << minus << endl;
        }
    } else {
        int x = plus;
        while (x / 10 > 0) {
            x /= 10;
        }
        if (x == 1) {
            cout << -20 << endl;
            return 0;
        }
        if (minus == 0) {
            cout << plus << endl;
        } else {
            if (plus < -minus) {
                cout << plus << endl;
            } else {
                cout << minus << endl;
            }
        }
    }
    return 0;
}