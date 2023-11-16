//
// Tomás Oliveira e Silva, AED, October 2021
//
// explain the program output
//
// try also compiling the program with the -Wsign-compare compilation flag
//

#include <stdio.h>

int main(void)
{
  unsigned int i = 1;
  int j = -1;
  int k = -2147483648;

  printf("original i = %u\n",i);
  printf("original j = %d\n",j);
  printf("original k = %d\n",k);
  // compare i with j
  // como i está representado sem sinal na memoria i=0000...01 enquanto que
  // j tem sinal e está representado na memória com sinal logo j=1111...10
  // depois quando comparamos um com o outro fazemos uma comparação sem sinal e
  // por isso o número sem sinal de j é bastante superior do que o de i
  if(i > j)
    printf("i > j is true\n");
  else
    printf("i > j is false\n");
  // replace k by its absolute value and print the result
  // k = -2^31 que é o menor número representável para um inteiro de 32 bits enquanto
  // que o maior é 2^31-1, por isso quando tentamos converter o número para positivo
  // náo é possivel adicionar o 0 binário atrás do número para que ele seja positivo
  // pelo que ele continua a ser o mesmo número
  if(k < 0)
    k = -k;
  printf("absolute value of k = %d\n",k);
  return 0;
}
