#include <iostream>
#include "calcParser.h"
#include "errorHandler.h"
int main()
{
    std::string input;
    std::getline(std::cin, input);
    std::cout << std::endl;

    if (!hasErrors(input))
    {
        calcParser(input);
    }
    else
    {
        std::cout << "Invalid input. Try again" << std::endl;
    }
    return 0;
}
