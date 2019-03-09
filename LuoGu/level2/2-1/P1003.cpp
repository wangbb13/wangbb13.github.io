/*
 * 题目：铺地毯
 * 题意：顺序地铺放N块地毯(a, b, g, k)
 * 问某一位置(x,y)最上面地地毯序号
 * 解答：……
 */
#include <iostream>
#include <vector>
using namespace std;

typedef struct rect_t {
    int x1, y1;
    int x2, y2;
} Rect;

inline bool isIn(int x, int y, Rect q) {
    return ((x >= q.x1 && x <= q.x2) && (y >= q.y1 && y <= q.y2));
}

int main() {
    int n, a, b, g, k, ans;
    cin >> n;
    vector<Rect> carpet(n);
    for (int i = 0; i < n; ++i) {
        cin >> a >> b >> g >> k;
        carpet[i] = { a, b, a + g, b + k };
    }
    cin >> a >> b;
    ans = -1;
    for (int i = 0; i < n; ++i) {
        if (isIn(a, b, carpet[i])) {
            ans = i + 1;
        }
    }
    cout << ans << endl;
    return 0;
}