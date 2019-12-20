#include <iostream>
#ifndef PEMDAS_H
#define PEMDAS_H

int findFirstSpecificOperator(std::string input, char op);

void addTogether(std::string &input, unsigned int operatorIndex, char op);

void equate(std::string &input, char op);

double PEMDAS(std::string input);

#endif // PEMDAS_H
