#include <stdio.h>


int countElements(float arr[], int n, int* num_operations) {
  if (n <= 2) {
    return 1;
  }

  float ratio = arr[1]/arr[0];
  *num_operations = 1; // Start with 1 operation for the initial ratio calculation

  for (int i = 2; i < n; i++) {
    (*num_operations)+=2; // Increment operation count for each comparison and division
    if (arr[i]/arr[i-1] != ratio) {
      return 0;
    }
  }
  return 1;
}

int main() {
  float array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  float array2[] = {1, 2, 4, 4, 5, 6, 7, 8, 9, 10};
  float array3[] = {1, 2, 4, 8, 5, 6, 7, 8, 9, 10};
  float array4[] = {1, 2, 4, 8, 16, 6, 7, 8, 9, 10};
  float array5[] = {1, 2, 4, 8, 16, 32, 7, 8, 9, 10};
  float array6[] = {1, 2, 4, 8, 16, 32, 64, 8, 9, 10};
  float array7[] = {1, 2, 4, 8, 16, 32, 64, 128, 9, 10};
  float array8[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 10};
  float array9[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
  float* arrays[] = {array1, array2, array3, array4, array5, array6, array7, array8, array9};

  int nArray = 1; // Initialize nArray to 1

  for (int i = 0; i < 9; i++) {
    int numOps = 0;
    int size = sizeof(arrays[i]) / sizeof(arrays[0]);

    int result = countElements(arrays[i], 10, &numOps);
    printf("Result in the array%d: %d\nOperations: %d\n", nArray, result, numOps);
    nArray++; // Increment nArray
  }

  return 0;
}


