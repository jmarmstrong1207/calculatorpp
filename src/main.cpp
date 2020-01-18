#include <iostream>
#include "equation.h"
#include <unistd.h>

int main()
{
      std::string input;

      std::cout << "Enter equation: " << std::endl;

      std::getline(std::cin, input);
      std::cout << std::endl;

      Equation x(input);
      try
      {
        std::cout << "Answer: " << x.calculate() << std::endl;
      }
      catch (std::invalid_argument)
      {
        std::cout << "The input is invalid.";
      }


    return 0;
}
