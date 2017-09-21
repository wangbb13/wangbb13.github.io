#include <iostream>
using namespace std;

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

double dp[51][51];
double dpp[51][51];
int N;
int operands[51];
int operators[51];

int MinValOfExpr(int l, int r);
int MaxValOfExpr(int l, int r);

void ClearDP() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      dp[i][j] = INT_MIN;
      dpp[i][j] = INT_MAX;
    }
  }
}

int CalculateExpr(int n1, int n2, int opt) {
  if (opt == 0) {
    return (n1 + n2);
  }
  return (n1 * n2);
}

int MinValOfExpr(int l, int r) {
  if (dpp[l][r] != INT_MAX) {
    return dpp[l][r];
  }
  if (l == r) {
    dpp[l][r] = operands[l];
  } else if ((l + 1) == r) {
    dpp[l][r] = CalculateExpr(operands[l], operands[r], operators[l]);
  } else {
    double minVal = INT_MAX;
    double lev[2], rev[2];
    for (int i = l; i < r; i++) {
      lev[0] = MaxValOfExpr(l, i);
      lev[1] = MinValOfExpr(l, i);
      rev[0] = MaxValOfExpr(i+1, r);
      rev[1] = MinValOfExpr(i+1, r);
      for (int k = 0; k < 2; k++) {
        for (int l = 0; l < 2; l++) {
          minVal = min(minVal, CalculateExpr(lev[k], rev[l], operators[i]));
        }
      }
    }
    dpp[l][r] = minVal;
  }
  return dpp[l][r];
}

int MaxValOfExpr(int l, int r) {
  if (dp[l][r] != INT_MIN) {
    return dp[l][r];
  }
  if (l == r) {
    dp[l][r] = operands[l];
  } else if ((l + 1) == r) {
    dp[l][r] = CalculateExpr(operands[l], operands[r], operators[l]);
  } else {
    double maxVal = INT_MIN;
    double lev[2], rev[2];
    for (int i = l; i < r; i++) {
      lev[0] = MaxValOfExpr(l, i);
      lev[1] = MinValOfExpr(l, i);
      rev[0] = MaxValOfExpr(i+1, r);
      rev[1] = MinValOfExpr(i+1, r);
      for (int k = 0; k < 2; k++) {
        for (int l = 0; l < 2; l++) {
          maxVal = max(maxVal, CalculateExpr(lev[k], rev[l], operators[i]));
        }
      }
    }
    dp[l][r] = maxVal;
  }
  return dp[l][r];
}


int main(int argc, char const *argv[])
{
  char ch;
  int numbers[51];
  int labels[51];
  double record[51];
  double maxVal = INT_MIN;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> ch;
    if (ch == 't') {
      labels[i] = 0;
    } else {
      labels[i] = 1;
    }
    cin >> numbers[i];
  }
  for (int i = 0; i < N; i++) {
    ClearDP();
    for (int j = 0; j < N; j++) {
      int index = (i + j) % N;
      operands[j] = numbers[index];
      if (j < N - 1) {
        operators[j] = labels[((index+1)%N)];
      }
    }
    record[i] = MaxValOfExpr(0, N-1);
    maxVal = max(maxVal, record[i]);
  }
  cout << maxVal << endl;
  for (int i = 0; i < N; i++) {
    if (record[i] == maxVal) {
      cout << (i+1) << " ";
    }
  }
  system("pause");
  return 0;
}