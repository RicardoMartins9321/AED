#include <stdio.h>


int countTriplets(int arr[], int size, int* count, int* comparisons) {
    *count = 0;
    *comparisons = 0;

    // i <= size-3 to avoid out of bounds
    for (int i = 0; i < size-2; i++) {
        // j = i+1 to avoid duplicate triplets and j <= size-2 to avoid out of bounds
        for (int j = i + 1; j < size-1; j++) {
            // k = j+1 to avoid duplicate triplets and k <= size-1 to avoid out of bounds
            for (int k = j + 1; k <= size-1; k++) {
                (*comparisons)++;
                if (arr[k] == arr[i] + arr[j]) {
                    (*count)+=1;
                }
            }
        }
    }

  return count;
}

int main() {
  int array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int array2[] = {1, 2, 1, 4, 5, 6, 7, 8, 9, 10};
  int array3[] = {1, 2, 1, 3, 2, 6, 7, 8, 9, 10};
  int array4[] = {0, 2, 2, 0, 3, 3, 0, 4, 4, 0};
  int array5[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int array6[] = {4, 4, 4, 2, 4, 6, 6, 6, 3, 3};
  int* arrays[] = {array1, array2, array3, array4, array5, array6};

  int nArray = 1; // Initialize nArray to 1

  for (int i = 0; i <= sizeof(arrays); i++) {
    int count;
    int comparisons = 0;
    int size = sizeof(arrays[i]) / sizeof(arrays[i][0]);

    countTriplets(arrays[i], 10, &count,&comparisons);
    printf("Triplets in the array%d: %d\nComparisons: %d\n", nArray, count, comparisons);
    nArray++; // Increment nArray
  }

  return 0;
}


