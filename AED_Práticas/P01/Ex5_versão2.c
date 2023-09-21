#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846

int main(void)
{
  FILE *fp;
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


  fp = fopen("Ex5.txt", "w");
    if (fp == NULL) {
        printf("File couldn't be created\n");
        return 1;
    }

  fprintf(fp, "This is a test file.\n");

  fprintf(fp, "ang\tsin(ang)\tcos(ang)\n");
  fprintf(fp, "----\t--------\t--------\n");
  for (int num=smallAngle; num<=bigAngle; num+=space)
  {
    fprintf(fp, "%d\t", num);
    // ind order ro use sin and cos functions, we need to convert the angle to radians
    fprintf(fp, "%lf\t", sin(num * M_PI  / 180));
    fprintf(fp, "%lf\n", cos(num * M_PI  / 180));
  }
  fclose(fp);

    printf("\nFile created and written successfully.\n");
  return 0;
}
