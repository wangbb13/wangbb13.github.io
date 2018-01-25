#include <stdio.h>
#include <stdlib.h>
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

int N = 12 * 60 * 60;
int K[14410] = {0};

int main() {
  int i, j, s, m, h, mx, mi, md;
  double d, ans;
  for (i = 0; i < N; i++) {
    s = (i % 60) * 60 * 12;
    m = (i % 3600) * 12;
    h = i;
    mi = min(min(s, m), h);
    mx = max(max(s, m), h);
    md = s + m + h - mi - mx;
    j = min(min(mi + N - mx, md - mi), mx - md);
    K[j] ++;
  }
  for (i = 14409; i >= 0; i--) {
    K[i] += K[i+1];
  }
  while (scanf("%lf", &d) && d >= 0.) {
    ans = (double)K[(int)((d / 360.) * (double)N)] / (double)N * 100.;
    printf("%.3lf\n", ans);
  }
  system("pause");
  return 0;
}