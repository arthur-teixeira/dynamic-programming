#include <math.h>
#include <string.h>
// https://leetcode.com/problems/climbing-stairs
// literally the same as a Fibonacci sequence

int climbStairs(int n) {
  if (n <= 1) {
    return 1;
  }

  return climbStairs(n - 1) + climbStairs(n - 2);
}

int climbStairsAux(int n, int *results) {
  if (n <= 1) {
    return 1;
  }

  int l;
  if (results[n - 1] >= 0) {
    l = results[n - 1];
  } else {
    l = climbStairsAux(n - 1, results);
    results[n - 1] = l;
  }

  int r;
  if (results[n - 2] >= 0) {
    r = results[n - 2];
  } else {
    r = climbStairsAux(n - 2, results);
    results[n - 2] = l;
  }

  return l + r;
}

int climbStairsMemoized(int n) {
  int results[n];
  memset(&results, -1, sizeof(results));

  return climbStairsAux(n, results);
}

int climbStairsBottomUp(int n) {
  int results[n];
  memset(&results, -1, sizeof(results));

  results[0] = 0;
  results[1] = 1;

  for (int i = 2; i <= n; i++) {
    results[i] = results[i - 1] + results[i - 2];
  }

  return results[n];
}

int climbStairsBinetFormula(int n) {
  int q = n + 1;

  float sqrt5 = sqrt(5);
  float goldenMean = (1 + sqrt5) / 2;
  float phi = (1 - sqrt5) / 2;

  return floorf((1 / sqrt5) * (powf(goldenMean, q) - powf(phi, q)));
}
