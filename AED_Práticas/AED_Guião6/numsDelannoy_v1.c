#include <stdio.h>

int numsDelannoy(int x, int y, int* num_calls) {
  (*num_calls)++; // Increment number of calls (operations)
  if (x==0 || y==0) return 1;

  return numsDelannoy(x-1, y, num_calls) + numsDelannoy(x, y-1, num_calls) + numsDelannoy(x-1, y-1, num_calls);
}

int main() {
  for (int x=1,y = 1; x <= 10; x++,y++) {
    int num_calls = 0;
    int result = numsDelannoy(x, y, &num_calls);
    // num_calls-1 porque a primeira chamada não é recursiva
    printf("(%d,%d) = %d combs \tchamadas: %d\n", x,y, result, num_calls-1);
  }

  /*for (int x=1; x<=10; x++){
    for (int y=1; y<=10; y++){
      int num_calls = 0;
      int result = numsDelannoy(x, y, &num_calls);
      // num_calls-1 porque a primeira chamada não é recursiva
      printf("(%d,%d) = %d combs \tchamadas: %d\n", x,y, result, num_calls-1);
    }
  }*/

  return 0;
}
