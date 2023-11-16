#include <stdio.h>
#include <math.h>

double isArmstrongNumber(int num) {
  int digit_count = 0;
  int temp = num;
  while (temp != 0) {
    temp /= 10;
    digit_count++;
  }

  double sum = 0;
  temp = num;
  while (temp != 0) {
    int digit = temp % 10;
    sum += pow(digit, digit_count);
    temp /= 10;
  }

  return sum == num;
}

void findArmstrongNumbers(int start, int end) {
  printf("Numeros de Armstrong no intervalo de %d a %d:\n", start, end);
  for (int num = start; num <= end; num++) {
    if (isArmstrongNumber(num)) {
      printf("%d\n", num);
    }
  }
}

int main() {
  int start = 1;
  int end = 100000;
  findArmstrongNumbers(start, end);
  return 0;
}
