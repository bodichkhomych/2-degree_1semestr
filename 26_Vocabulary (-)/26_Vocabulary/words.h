#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

typedef vector<int> way;

bool isEditionStep(string first, string second);

class word {
	string val;
	vector<word*> steps;
public:
	word(string _val);

	string &getVal();
	word *getStep(int index);
	int getStepsLen();

	void addStep(word *newStep);
	bool isStep(word *another);
};

class vocabulary {
public:
	vector<word*> contents;
	int len;

	void addWord(string nword);
	vocabulary(string filename);

	int getStrPos(const string &str);
};

void getMaxWay(vocabulary &src);