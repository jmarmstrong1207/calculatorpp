#include <iostream>
#ifndef EQUATION_H
#define EQUATION_H


class Equation
{
private:
    std::string equation;
    int furthestLeftPIndex;
    int furthestRightPIndex;
    int firstTrigIndex;

    void removeWhitespace();

    int findFirstSpecificOperator(char op);

    void getLeftAndRightIndexOfOperand(int operatorIndex, int &leftIndex, int &rightIndex, char side);

    void addOperandsTogether(int operatorIndex, char op);

    bool isNumber();

    void equateAllCertainOperators(char op);

    int findFurthestRightParenthesisIndex();

    std::string getLargestParenthesisEquation();

    void replaceLargestParenthesisEquation(std::string equationAnswer);

    void largestParenthesisEquate();

    double determineTrigFxnAndEquate(std::string trigFxn, double num);

    void equateFirstTrig();

public:

    Equation(std::string x);

    double calculate();
    static int locateTrigIndex(std::string equation);
    static int getNextCorrespondingParenthesisIndex(std::string equation, int leftPIndex);
    static int getNextRightParenthesisIndex(std::string equation, int leftPIndex);
};
#endif // EQUATION_H
