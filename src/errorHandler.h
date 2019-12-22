#include <iostream>
#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H
class EquationErrorFinder
{
public:
    EquationErrorFinder(std::string x);
    bool hasErrors();

private:
    std::string equation;
    bool hasInvalidCharacters();
    int getNumberOfInstances(char x);
    bool hasOpenParentheses();
    bool hasEmptyParentheses();
    void removetrigFxns();
};



#endif // ERRORHANDLER_H
