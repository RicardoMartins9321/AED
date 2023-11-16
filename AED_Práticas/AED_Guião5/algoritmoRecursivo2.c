#include <stdio.h>

int T(int n, int* num_calls) {
  (*num_calls)++; // Increment number of calls (operations)
  if (n == 1) {
    return 1;
  } else {
    // n/2 is same as rounding down and (n+1)/2 is same as rounding up
    return T(n/2, num_calls) + T((n+1) / 2, num_calls) + n;
  }
}

int main() {
  for (int n = 1; n <= 15; n++) {
    int num_calls = 0;
    int result = T(n, &num_calls);
    // num_calls-1 porque a primeira chamada não é recursiva
    printf("n: %d \t\tresultado: %d \t\tchamadas: %d\n", n, result, num_calls-1);
  }
  return 0;
}

/* Para a segunda função, a cada chamada recursiva, a função T(n) é chamada duas vezes,
  uma vez com um argumento de n/2 e outra vez com um argumento de (n+1)/2. Portanto, o número
  de chamadas recursivas será 2 vezes menos os casos particulares de cada partição da função
  quando esta vai dar um valor igual a 1. Isso sugere que a complexidade é O(2n-2)*/
