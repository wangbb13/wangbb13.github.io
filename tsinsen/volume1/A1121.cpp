#include <iostream>
#include <cstring>
using namespace std;

const int LEN = 100;

typedef struct bigInt {
  int al[100];
  int size;
} BI;

bool isH(BI a) {
  int i = LEN - a.size, j = LEN - 1;
  while (i < j) {
    if (a.al[i] != a.al[j]) {
      return false;
    }
    i++;
    j--;
  }
  return true;
}

BI add(BI a, int n) {
  int s = LEN - a.size;
  int i;
  BI ans = {{0}, 0};
  for (i = LEN - 1; i >= LEN - a.size; i--) {
    ans.al[i-1] = (ans.al[i] + a.al[i] + a.al[s]) / n;
    ans.al[i]   = (ans.al[i] + a.al[i] + a.al[s]) % n;
    s++;
  }
  if (ans.al[i] != 0) {
    ans.size = LEN - i;
  } else {
    ans.size = LEN - i - 1;
  }
  return ans;
}

int main() {
  BI num = {{0}, 0};
  int n, i = 0, j, k;
  char input[100];
  cin >> n;
  cin >> input;
  num.size = strlen(input);
  for (j = 0, k = LEN - num.size; j < num.size; j++, k++) {
    if (input[j] >= '0' && input[j] <= '9') {
      num.al[k] = (int)(input[j] - '0');
    } else {
      num.al[k] = 10 + (int)(input[j] - 'A');
    }
  }
  while (!isH(num)) {
    i++;
    if (i == 31) {
      cout << "Impossible!" << endl;
      return 0;
    }
    num = add(num, n);
  }
  cout << "STEP=" << i << endl;
  return 0;
}