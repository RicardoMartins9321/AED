#include <stdio.h>
#include <math.h>

// Função para calcular a soma dos cubos dos dígitos de um número
double sumOfCubes(int num, int *count) {
  double sum = 0; // tem de ser double por causa da função pow faz com que o resultado seja double

  while(num > 0) {
    (*count)++;
    int digit = num % 10;
    sum += pow(digit, 3);
    num /= 10;
  }
  return sum;
}

int main() {
  int count = 0;

  // Verificar todos os números de 3 dígitos
  for(int i = 100; i < 1000; i++) {
    // caso o número seja igual a soma dos cubos dos seus dígitos é um número de Armstrong
    if(i == sumOfCubes(i, &count)) {
      printf("%d\n", i);
    }
  }

  printf("Numero de vezes que a operação foi executada: %d\n", count);
  return 0;
}
