#include <stdio.h>
# include <stdlib.h>
# include <time.h>

enum Day{Sun = 1, Mon = 2, Tue = 3, Wed = 4, Thu = 5, Fri = 6, Sat = 7};

void printAge(int *pAge)
{
   printf("You are %d years old\n", *pAge); //dereference
}

int main(){

  enum Day today;
  today = Sun;

  if(today == Sun || today == Sat)
  {
    printf("\nIt's the weekend! Party time!");
  }
  else
  {
    printf("\nI have to work today :(");
  }


  // Use current time as a seed for random # generator
   srand(time(0));

   // rand() generates a pseudo random # between 0 - 32,767
   int number1 = (rand() % 6) + 1;
   int number2 = (rand() % 6) + 1;
   int number3 = (rand() % 6) + 1;

   printf("%d\n", number1);
   printf("%d\n", number2);
   printf("%d\n", number3);


  // BITWISE OPERATORS = special operators used in bit level programming
  //                                          (knowing binary is important for this topic)

  // & = AND
  // | = OR
  // ^ = XOR
  // <<  left shift
  // >>  right shift

  int x = 6;  //    6 = 00000110
  int y = 12; //    12 = 00001100
  int z = 0;  //    0 = 00000000

  z = x & y; // 1 if both bits are 1
  printf("AND = %d\n", z);

  z = x | y; // 1 if either bit is 1
  printf("OR = %d\n", z);

  z = x ^ y; // 1 if both bits are different
  printf("XOR = %d\n", z);

  z = x << 2;  // x * 2^2
  printf("SHIFT LEFT = %d\n", z);

  z = x >> 2;  // x / 2^2
  printf("SHIFT RIGHT = %d\n", z);

  // memory = an array of bytes within RAM (street)
  // memory block = a single unit (byte) within memory (house), used to hold some value (person)
  // memory address = the address of where a memory block is located (house address)

  char a;
  char b[1];

  printf("%d bytes\n", sizeof(a));
  printf("%d bytes\n", sizeof(b));

  printf("%p\n", &a);
  printf("%p\n", &b);


  // pointer = a "variable-like" reference that holds a memory address to another variable, array, etc.
  //           some tasks are performed more easily with pointers
  //           * = indirection operator (value at address)

  int age = 21;
  int *pAge = &age;

  printAge(pAge);

  //printf("address of age: %p\n", &age);
  //printf("value of pAge: %p\n", pAge);
  //printf("size of age: %d bytes\n", sizeof(age));
  //printf("size of pAge: %d bytes\n", sizeof(pAge));
  //printf("value of age: %d\n", age);
  //printf("value at stored address: %d\n", *pAge); //dereferencing

   return 0;
}
