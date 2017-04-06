#include <iostream>
#include <vector>
using namespace std;

vector<int> dp(100003, 0);
vector<int> nums(11, 0);
vector<int> cost(11, 0);
int cash;

void ZeroOnePack(int cost) {
  for (int i = cash; i >= cost; i--) {
    dp[i] = max(dp[i], dp[i - cost] + cost);
  }
}

void CompletePack(int cost) {
  for (int i = cost; i <= cash; i++) {
    dp[i] = max(dp[i], dp[i - cost] + cost);
  }
}

void MultiplePack(int cost, int amount) {
  if (cost * amount > cash) {
    CompletePack(cost);
    return;
  }
  int k = 1;
  while (k < amount) {
    ZeroOnePack(k * cost);
    amount -= k;
    k *= 2;
  }
  ZeroOnePack(amount * cost);
}

int main(int argc, char const *argv[])
{
  int i, N;
  while (cin >> cash >> N) {
    for (i = 0; i < N; i++) {
      cin >> nums[i] >> cost[i];
    }
    dp.assign(100003, 0);
    for (i = 0; i < N; i++) {
      MultiplePack(cost[i], nums[i]);
    }
    cout << dp[cash] << endl;
  }
  system("pause");
  return 0;
}