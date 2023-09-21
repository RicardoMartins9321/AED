#include <iostream>

// function prototype
int factorial(int num);

// struct = data structure that allows us to store different data types
//                in a single variable
//                (similar to a class)
struct Car{
    std::string model;
    int year;
    std::string color;
};

void printCar(Car &car);
void paintCar(Car &car, std::string color);


int main () {
  int num;

  std::cout << "Write the number you want to calculate the factorial of: ";
  std::cin >> num;
  std::cout << "The factorial of " << num << " is: " << factorial(num) << '\n';


   Car car1;
    Car car2;

    car1.model = "Mustang";
    car1.year = 2023;
    car1.color = "red";

    car2.model = "Corvette";
    car2.year = 2024;
    car2.color = "blue";

    paintCar(car1, "silver");
    paintCar(car2, "gold");

    printCar(car1);
    printCar(car2);

  return 0;
}

void printCar(Car &car){
    std::cout << car.model << '\n';
    std::cout << car.year << '\n';
    std::cout << car.color << '\n';
}
void paintCar(Car &car, std::string color){
    car.color = color;
}

// recursive function
int factorial(int num){
  if(num > 1){
      return num * factorial(num - 1);
  }
  else{
      return 1;
  }
}
