#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int cut_rod(int *p, int n) {
  if (n == 0) {
    return 0;
  }
  int q = -1;
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

int *extended_cut_rod(int *p, int n, int *s) {
  int *r = calloc(n + 1, sizeof(int));
  memset(r, -1, sizeof(*r));
  r[0] = 0;

  for (int j = 1; j <= n; j++) {
    int q = -1;
    for (int i = 1; i <= j; i++) {
      if (q < p[i] + r[j - i]) {
        q = p[i] + r[j - i];
        s[j] = i;
      }
    }
    r[j] = q;
  }

  return r;
}

void print_cut_rod_solution(int *p, int n) {
  int s[n + 1];
  memset(s, -1, sizeof(s));

  int *r = extended_cut_rod(p, n, s);

  printf("Optimal solution for %d: ", n);
  while (n > 0) {
    printf("%d ", s[n]);
    n -= s[n];
  }

  printf("\n");
}

void gen_prices(int *ps, int n) {
  ps[0] = 0;
  for (int i = 1; i < n; i++) {
    ps[i] = (int)(10.0 * rand() / (RAND_MAX + 1.0));
  }
}

void print_prices(int *ps, int n) {
  printf("prices: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", ps[i]);
  }
  printf("\n");
}

int main() {
  int n = 8;
  int prices[n];
  srand(time(NULL));
  gen_prices(prices, n);
  print_prices(prices, n);

  printf("Max revenue for %d: %d\n", n, memoized_cut_rod(prices, n));
  printf("Max revenue for %d: %d\n", n, bottom_up_cut_rod(prices, n));
  print_cut_rod_solution(prices, n);
}
