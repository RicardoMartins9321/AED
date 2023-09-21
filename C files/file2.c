#include <stdio.h>
#include <string.h>

void birthday(char x[], int y); // function prototype (declaration) - tells compiler about the function

void birthday(char x[], int y)
{
   printf("\nHappy birthday dear %s!", x);
   printf("\nYou are %d years old!", y);
}

double add(double x, double y)
{
   return x + y;
}

int findMax(int x, int y)
{
   return (x > y) ? x : y;
}


void sort(char array[], int size)
{
   for(int i = 0; i < size - 1; i++)
   {
      for(int j = 0; j < size - i - 1; j++)
      {
         if(array[j] > array[j+1])
         {
            int temp = array[j];
            array[j] = array[j+1];
            array[j+1] = temp;
         }
      }
   }
}

void printArray(char array[], int size)
{
   for(int i = 0; i < size; i++)
   {
      printf("%c ", array[i]);
   }
}

struct Player
{
   char name[12];
   int score;
};

int main()
{
  char name[] = "Bro";
  int age = 21;
  double num1 = 10.5;
  double num2 = 20.5;


  birthday(name, age);
  printf("\nresult: %lf", add(num1, num2));


  int max = findMax(10, 20);
  printf("\nmax: %d", max);


  char cars[][10] = {"Mustang","Corvette","Camaro"};

   //cars[0] = "Tesla";
   strcpy(cars[0], "Tesla");

  for(int i = 0; i < sizeof(cars)/sizeof(cars[0]); i++)
  {
    printf("%s\n", cars[i]);
  }


  //int array[] = {9, 1, 8, 2, 7, 3, 6, 4, 5};
  char array[] = {'F', 'A', 'D', 'B', 'C'};
  int size = sizeof(array)/sizeof(array[0]);

  sort(array, size);
  printArray(array, size);


   // struct = collection of related members ("variables")
   //          they can be of different data types
   //          listed under one name in a block of memory
   //          VERY SIMILAR to classes in other languages (but no methods)

   struct Player player1 = {"Bro", 4};
   struct Player player2 = {"Bra", 5};

   //strcpy(player1.name, "Bro");
   //player1.score = 4;

   //strcpy(player2.name, "Bra");
   //player2.score = 5;

   printf("%s\n", player1.name);
   printf("%d\n", player1.score);

   printf("%s\n", player2.name);
   printf("%d\n", player2.score);


  return 0;
}
