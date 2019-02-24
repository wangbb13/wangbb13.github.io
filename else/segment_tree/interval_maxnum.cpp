/*
 * 题目描述：求N个数中任一区间[i, j]中的最大值
 * 数据规模：N <= 200,000；区间数M <= 10,000
 * 输入格式：N
 *           a1, a2, ... , an
 *           M
 *           l1, r1
 *           ...
 *           lm, rm
 * 解决方案：树状数组
 */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>
using namespace std;

const int MAXN = 200005;

int H[MAXN];
int A[MAXN];
int N, M;

int lowbit(int x) {
  return (x & (-x));
}

void update(int p) {
  int i, j;
  while (p <= N) {
    H[p] = A[p];
    j = lowbit(p);
    for (i = 1; i < j; i <<= 1) {
      H[p] = max(H[p], H[p - i]);
    }
    p += j;
  }
}

int query(int l, int r) {
  int ans = A[r];
  while (r >= l) {
    ans = max(ans, A[r]);
    r--;
    for (; r - lowbit(r) >= l; r -= lowbit(r)) {
      ans = max(ans, H[r]);
    }
  }
  return ans;
}

int main() {
  int i, j, k;
  cin >> N;
  for (i = 1; i <= N; i++) {
    cin >> A[i];
    update(i);
  }
  cin >> M;
  for (k = 0; k < M; k++) {
    cin >> i >> j;
    cout << query(i, j) << endl;
  }
  return 0;
}

// int func() {
// 	std::default_random_engine generator;
// 	std::uniform_int_distribution<int> distribution(0, 100);
// 	auto dice = std::bind(distribution, generator);
// 	cout << dice() << endl;
//   cout << "**/" << endl;
// }
