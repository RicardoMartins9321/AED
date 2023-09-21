#include <iostream>

int main()
{
  //std::string students[] = {"Spongebob", "Patrick", "Squidward", "Sandy"};
  char grades[] = {'A', 'B', 'C', 'D', 'F'};
  std::string students[] = {"Spongebob", "Patrick", "Squidward", "Sandy"};

  // we can use sizeof() to determine the number of elements in an array in bytes
  // and then divide that number by the size of the first element in the array
  // because
  for(int i = 0; i < sizeof(grades)/sizeof(grades[0]); i++){
      std::cout << grades[i] << '\n';
  }

  // sizeof(students)/sizeof(students[0]) also works
  for(int i = 0; i < sizeof(students)/sizeof(std::string); i++){
      std::cout << students[i] << '\n';
  }

  for(std::string student : students){
      std::cout << student << '\n';
  }


  // memory address = a location in memory where data is stored
  // a memory address can accessed with & (address-of operator)

  std::string name = "Bro";
  int age  = 21;
  bool student = true;

  std::cout << &name << '\n';
  std::cout << &age << '\n';
  std::cout << &student << '\n';


  std::string x = "Kool-Aid";
	std::string y = "Water";

	swap(x, y);

	std::cout << "X: " << x << '\n';
	std::cout << "Y: " << y << '\n';


  // pointers = variable that stores a memory address of another variable
  //                    sometimes it's easier to work with an address

  // & address-of operator
  // * dereference operator

  std::string name2 = "Bro";
  int age2 = 21;
  std::string freePizzas[5] = {"pizza1", "pizza2", "pizza3", "pizza4", "pizza5"};

  std::string *pName = &name2;
  int *pAge = &age2;
  // arrays are already pointers so we don't need to use the address-of operator &
  std::string *pFreePizzas = freePizzas;

  std::cout << *pName << '\n';
  std::cout << *pAge << '\n';
  std::cout << *pFreePizzas << '\n';


  int *pointer2 = nullptr;
  int x2 = 123;

  pointer2 = &x2;

  if(pointer2 == nullptr){
      std::cout << "address was not assigned!\n";
  }
  else{
      std::cout << "address was assigned!\n";
      std::cout << *pointer2;
  }


  char *pGrades = NULL;
  int size;

  std::cout << "How many grades to enter in?: ";
  std::cin >> size;

  pGrades = new char[size]; // dynamically allocate memory for an array

  for(int i = 0; i < size; i++){
      std::cout << "Enter grade #" << i + 1 << ": ";
      std::cin >> pGrades[i];
  }

  for(int i = 0; i < size; i++){
      std::cout << pGrades[i] << " ";
  }

  delete[] pGrades; // delete the array when we're done with it to free up memory

  return 0;
}

// pass by reference works by passing a reference to the memory address of the argument
// while pass by value works by passing a copy of the argument which is stored in a different memory address
// pass by reference is more efficient because it doesn't require copying the argument
void swap(std::string &x, std::string &y){
	std::string temp;
	temp = x;
	x = y;
	y = temp;
}
