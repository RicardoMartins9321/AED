#include <stdio.h>

#define SIZE 100
long unsigned int CombCache[SIZE][SIZE];

void initializeCache() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++)
      CombCache[i][j] = 0;
  }
}

long unsigned int numsDelannoy(unsigned int x, unsigned y, unsigned int* num_calls) {
  (*num_calls)++; // Increment number of calls (operations)

  if (CombCache[x][y] != 0) return CombCache[x][y];

  long unsigned int r;
  if (x==0 || y==0) {
    r = 1;
  } else {
    r = numsDelannoy(x-1, y, num_calls) + numsDelannoy(x, y-1, num_calls) + numsDelannoy(x-1, y-1, num_calls);
  }

  CombCache[x][y] = r;
  return r;
}

int main() {
  for (int x=1,y = 1; x <= 50; x++,y++) {
    int num_calls = 0;
    int result = numsDelannoy(x, y, &num_calls);
    // num_calls-1 porque a primeira chamada não é recursiva
    printf("(%d,%d) = %d combs \tchamadas: %d\n", x,y, result, num_calls-1);
  }
  return 0;
}
