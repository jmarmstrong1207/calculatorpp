#include <iostream>
#include "errorHandler.h"
#include "equation.h"

EquationErrorFinder::EquationErrorFinder(std::string x)
{
    equation = x;
}

bool EquationErrorFinder::hasInvalidCharacters()
{
    for (char x : equation)
    {
        if ( (!isdigit(x) && x != '.') && (x != '*' && x != '/' && x != '+' && x != '-')  && x != ' ' && x != '(' && x != ')') return true;
    }
    return false;
}

// Returns number of instances of a character in a string
int EquationErrorFinder::getNumberOfInstances(char x)
{
    int sum = 0;
    for (char i : equation)
    {
        if (i == x)
        {
            sum++;
        }
    }
    return sum;
}

// Counts # of left and right parenthesis. If not equal, there are errors
bool EquationErrorFinder::hasOpenParentheses()
{
    return getNumberOfInstances('(') != getNumberOfInstances(')');
}

bool EquationErrorFinder::hasEmptyParentheses()
{
    return static_cast<int>(equation.size()) == getNumberOfInstances('(') + getNumberOfInstances(')');
}

// Makes it easier to parse the equation for errors
void EquationErrorFinder::removetrigFxns()
{
    unsigned int firstIndex = Equation::locateTrigIndex(equation);
    unsigned int lastIndex = Equation::getNextCorrespondingParenthesisIndex(equation, firstIndex + 3);

    if (firstIndex != -1 && firstIndex != -1)
    {
        equation.erase(firstIndex, lastIndex - firstIndex + 1);
        equation.insert(firstIndex, "0");
    }
}

bool EquationErrorFinder::hasErrors()
{
    removetrigFxns();
    return hasInvalidCharacters() || hasOpenParentheses() || hasEmptyParentheses();
}
