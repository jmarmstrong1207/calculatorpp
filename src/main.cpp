#include <iostream>
#include "errorHandler.h"
#include "equation.h"
#include <unistd.h>

int main()
{
      std::string input;
      std::getline(std::cin, input);
      std::cout << std::endl;

      Equation x(input);

      std::cout << "Answer: " << x.calculate() << std::endl;


    return 0;
}
