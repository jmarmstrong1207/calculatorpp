#include <iostream>
#include <cmath>
#include "equation.h"

Equation::Equation(std::string x)
{
    equation = x;

    removeWhitespace();
    furthestLeftPIndex = -1;
    furthestLeftPIndex = -1;

    firstTrigIndex = locateTrigIndex(equation);
}

void Equation::removeWhitespace()
{
    for (int i = 0; i < equation.length(); i++)
    {
        if (equation[i] == ' ')
        {
            equation.erase(i, 1);
        }
    }
}

// finds specific operators in a vector of all of the operators in the equation, then places them into another vector
int Equation::findFirstSpecificOperator(char op)
{
    int specificOperatorIndex = 0;
    for ( int i = 0; i < equation.length(); i++)
    {
        if (equation[i] == op)
        {
            specificOperatorIndex = i;
            break;
        }

        else if (i == equation.length() - 1)
        {
            specificOperatorIndex = -1;
        }
    }

    return specificOperatorIndex;
}

// Gets left or right operand's beginning and last index, depending whether side is 'l' or 'r'
void Equation::getLeftAndRightIndex(int operatorIndex, int &leftIndex, int &rightIndex, char side)
{
    int i = 1;
    if (side == 'l')
    {
        while (static_cast<int>(operatorIndex - i) >= 0 && (isdigit(equation[operatorIndex - i]) || equation[operatorIndex - i] == '.'))
        {
            i++;
        }

        // There is only a check for the left side, because equations can start with a negative (e.g. -1 + 2),
        // and we need to know that so we can tell this program about it. The right side doesnt have this check
        // because "1 + 2-" is not valid, so the program will naturally crash trying to convert it to a double.
        if (static_cast<int>(operatorIndex - i) == -1 && equation[0] == '-')
        {
            leftIndex = -1;
            rightIndex = -1;
        }
        else
        {
            // the + 1 is to put it exactly at the start of the operand
            leftIndex = operatorIndex - i + 1;
            rightIndex = operatorIndex - 1;
        }
    }
    else
    {
        while (operatorIndex + i < equation.size() && (isdigit(equation[operatorIndex + i]) || equation[operatorIndex + i] == '.'))
        {
            i++;
        }

        leftIndex = operatorIndex + 1;

        // the - 1 is to put it exactly at the end of the operand
        rightIndex = operatorIndex + i - 1;
    }
}

// adds operands of a single and specific operator, then replaces the operation with the answer (e.g. "5 * 2 * 3 - 2" -> "10 * 3 - 2")
void Equation::addTogether(int operatorIndex, char op)
{
    int leftOperandLeftIndex = 0;
    int leftOperandRightIndex = 0;
    getLeftAndRightIndex(operatorIndex, leftOperandLeftIndex, leftOperandRightIndex, 'l');

    int rightOperandLeftIndex = 0;
    int rightOperandRightIndex = 0;
    getLeftAndRightIndex(operatorIndex, rightOperandLeftIndex, rightOperandRightIndex, 'r');


    double leftOperand = 0;
    double rightOperand = 0;

    // If there is no left operand, we will assume it is "-x + y". If it's something like "+x +y", it'll naturally crash.
    if (leftOperandLeftIndex == -1)
    {
        // This turns the left operand into the right operand, including the negative
        leftOperandLeftIndex = rightOperandLeftIndex - 1;
        leftOperandRightIndex = rightOperandRightIndex;

        getLeftAndRightIndex(leftOperandRightIndex + 1, rightOperandLeftIndex, rightOperandRightIndex, 'r');
    }
    leftOperand = std::stod(equation.substr(leftOperandLeftIndex, leftOperandRightIndex - leftOperandLeftIndex + 1));
    rightOperand = std::stod(equation.substr(rightOperandLeftIndex, rightOperandRightIndex - rightOperandLeftIndex + 1));

    equation.erase(leftOperandLeftIndex, rightOperandRightIndex - leftOperandLeftIndex + 1);
    if (op == '^') equation.insert(leftOperandLeftIndex, std::to_string(pow(leftOperand, rightOperand)));
    else if	(op == '*') equation.insert(leftOperandLeftIndex, std::to_string(leftOperand * rightOperand));
    else if (op == '/') equation.insert(leftOperandLeftIndex, std::to_string(leftOperand / rightOperand));
    else if (op == '+') equation.insert(leftOperandLeftIndex, std::to_string(leftOperand + rightOperand));
    else equation.insert(leftOperandLeftIndex, std::to_string(leftOperand - rightOperand));
}

// determine if string is just a double
bool Equation::isNumber()
{
    for (int i = 0; i < equation.size(); i++)
    {
        if (!isdigit(equation[i]) && equation[i] != '.' && i != 0 && equation[i] != '-')
        {
            return false;
        }
    }
    return true;
}

// Solves the equation by going through only one operator type, and simplifying the result of each operation of that type to a number.
// (e.g, op = '*' and equation = "5 * 2 * 3 - 2". input becomes "30 - 2"). It doesn't do subtraction, only multiplication.
void Equation::equate(char op)
{
    int index = 0;

    bool keepGoing = true;

    while (keepGoing)
    {
        index = findFirstSpecificOperator(op);

        if (index != -1) addTogether(index, op);
        else keepGoing = false;
    }
}

int Equation::findFurthestRightParenthesisIndex()
{
    int i = equation.size() - 1;
    while (i >= 0 && equation[i] != ')')
    {
        i--;
        if (i == 0 && equation[i] != ')')
        {
            return -1;
        }
    }
    return i;
}

// get the entire equation inside parentheses
std::string Equation::getLargestParenthesisEquation()
{
    return equation.substr(furthestLeftPIndex + 1, furthestRightPIndex - furthestLeftPIndex - 1);
}

void Equation::replaceLargestParenthesisEquation(std::string equationAnswer)
{
    equation.erase(furthestLeftPIndex, furthestRightPIndex - furthestLeftPIndex + 1);
    equation.insert(furthestLeftPIndex, equationAnswer);
}

// Solves the equation within the largest parenthesis
void Equation::largestParenthesisEquate()
{
    Equation equationInsideParenthesis(getLargestParenthesisEquation());

    // calculate() includes parenthesis, so it essentially does recursion if there are nested parentheses
    std::string equationAnswer = std::to_string(equationInsideParenthesis.calculate());
    replaceLargestParenthesisEquation(equationAnswer);
}


int Equation::getNextCorrespondingParenthesisIndex(std::string equation, int leftPIndex)
{
    if (leftPIndex >= 0)
    {
        for (int i = leftPIndex; i < equation.size(); i++)
        {
            if (equation[i] == ')')
            {
                int leftPCount = 0;
                int rightPCount = 0;
                for (int j = 0; j <= i ; j++)
                {
                    if (equation[j] == '(') leftPCount++;
                    if (equation[j] == ')') rightPCount++;
                }
                if (leftPCount == rightPCount) return i;
            }
        }
    }
    return -1;
}


double Equation::equateStringTrig(std::string trigFxn, double num)
{
    if (trigFxn == "sin") return sin(num);
    if (trigFxn == "cos") return cos(num);
    if (trigFxn == "tan") return tan(num);
    if (trigFxn == "tan") return tan(num);
    if (trigFxn == "tan") return tan(num);
}

// find the index of the first letter of the trig fxn. If not, return -1
int Equation::locateTrigIndex(std::string equation)
{
    for (int i = 0; i < static_cast<int>(equation.size()) - 2; i++)
    {
        std::string substring = equation.substr(i, 3);
        if (substring == "sin" || substring == "cos" || substring == "tan")
        {
            return i;
        }
    }
    return -1;
}

int Equation::getNextRightParenthesisIndex(std::string equation, int leftPIndex)
{
    for (int i = leftPIndex; i < static_cast<int>(equation.size()) - 2; i++)
    {
        if (equation[i] == ')') return i;
    }
    return -1;
}
// Simplifies trig functions like sin(5)
void Equation::equateFirstTrig()
{
    int leftPIndex = firstTrigIndex + 3;
    int rightPIndex = Equation::getNextCorrespondingParenthesisIndex(equation, leftPIndex);

    // e.g. "sin"
    int beginningOfNum = leftPIndex + 1;
    int endOfNum = rightPIndex - 1;

    std::string trigFxn = equation.substr(firstTrigIndex, 3);

    Equation inside(equation.substr(beginningOfNum, endOfNum - beginningOfNum + 1));

    double insideAns = inside.calculate();

    std::string ans = std::to_string(equateStringTrig(trigFxn, insideAns));
    equation.erase(firstTrigIndex, rightPIndex - firstTrigIndex + 1);
    equation.insert(firstTrigIndex, ans);
}

// It starts from the first multiplication operator from the left, then multiplies its operands. It repeats for the 2nd, 3rd, etc.
// It does the same thing for the other operators.
double Equation::calculate()
{
    // the if statements repeat itself so if it is already simplified in the middle of all of this, the program doesn't have to
    // do any more unnecessary functions
    if (!isNumber())
    {
        if (firstTrigIndex != -1) equateFirstTrig();
    }

    furthestLeftPIndex = findFirstSpecificOperator('(');
    furthestRightPIndex = findFurthestRightParenthesisIndex();
    if (!isNumber()) if (furthestLeftPIndex != -1) largestParenthesisEquate();
    if (!isNumber()) equate('^');
    if (!isNumber()) equate('*');
    if (!isNumber()) equate('/');
    if (!isNumber()) equate('+');
    if (!isNumber()) equate('-');
    return stod(equation);
}
