#pragma once
#include <string>
using namespace std;

class Operator
{
public:
	Operator(string l) { if (!l.empty()) line = l; };
	virtual void evaluate() = 0;
	//~Operator() {line.~basic_string};
private:
	string line;
};

