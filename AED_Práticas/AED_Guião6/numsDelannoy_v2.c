#include <stdio.h>

long unsigned int numsDelannoy(unsigned int x, unsigned y, unsigned int* num_calls) {
  long unsigned int comb[x+1][y+1];

  for (int i = 0; i <= x; i++) {
    for (int j = 0; j <= y; j++) {
      if (i==0 || j==0) {
        comb[i][j] = 1;
      } else {
        comb[i][j] = comb[i-1][j] + comb[i][j-1] + comb[i-1][j-1];
      }
      (*num_calls)++; // Increment number of calls (operations)
    }
  }

  return comb[x][y];
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
