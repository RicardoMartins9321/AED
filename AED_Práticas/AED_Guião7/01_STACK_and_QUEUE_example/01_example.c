//
// TO DO : desenvolva um algoritmo para verificar se um numero inteiro positivo
//         e uma capicua
//         Exemplos: 12321 e uma capiacua, mas 123456 nao e
//         USE uma PILHA DE INTEIROS (STACK) e uma FILA DE INTEIROS (QUEUE)
//
// TO DO : design an algorithm to check if the digits of a positive decimal
//         integer number constitue a palindrome
//         Examples: 12321 is a palindrome, but 123456 is not
//         USE a STACK of integers and a QUEUE of integers
//

#include <stdio.h>

#include "IntegersQueue.h"
#include "IntegersStack.h"

int main(void) {
  int n, num;
  printf("Escolha um numero: ");
  scanf("%d", &n);
  num = n;

  Queue* q = QueueCreate(100);
  Stack* s = StackCreate(100);

  while(n > 0) {
    int algarismo = n % 10; // obtem o ultimo digito
    QueueEnqueue(q, algarismo);
    StackPush(s, algarismo);
    n /= 10;  // reduz o numero de digitos
  }

  int isCapicua = 1;

  while (!QueueIsEmpty(q) && !StackIsEmpty(s)) {
    if (StackPop(s) != QueueDequeue(q)) {
      isCapicua = 0;
      break;
    }
  }

  if (isCapicua) {
    printf("%d is a capicua\n", num);
  } else {
    printf("%d is not a capicua\n", num);
  }

  return 0;
}
