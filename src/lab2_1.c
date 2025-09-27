#include <stdio.h>

long long sum_to_n(int n) {
  long long sum = 0;
  for (int i = 1; i <= n; i++) {
    sum += i;
  }
  return sum;
}

int main(void) {
  int n;
  printf("Enter a positive integer n: ");
  if (scanf("%d", &n) != 1) {
    printf("Error: invalid input.\n");
    return 1;
  }

  if (n < 1) {
    printf("Error: n must be >= 1.\n");
    return 1;
  }

  long long result = sum_to_n(n);
  printf("Sum 1..%d = %lld\n", n, result);

  return 0;
}
