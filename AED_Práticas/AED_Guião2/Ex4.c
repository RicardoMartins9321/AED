#include <stdio.h>
#include <stdlib.h>

void DisplayArray(double* a, size_t n) {
  if (a == NULL || n == 0) {
    printf("Invalid input: array is NULL or n is zero.\n");
    return;
  }

  printf("Array = [ ");
  for (size_t i = 0; i < n; i++) {
    printf("%.2lf", a[i]);
    if (i < n - 1) {
      printf(", ");
    }
  }
  printf(" ]\n");
}

double* ReadArray(size_t* size_p) {
  if (size_p == NULL || *size_p <= 0) {
    return NULL;
  }

  double* array = (double*)malloc(*size_p * sizeof(double));
  if (array == NULL) {
    *size_p = 0;
    return NULL; // Falha na alocação de memória
  }

  printf("Enter %zu elements:\n", *size_p);
  for (size_t i = 0; i < *size_p; i++) {
    if (scanf("%lf", &array[i]) != 1) {
      free(array);
      *size_p = 0;
      return NULL; // Falha na leitura
    }
  }

  return array;
}

double* Append(double* array_1, size_t size_1, double* array_2, size_t size_2) {
  if (array_1 == NULL || array_2 == NULL || size_1 <= 0 || size_2 <= 0) {
    return NULL;
  }

  double* result = (double*)malloc((size_1 + size_2) * sizeof(double));
  if (result == NULL) {
    return NULL; // Falha na alocação de memória
  }

  for (size_t i = 0; i < size_1; i++) {
    result[i] = array_1[i];
  }

  for (size_t i = 0; i < size_2; i++) {
    result[size_1 + i] = array_2[i];
  }

  return result;
}

int main() {
  size_t size1, size2;
  printf("Enter the number of elements for array 1: ");
  if (scanf("%zu", &size1) != 1 || size1 <= 0) {
    printf("Invalid size for array 1.\n");
    return 1;
  }

  double* array1 = ReadArray(&size1);
  if (array1 == NULL) {
    printf("Failed to read array 1.\n");
    return 1;
  }

  printf("Enter the number of elements for array 2: ");
  if (scanf("%zu", &size2) != 1 || size2 <= 0) {
    printf("Invalid size for array 2.\n");
    free(array1);
    return 1;
  }

  double* array2 = ReadArray(&size2);
  if (array2 == NULL) {
    printf("Failed to read array 2.\n");
    free(array1);
    return 1;
  }

  printf("Array 1: ");
  DisplayArray(array1, size1);
  printf("Array 2: ");
  DisplayArray(array2, size2);

  double* combinedArray = Append(array1, size1, array2, size2);
  if (combinedArray == NULL) {
    printf("Failed to combine arrays.\n");
    free(array1);
    free(array2);
    return 1;
  }

  printf("Combined Array: ");
  DisplayArray(combinedArray, size1 + size2);

  free(array1);
  free(array2);
  free(combinedArray);

  return 0;
}
