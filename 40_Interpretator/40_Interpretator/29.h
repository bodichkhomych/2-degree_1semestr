#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cmath>
using namespace std;

int priority(char a);

string reversePolishNotation(string expression);

int calculate(string postfixNotation);