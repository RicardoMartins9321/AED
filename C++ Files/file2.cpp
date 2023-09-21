#include <iostream>

// cout << (insertion operator)
// cin >> (extraction operator)

void happyBirthday(std::string name, int age);

int myNum = 3; //global
void printNum();

int main()
{
  std::string name;
  int age;

  std::cout << "What's your full name? ";
  // getline() is a function that reads a line of text from an input stream
  std::getline(std::cin >> std::ws, name); // std::ws is a stream manipulator that discards leading whitespace

  std::cout << "What's your age? ";
  std::cin >> age;  // cin will stop reading at the first whitespace character it encounters

  std::cout << "Hello " << name << '\n';
  std::cout << "You are " << age << " years old" << '\n';


  std::string name2 = "Bro";
  int age2 = 21;

  happyBirthday(name2, age2);


  int myNum = 1; //local
  printNum();
  std::cout << "main: " << myNum << '\n'; //local
  std::cout << ::myNum << '\n'; // global because of the scope resolution operator (::)



  return 0;
}

void happyBirthday(std::string name, int age)
{
  std::cout << "Happy Birthday " << name << "!\n";
  std::cout << "You are now " << age << " years old!\n";
}

void printNum(){
    int myNum = 2; //local
    std::cout << "printNum: "<< myNum << '\n'; //local
    //std::cout << ::myNum << '\n'; //global
}
