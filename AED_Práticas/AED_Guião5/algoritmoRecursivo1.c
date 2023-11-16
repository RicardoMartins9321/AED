#include <stdio.h>

int T(int n, int* num_calls) {
  (*num_calls)++; // Increment number of calls (operations)
  if (n == 1) {
    return 1;
  } else {
    // n/2 is same as rounding down
    return T(n/2, num_calls) + n;
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

/* Para a primeira função, a cada chamada recursiva, o valor de n é dividido por 2. Portanto, o número
  de chamadas recursivas é igual ao número de vezes que podemos dividir n por 2 até que o resultado
  seja menor que 1. Isso é equivalente a log(n) na base 2, então a complexidade é O(log n)*/
