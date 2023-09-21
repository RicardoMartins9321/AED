#include <iostream>

class Car{
  public:
    std::string make;
    std::string model;
    int year;
    std::string color;

    void accelerate(){
        std::cout << "You step on the gas!\n";
    }
    void brake(){
        std::cout << "You step on the brakes!\n";
    }

  Car(std::string make, std::string model, int year, std::string color){
    this->make = make;
    this->model = model;
    this->year = year;
    this->color = color;
  }
};


class Stove{
  private:
    int temperature = 0;
  public:

  int getTemperature(){
    return temperature;
  }
  void setTemperature(int temperature){
    if(temperature < 0){
      this->temperature = 0;
    }
    else if(temperature >= 10){
      this->temperature = 10;
    }
    else{
      this->temperature = temperature;
    }
  }
};


class Animal{
  public:
    bool alive = true;

  void eat(){
    std::cout << "This animal is eating\n";
  }
};
class Dog : public Animal{
  public:

  void bark(){
    std::cout << "The dog goes woof!\n";
  }
};
class Cat : public Animal{
  public:

  void meow(){
    std::cout << "The cat goes meow!\n";
  }
};

int main() {
  //constructor =  special method that is automatically called when an object is instantiated
	//                      useful for assigning values to attributes as arguments

  Car car1("Chevy", "Corvette", 2022, "blue");
  Car car2("Ford", "Mustang", 2023, "red");

  std::cout << car1.make << '\n';
  std::cout << car1.model << '\n';
  std::cout << car1.year << '\n';
  std::cout << car1.color << '\n';

  car1.accelerate();
  car1.brake();



  Stove stove;

  stove.setTemperature(5);

  std::cout << "The temperature setting is: " << stove.getTemperature();



  Dog dog;
  Cat cat;

  std::cout << dog.alive << '\n';
  dog.eat();
  dog.bark();

  return 0;
}
