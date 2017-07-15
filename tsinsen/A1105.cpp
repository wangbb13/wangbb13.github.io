#include <iostream>
#include <vector>
using namespace std;


int main(int argc, char const *argv[])
{
  vector< vector<int> > ans;
  vector< vector<int> > temp;
  vector<int> mine(12, 0);
  vector< vector<int> > matrix(12, vector<int>(12, 0));
  int n;
  int i, j, k, r, s, sum = 0, max_val = -1;
  cin >> n;
  if (n == 0) {
    cout << 0 << endl;
    cout << "MAX=0" << endl;
    return 0;
  }
  for (i = 0; i < n; i++) {
    cin >> mine[i];
    sum += mine[i];
  }
  for (i = 0; i < n-1; i++) {
    for (j = i+1; j < n; j++) {
      cin >> k;
      if (k == 1) {
        matrix[i][j] = 1;
        matrix[j][i] = 1;
      }
    }
  }
  for (i = 0; i < n; i++) {
    vector< vector<int> > level;
    vector<int> a;
    a.push_back(i);
    a.push_back(mine[i]);
    a.push_back((1 << i));
    level.push_back(a);
    bool proceed = true;
    while (proceed) {
      proceed = false;
      vector< vector<int> > next;
      for (j = 0; j < level.size(); j++) {
        r = level[j][0];
        s = level[j].size();
        bool flag = true;
        for (k = 0; k < n; k++) {
          if ((matrix[r][k] == 1) && ((level[j][s-1] & (1 << k)) == 0)) {
            flag = false;
            vector<int> copy(level[j].begin(), level[j].end());
            copy.insert(copy.begin(), k);
            copy[s-1] += mine[k];
            if (copy[s-1] == sum) {
              for (s = s - 2; s > 0; s--) {
                cout << (copy[s] + 1) << "-";
              }
              cout << (copy[0] + 1) << endl;
              cout << "MAX=" << sum << endl;
              return 0;
            }
            copy[s] |= (1 << k);
            next.push_back(copy);
            proceed = true;
          }
        }
        if (flag) {
          next.push_back(level[j]);
        }
      }
      if (proceed) {
        temp = level;
        level = next;
        next = temp;
      }
    }
    max_val = -1;
    k = -1;
    for (j = 0; j < level.size(); j++) {
      s = level[j].size();
      if (level[j][s-2] > max_val) {
        k = j;
        max_val = level[j][s-2];
      }
    }
    ans.push_back(level[k]);
  }
  max_val = -1;
  k = -1;
  for (j = 0; j < ans.size(); j++) {
    s = ans[j].size();
    if (ans[j][s-2] > max_val) {
      k = j;
      max_val = ans[j][s-2];
    }
  }
  s = ans[k].size();
  for (j = s - 3; j > 0; j--) {
    cout << (ans[k][j] + 1) << "-";
  }
  cout << (ans[k][0] + 1) << endl;
  cout << "MAX=" << ans[k][s-2] << endl;
  return 0;
}