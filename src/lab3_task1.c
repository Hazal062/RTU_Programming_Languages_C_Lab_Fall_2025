/*
 * Lab 3, Task 1
 * Name: Hazal Guc
 * Student ID: 231ADB264
 *
 * Implement array algorithms:
 * - find minimum value
 * - find maximum value
 * - calculate sum
 * - calculate average
 */

#include <stdio.h>

int array_min(const int arr[], int size) {
  if (size <= 0) return 0;
  int m = arr[0];
  for (int i = 1; i < size; i++)
    if (arr[i] < m) m = arr[i];
  return m;
}

int array_max(const int arr[], int size) {
  if (size <= 0) return 0;
  int m = arr[0];
  for (int i = 1; i < size; i++)
    if (arr[i] > m) m = arr[i];
  return m;
}

int array_sum(const int arr[], int size) {
  long long s = 0;
  for (int i = 0; i < size; i++) s += arr[i];
  return (int)s;
}

float array_avg(const int arr[], int size) {
  if (size <= 0) return 0.0f;
  long long s = 0;
  for (int i = 0; i < size; i++) s += arr[i];
  return (float)s / size;
}

int main(void) {
  int arr[] = {10, 20, 5, 30, 15};
  int n = sizeof(arr) / sizeof(arr[0]);

  printf("Min: %d\n", array_min(arr, n));
  printf("Max: %d\n", array_max(arr, n));
  printf("Sum: %d\n", array_sum(arr, n));
  printf("Avg: %.2f\n", array_avg(arr, n));

  return 0;
}
