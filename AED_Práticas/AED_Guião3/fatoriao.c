#include <stdio.h>
#include "elapsed_time.h"
#include <time.h>

// Função para calcular o fatorial de um número
int factorial(int n) {
  int fact = 1;
  int mults = 0;

  for(int i = 2; i <= n; i++) {
    fact *= i;
  }
  return fact;
}

// Função para calcular a soma dos fatoriais dos dígitos de um número
int sumOfFactorials(int num, int factorials[], int* ndivs) {
  int sum = 0;

  while (num > 0) {
    int digit = num % 10; // obtem o último dígito do número
    sum += factorials[digit]; // soma o fatorial do dígito final ao total
    num /= 10;  // retira uma casa decimal ao número
    (*ndivs) += 2;
  }
  return sum;
}

int main() {
  // Calcular os fatoriais de 0 a 9
  int factorials[10];
  for(int i = 0; i < 10; i++) {
    factorials[i] = factorial(i);
  }

  int ndivs = 0;

  // Tempo de início
  clock_t start_time = clock();

  // Verificar todos os números de 1 a 10^6
  for(int i = 1; i < 1000000; i++) {
    // caso o número seja igual a soma dos fatoriais dos seus dígitos é um fatorião
    if(i == sumOfFactorials(i, factorials, &ndivs)) {
      printf("%d\n", i);
    }
  }

  // Tempo de término
  clock_t end_time = clock();

  // Tempo de execução em segundos
  double exec_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

  printf("Tempo de execucão: %f segundos\n", exec_time);
  printf("Numero de divisoes: %d\n", ndivs);


  return 0;
}
