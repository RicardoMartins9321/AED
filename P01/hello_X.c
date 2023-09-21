#include <stdio.h>

int main(void)
{
  char name[25]; // char array to store name

  printf("\nWhat's your name? ");
  // scanf("%s", &name); // stops reading when it finds a white space
  fgets(name, 25, stdin); // read input from STDIN
  name[strlen(name) - 1] = '\0'; // fgets() adds '\n' at the end so we need to remove it

  printf("Hello %s!", name);

  return 0;
}
