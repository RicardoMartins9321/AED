#include <stdio.h>
#include <math.h>

int F_v1(int n)
{
  static int Fv[50] = { 0,1 };
if(n > 1 && Fv[n] == 0)
Fv[n] = F_v1(n - 1) + F_v1(n - 2);
return Fv[n];

}

int main() {
  int n = 1000;
  printf("F_v1(%d) = %d\n", n, F_v1(n));
  return 0;
}

