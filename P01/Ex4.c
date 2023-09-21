#include <stdio.h>
#include <math.h>

int main(void)
{
  int rows;

  printf("\nHow many rows do you want? ");
  scanf("%d", &rows);

  printf("num*num\t\tsqrt(num)\n");
  for (int num=1; num <=rows; num++)
  {
    printf("%d\t\t", num*num);
    printf("%lf\n", sqrt(num));
  }

  return 0;
}
