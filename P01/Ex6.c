#include <stdio.h>


int main(void)
{
  printf("size in bytes: %lu\n", sizeof(void *));
  printf("size in bytes: %lu\n", sizeof(void));
  printf("size in bytes: %lu\n", sizeof(char));
  printf("size in bytes: %lu\n", sizeof(short));
  printf("size in bytes: %lu\n", sizeof(int));
  printf("size in bytes: %lu\n", sizeof(long));
  printf("size in bytes: %lu\n", sizeof(long long));
  printf("size in bytes: %lu\n", sizeof(float));
  printf("size in bytes: %lu\n", sizeof(double));

  return 0;
}
