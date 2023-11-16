#include <stdio.h>

// Função para calcular o máximo de dois números
int max(int a, int b) {
  return (a > b)? a : b;
}

// Função Dinâmica para resolver o problema da fileira das moedas
long unsigned int coin_row(unsigned int* C, unsigned int n, unsigned int* num_calls) {
  (*num_calls)++; // Increment number of calls (operations)

  long unsigned int coins[n+1];
  coins[0] = 0;
  coins[1] = C[0];

  for (int i = 2; i <= n; i++) {
    (*num_calls)++; // Increment number of calls (operations)
    coins[i] = max(C[i] + coins[i - 2], coins[i - 1]);
  }

  return coins[n];
}

int main() {
  /*V(0) = 0
    V(1) = c1 = 5
    V(2) = max { c2 + V(0), V(1) } = max { 2 +0, 5 } = 5
    V(3) = max { c3 + V(1), V(2) } = max { 1 + 5, 5 } = 6
    V(4) = max { c4 + V(2), V(3) } = max { 10 + 5, 6 } = 15
    V(5) = max { c5 + V(3), V(4) } = max { 6 + 6, 15 } = 15
    V(6) = max { c6 + V(4), V(5) } = max { 2 + 15, 15 } = 17
    */
  int C[] = {5, 1, 2, 10, 6, 2};
  int n = sizeof(C)/sizeof(C[0]);
  int num_calls = 0;
  int result = coin_row(C, n, &num_calls);

  printf("Max Value: %d \tNum Calls: %d", result, num_calls);
  return 0;
}
