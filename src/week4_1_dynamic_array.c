/*
 * File: week4_1_dynamic_array.c
 * Author: Hazal Guc
 * Student ID: 231ADB264
 * Description:
 *   Create an int array dynamically with malloc, read values,
 *   compute sum and average, print results, then free memory.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n;
  int *arr = NULL;

  printf("Enter number of elements: ");
  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid size.\n");
    return 1;
  }

arr = (int *)malloc((size_t)n * sizeof *arr);
  if (arr == NULL) {
    perror("malloc");
    return 1;
  }

  printf("Enter %d integers: ", n);
  long long sum = 0;
  for (int i = 0; i < n; i++) {
    if (scanf("%d", &arr[i]) != 1) {
      printf("Invalid input.\n");
      free(arr);
      return 1;
    }
    sum += arr[i];
  }

  double avg = (double)sum / n;
  printf("Sum = %lld\n", sum);
  printf("Average = %.2f\n", avg);

  free(arr);
  return 0;
}
