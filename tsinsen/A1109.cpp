#include <iostream>
using namespace std;

int main() {
  int p;
  int ans[10];
  int i, j, k, r, s, t, u, v;
  int a1, a2, a3;
  bool first = true;
  int ans_count = 0;
  cin >> p;
  if (p >= 17 && p <= 23) {
    int three_point_sum = 3 * p - 45;
    for (i = 1; i <= 9; i++) {
      for (j = i+1; j <= 9; j++) {
        for (k = j+1; k <= 9; k++) {
          if ((i+j+k) == three_point_sum) {
            int tmp[10] = {0};
            tmp[i] = tmp[j] = tmp[k] = 1;
            a1 = p - (i+j);
            a2 = p - (i+k);
            a3 = p - (j+k);
            for (r = 1; r <= 9; r++) {
              for (s = r+1; s <= 9; s++) {
                if (tmp[r] == 0 && tmp[s] == 0 && ((r+s) == a1)) {
                  tmp[r] = tmp[s] = 1;
                  for (t = 1; t <= 9; t++) {
                    for (u = t+1; u <= 9; u++) {
                      if (tmp[t] == 0 && tmp[u] == 0 && ((t+u) == a2)) {
                        ans_count++;
                        if (first) {
                          tmp[t] = tmp[u] = 1;
                          ans[1] = i; ans[2] = r; ans[3] = t;
                          ans[4] = s; ans[5] = u; ans[6] = j;
                          ans[9] = k;
                          for (v = 1; v <= 9; v++) {
                            if (tmp[v] == 0) {
                              ans[7] = v;
                              for (v++; v <= 9; v++) {
                                if (tmp[v] == 0) {
                                  ans[8] = v;
                                  break;
                                }
                              }
                              break;
                            }
                          }
                          tmp[t] = tmp[u] = 0;
                          first = false;
                        }
                      }
                    }
                  }
                  tmp[r] = tmp[s] = 0;
                }
              }
            }
          }
        }
      }
    }
    if (ans_count > 0) {
      cout << ans_count << endl;
      cout << ans[1] << endl;
      cout << ans[2] << " " << ans[3] << endl;
      cout << ans[4] << " " << ans[5] << endl;
      cout << ans[6] << " " << ans[7] << " " << ans[8] << " " << ans[9] << endl;
    } else {
      cout << "NO" << endl;
    }
  } else {
    cout << "NO" << endl;
  }
  return 0;
}