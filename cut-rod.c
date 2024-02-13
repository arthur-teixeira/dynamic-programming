#include <math.h>
#include <stdio.h>
#include <string.h>

int cut_rod(int *p, int n) {
  if (n == 0) {
    return 0;
  }
  int q = -INFINITY;
  for (int i = 1; i <= n; i++) {
    q = fmaxf(q, p[i] + cut_rod(p, n - i));
  }

  return q;
}

int memoized_cut_rod_aux(int *p, int n, int *r) {
  if (r[n] >= 0) {
    return r[n];
  }

  int q;
  if (n == 0) {
    q = 0;
  } else {
    q = -1;
    for (int i = 1; i <= n; i++) {
      q = fmaxf(q, p[i] + memoized_cut_rod_aux(p, n - i, r));
      r[n] = q;
    }
  }

  return q;
}

int memoized_cut_rod(int *p, int n) {
  int r[n + 1];
  memset(&r, -1, sizeof(r));

  return memoized_cut_rod_aux(p, n, r);
}

int bottom_up_cut_rod(int *p, int n) {
  int r[n + 1];
  memset(&r, -1, sizeof(r));
  r[0] = 0;

  for (int j = 1; j <= n; j++) {
    int q = -1;

    for (int i = 1; i <= j; i++) {
      q = fmaxf(q, p[i] + r[j - i]);
    }
    r[j] = q;
  }

  return r[n];
}

int main() {
  int prices[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
  int n = 10;

  printf("Max revenue for 30: %d\n", memoized_cut_rod(prices, 300));
  printf("Max revenue for 30: %d\n", bottom_up_cut_rod(prices, 300));
}
