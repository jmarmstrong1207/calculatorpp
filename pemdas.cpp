#include <iostream>

// finds specific operators in a vector of all of the operators in the equation, then places them into another vector
int findFirstSpecificOperator(std::string input, char op)
{
    int specificOperatorIndex = 0;
    for (unsigned int i = 0; i < input.length(); i++)
    {
        if (input[i] == op)
        {
            specificOperatorIndex = i;
            break;
        }

        else if (i == input.length() - 1)
        {
            specificOperatorIndex = -1;
        }
    }

    return specificOperatorIndex;
}

// Gets left or right operand's beginning and last index, depending whether side is 'l' or 'r'
void getLeftAndRightIndex(std::string &input, unsigned int operatorIndex, unsigned int &leftIndex, unsigned int &rightIndex, char side)
{
    int i = 1;
    if (side == 'l')
    {
        while (static_cast<int>(operatorIndex - i) >= 0 && (isdigit(input[operatorIndex - i]) || input[operatorIndex - i] == '.'))
        {
            i++;
        }
        // the + 1 is to put it exactly at the start of the operand
        leftIndex = operatorIndex - i + 1;

        rightIndex = operatorIndex - 1;
    }
    else
    {
        while (operatorIndex + i < input.size() && (isdigit(input[operatorIndex + i]) || input[operatorIndex + i] == '.'))
        {
            i++;
        }

        leftIndex = operatorIndex + 1;

        // the - 1 is to put it exactly at the end of the operand
        rightIndex = operatorIndex + i - 1;
    }
}

// adds operands of a single and specific operator, then replaces the operation with the answer (e.g. "5 * 2 * 3 - 2" -> "10 * 3 - 2")
void addTogether(std::string &input, unsigned int operatorIndex, char op)
{

    unsigned int leftOperandLeftIndex = 0;
    unsigned int leftOperandRightIndex = 0;
    getLeftAndRightIndex(input, operatorIndex, leftOperandLeftIndex, leftOperandRightIndex, 'l');

    unsigned int rightOperandLeftIndex = 0;
    unsigned int rightOperandRightIndex = 0;
    getLeftAndRightIndex(input, operatorIndex, rightOperandLeftIndex, rightOperandRightIndex, 'r');

    double leftOperand = std::stod(input.substr(leftOperandLeftIndex, leftOperandRightIndex - leftOperandLeftIndex + 1));
    double rightOperand = std::stod(input.substr(rightOperandLeftIndex, rightOperandRightIndex - rightOperandLeftIndex + 1));

    input.erase(leftOperandLeftIndex, rightOperandRightIndex - leftOperandLeftIndex + 1);

    if (op == '*')
    {
        input.insert(leftOperandLeftIndex, std::to_string(leftOperand * rightOperand));
    }
    else if (op == '/')
    {
        input.insert(leftOperandLeftIndex, std::to_string(leftOperand / rightOperand));
    }
    else if (op == '+')
    {
        input.insert(leftOperandLeftIndex, std::to_string(leftOperand + rightOperand));
    }
    else
    {
        input.insert(leftOperandLeftIndex, std::to_string(leftOperand - rightOperand));
    }
}

double PEMDAS(std::string input);

// Solves the equation within the parenthesis
void parenthesisEquate(std::string &input, unsigned int leftPIndex)
{
    std::string equationInsideParenthesis;

    // find right parenthesis
    unsigned int rightPIndex = 0;
    int i = input.size() - 1;
    while (input[i] != ')')
    {
        i--;
    }
    rightPIndex = i;

    equationInsideParenthesis = input.substr(leftPIndex + 1, rightPIndex - leftPIndex - 1);

    // PEMDAS() includes parenthesis, so it essentially does recursion if there are nested parentheses
    std::string equationAnswer = std::to_string(PEMDAS(equationInsideParenthesis));

    input.erase(leftPIndex, rightPIndex - leftPIndex + 1);
    input.insert(leftPIndex, equationAnswer);

}

// Solves the equation by going through only one operator type, and simplifying the result of each operation of that type to a number.
// (e.g, op = '*' and input = "5 * 2 * 3 - 2". input becomes "30 - 2"). It doesn't do subtraction, only multiplication.
void equate(std::string &input, char op)
{
    int index = 0;

    bool keepGoing = true;

    while (keepGoing)
    {
        index = findFirstSpecificOperator(input, op);

        if (index != -1 && op == '(') parenthesisEquate(input, index);
        else if (index != -1) addTogether(input, index, op);
        else keepGoing = false;
    }
}

// Order is PEMDAS
// It starts from the first multiplication operator from the left, then multiplies its operands. It repeats for the 2nd, 3rd, etc.
// It does the same thing for the other operators.
double PEMDAS(std::string input)
{

    equate(input, '(');

    equate(input, '*');
    equate(input, '/');
    equate(input, '+');
    equate(input, '-');

    return stod(input);
}
