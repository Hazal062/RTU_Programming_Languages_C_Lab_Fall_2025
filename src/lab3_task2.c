/*
 * Lab 3, Task 2
 * Name: Hazal Guc
 * Student ID: 231ADB264
 *
 * Practice using pointers as function parameters.
 * Implement:
 *  - swap (exchange values of two ints)
 *  - modify_value (multiply given int by 2)
 *
 * Rules:
 *  - Use pointers to modify variables in the caller.
 *  - Demonstrate changes in main.
 *
 * Example (expected behavior):
 *   int a = 5, b = 10;
 *   swap(&a, &b);        // now a = 10, b = 5
 *   int x = 7;
 *   modify_value(&x);    // now x = 14
 */

#include <stdio.h>

/* Function prototypes (given by the template) */
void swap(int *x, int *y);
void modify_value(int *x);

/* --- Implementations --- */

void swap(int *x, int *y) {
  if (!x || !y) return;  // defensive: null pointer guard
  int t = *x;
  *x = *y;
  *y = t;
}

void modify_value(int *x) {
  if (!x) return;  // defensive: null pointer guard
  *x *= 2;
}

/* --- Simple tests in main --- */
int main(void) {
  int a = 5, b = 10;
  printf("Before swap: a=%d, b=%d\n", a, b);
  swap(&a, &b);
  printf("After  swap: a=%d, b=%d\n", a, b);  // a=10, b=5

  int v = 7;
  printf("Before modify_value: v=%d\n", v);
  modify_value(&v);
  printf("After  modify_value: v=%d\n", v);  // v=14

  return 0;
}
