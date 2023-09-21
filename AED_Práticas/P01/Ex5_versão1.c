#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846

int main(void)
{
  int smallAngle;
  int bigAngle;
  int space;

  printf("\nWhat's the small angle? ");
  scanf("%d", &smallAngle);
  printf("\nWhat's the large angle? ");
  scanf("%d", &bigAngle);
  printf("\n(ex:5 - 0,5,10,15,20...)");
  printf("space in between angles: ");
  scanf("%d", &space);

  printf("ang\tsin(ang)\tcos(ang)\n");
  printf("----\t--------\t--------\n");
  for (int num=smallAngle; num<=bigAngle; num+=space)
  {
    printf("%d\t", num);
    // ind order ro use sin and cos functions, we need to convert the angle to radians
    printf("%lf\t", sin(num * M_PI  / 180));
    printf("%lf\n", cos(num * M_PI  / 180));
  }

  return 0;
}
