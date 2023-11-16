#include <stdio.h>

// Função para calcular o máximo de dois números
int max(int a, int b) {
  return (a > b)? a : b;
}

// Função recursiva para resolver o problema da fileira das moedas
int coin_row(int* C, int n, int* num_calls) {
  (*num_calls)++; // Increment number of calls (operations)

  if(n==0) return 0;
  if(n==1) return C[0];

  return max(C[n] + coin_row(C, n-2, num_calls), coin_row(C, n-1, num_calls));
}

int main() {
  int C[] = {5, 1, 2, 10, 6, 2};
  int n = sizeof(C)/sizeof(C[0]);
  int num_calls = 0;
  int result = coin_row(C, n, &num_calls);

  printf("Max Value: %d \tNum Calls: %d", result, num_calls);
  return 0;
}
