#include <iostream>

namespace first{
    int x = 1;
}
namespace second{
    int x = 2;
}

int main() {
    std::cout << "I like pizza!" << '\n';
    std::cout << "It's really good!";
    std::cout << "I like bananas!" << '\n';


    int x = 0;

    std::cout << x;
    std::cout << first::x;
    std::cout << second::x;


  // Typedefs and type aliases
  // typedef = reserved keyword used to create an additional name
  //                  (alias) for another data type.
  //                  New identifier for an existing type
  //                  Helps with readability and reduces typos
  //                  Use when there is a clear benefit
  //                  Replaced with 'using' (work better w/ templates)

  //typedef std::string text_t;
  //typedef int number_t;
  using text_t = std::string;
  using number_t = int;

  text_t firstName = "Bro";
  number_t age = 21;

  std::cout << firstName << '\n';
  std::cout << age << '\n';

    return 0;
}


