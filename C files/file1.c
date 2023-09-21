#include <stdio.h>

int main() {
   // printf() displays the string inside quotation
   printf("Hello, World!");

   char name[25]; // char array to store name
   int age;

   printf("\nWhat's your name? ");
   // scanf("%s", &name); // read input from STDIN
   fgets(name, 25, stdin); // read input from STDIN
   name[strlen(name) - 1] = '\0'; // fgets() adds '\n' at the end so we need to remove it

   printf("\nHow old are you? ");
   scanf("%d", &age);

   printf("%s is %d years old", name, age);


   if (age >= 18) {
      printf("\n%s is eligible for voting", name);
   }
   else if (age >= 10) {
      printf("\n%s is not eligible for voting but eligible for casting vote", name);
   }
   else {
      printf("\n%s is not eligible for voting", name);
   }


   char operator;
   double num1;
   double num2;
   double result;

   printf("\nEnter an operator (+ - * /): ");
   scanf("%c", &operator);

   printf("Enter number 1: ");
   scanf("%lf", &num1);

   printf("Enter number 2: ");
   scanf("%lf", &num2);

   switch(operator){
      case '+':
         result = num1 + num2;
         printf("\nresult: %lf", result);
         break;
      case '-':
         result = num1 - num2;
         printf("\nresult: %lf", result);
         break;
      case '*':
         result = num1 * num2;
         printf("\nresult: %lf", result);
         break;
      case '/':
         result = num1 / num2;
         printf("\nresult: %lf", result);
         break;
      default:
         printf("%c is not valid", operator);
   }


   for(int i = 1; i <= 10; i++)
   {
      printf("%d\n", i);
   }

   while(strlen(name) == 0)
   {
      printf("\nYou did not enter your name");
      printf("\nWhat's your name?: ");
      fgets(name, 25, stdin);
      name[strlen(name) - 1] = '\0';
   }

   printf("Hello %s", name);

   int number = 0;
   int sum = 0;

   do{
      printf("Enter a # above 0: ");
      scanf("%d", &number);
      if(number > 0)
      {
         sum += number;
      }
   }while(number > 0);


   double prices[] = {5.0, 10.0, 15.0, 25.0, 20.0};

   for(int i = 0; i < 5; i++)
   {
      printf("\nprices[%d]: %lf", i, prices[i]);
   }

   return 0;

}

