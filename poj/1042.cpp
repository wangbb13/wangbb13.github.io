/*
* input: 
* n (n lakes)
*   [2, 25]
* h (have h hours, 12h unit, unit=5min)
*   [1, 16] -> [12, 12*16]
* f1, f2, ..., fn   (initial unit fishes expected to catch)
    [0, )
* d1, d2, ..., dn   (decease count after catching)
    [0, )
* t1, t2, ..., tn-1 (travel cost)
    [0, 192]
sample input: 
2 
1 
10 1 
2 5 
2 
4 
4 
10 15 20 17 
0 3 4 3 
1 2 3 
4 
4 
10 15 50 30 
0 3 4 3 
1 2 3 
0
sample output:
45, 5 
Number of fish expected: 31 

240, 0, 0, 0 
Number of fish expected: 480 

115, 10, 50, 35 
Number of fish expected: 724
*/
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
  int n, h, f[25] = {0}, d[25] = {0}, t[25] = {0};
  int i, j;
  while (true) {
    cin >> n;
    if (n == 0) {
      break;
    }
    int cost[25][25] = {0};
    cin >> h;
    h *= 12;
    for (i = 0; i < n; i++) {
      cin >> f[i];
    }
    for (i = 0; i < n; i++) {
      cin >> d[i];
    }
    for (i = 1; i < n; i++) {
      cin >> t[i];
      t[i] += t[i-1];
    }
    int max_fishes = 0, max_index = 0;
    for (i = 0; i < n; i++) {
      int remain_time = h - t[i];
      int fish[25];
      int l = i + 1, none_l = 0, catch_fish = 0;
      for (j = 0; j <= i; j++) {
        fish[j] = f[j];
        if (fish[j] == 0) {
          none_l++;
        }
      }
      while (remain_time > 0 && none_l != l) {
        remain_time--;
        int temp = 0;
        for (j = 1; j < l; j++) {
          if (fish[j] > fish[temp]) {
            temp = j;
          }
        }
        catch_fish += fish[temp];
        cost[i][temp] += 5;
        fish[temp] -= d[temp];
        if (fish[temp] <= 0) {
          none_l++;
        }
      }
      cost[i][0] += remain_time * 5;
      if (catch_fish > max_fishes) {
        max_fishes = catch_fish;
        max_index = i;
      }
    }
    for(i = 0; i < (n-1); i++) {
      cout << cost[max_index][i] << ", ";
    }
    cout << cost[max_index][n-1] << endl;
    cout << "Number of fish expected: " << max_fishes << endl << endl;
  }
  return 0;
}
