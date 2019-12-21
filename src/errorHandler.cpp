#include <iostream>

bool hasInvalidCharacters(std::string input)
{
    for (char x : input)
    {
        if ( (!isdigit(x) && x != '.') && (x != '*' && x != '/' && x != '+' && x != '-')  && x != ' ' && x != '(' && x != ')') return true;
    }
    return false;
}

// Returns number of instances of a character in a string
int getInstances(std::string input, char x)
{
    int sum = 0;
    for (char i : input)
    {
        if (i == x)
        {
            sum++;
        }
    }
    return sum;
}
// Counts # of left and right parenthesis. If not equal, there are errors
bool openParentheses(std::string input)
{
    return getInstances(input, '(') != getInstances(input, ')');
}

bool emptyParentheses(std::string input)
{
    return static_cast<int>(input.size()) == getInstances(input, '(') + getInstances(input, ')');
}

bool hasErrors(std::string input)
{
    return hasInvalidCharacters(input) || openParentheses(input) || emptyParentheses(input);
}
