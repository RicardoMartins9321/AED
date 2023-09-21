#include <stdio.h>

// Note that in C, you need to pass the length of the arrays as additional arguments
// to functions since arrays do not carry their length information with them.

// the funtion printArray receives a pointer to the first element of the array
// and the length of the array
void printArray(const char* s, int* array, int length) {

  printf("%s: ", s);
  for(int i = 0; i < length; i++)
  {
    printf("%d ", array[i]);
  }
  printf("\n");
}

// the function cumSum receives two pointers to the first element of the arrays
// and the length of the arrays
void cumSum(int* a, int* b, int length)
{
  int sum = 0;
  for(int i = 0; i < length; i++)
  {
    sum += a[i];
    b[i] = sum;
  }
}

int main(void)
{
  int a[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int length = sizeof(a) / sizeof(a[0]);

  printArray("a", a, length);

  int b[12];
  cumSum(a, b, length);

  printArray("b", b, length);

  return 0;
}
