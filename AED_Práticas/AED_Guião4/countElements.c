#include <stdio.h>

int countElements(int arr[], int n, int* count, int* comparisons) {
  *count = 0;
  *comparisons = 0; // comparisons = n-2

  for (int i = 1; i < n - 1; i++) {
    (*comparisons)++;
    if (arr[i] == arr[i - 1] + arr[i + 1]) {
      (*count)++;
    }
  }
}

int main() {
  int array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int array2[] = {1, 2, 1, 4, 5, 6, 7, 8, 9, 10};
  int array3[] = {1, 2, 1, 3, 2, 6, 7, 8, 9, 10};
  int array4[] = {0, 2, 2, 0, 3, 3, 0, 4, 4, 0};
  int array5[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int n = sizeof(array1) / sizeof(array1[0]);
  int count, comparisons;

  countElements(array3, n, &count, &comparisons);
  printf("Elements that verify the condition: %d\nComparisons: %d\n", count, comparisons);

  return 0;
}


