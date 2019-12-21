#include <iostream>
#include <vector>
#include <cctype>
#include "calcParser.h"
#include "pemdas.h"

void removeWhitespace(std::string &input)
{
    for (unsigned int i = 0; i < input.length(); i++)
    {
        if (input[i] == ' ')
        {
            input.erase(i, 1);
        }
    }
}

double calcParser(std::string input)
{

    removeWhitespace(input);

    std::vector<unsigned int> operatorIndices;
    std::cout << "Answer: " << PEMDAS(input) << std::endl;

    return 5;
}
