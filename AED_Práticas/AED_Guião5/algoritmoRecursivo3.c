#include <stdio.h>

int T(int n, int* num_calls) {
  (*num_calls)++; // Increment number of calls (operations)
  if (n == 1) {
    return 1;
  } else if (n%2 == 0) {
    return 2 * T(n/2, num_calls) + n;
  } else {
    // n/2 is same as rounding down and (n+1)/2 is same as rounding up
    return T(n/2, num_calls) + T((n+1) / 2, num_calls) + n;
  }
}

int main() {
  for (int n = 1; n <= 100; n++) {
    int num_calls = 0;
    int result = T(n, &num_calls);
    // num_calls-1 porque a primeira chamada não é recursiva
    printf("n: %d \t\tresultado: %d \t\tchamadas: %d\n", n, result, num_calls-1);
  }
  return 0;
}

/*Para a terceira função, o número de chamadas recursivas depende se n é par ou ímpar
  e diminui à medida que n é dividido por 2 em cada chamada recursiva. Isso sugere que
  a complexidade é entre O(log n) para números pares e O(n) para números ímpares*/
