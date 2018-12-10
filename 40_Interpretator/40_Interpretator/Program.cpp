#include "Program.h"

string Program::exchange_variables(string expr) 
{
	//if there are variables in expr 
	//then exchange them by their values
	for (int i = 0; i < expr.size(); i++) {
		if ((expr[i] >= 'a' && expr[i] <= 'z') ||
			(expr[i] >= 'A' && expr[i] <= 'Z')) {
			char var = expr[i];
			expr.erase(i, 1);
			expr.insert(i, to_string(variables[var]));
		}
	}
	return expr;
}

void Program::parse()
{
	//the order in this array is significant
	char* relSigns[] = { ">=", "<=", "!=", "<", ">", "=" };
	char currLine[256];
	char* pos;
	while (source.getline(currLine, 256)) 
	{	
		if (pos = strstr(currLine, "#")) {
			string label;
			for (int i = 0; currLine[i] != '#'; i++)
				label += currLine[i];
			labels[stoi(label)] = source.tellg();
		}
		if (pos = strstr(currLine, "if")) 
		{
			char* relBeg = strstr(currLine, "(") + 1;
			char* relEnd = strstr(currLine, ")");
			for (int i = 0; i < 6; i++) {
				if (char* relation_pos = strstr(currLine, relSigns[i])) {
					string leftExpr = exchange_variables(string(relBeg, relation_pos));
					string rightExpr = exchange_variables(string(relation_pos + strlen(relSigns[i]), relEnd));
					int left = Expression(leftExpr).get_result();
					int right = Expression(rightExpr).get_result();
					if (strstr(currLine, "!=")) {
						if (left == right) goto endloop;
						else break;
					}
					if (strstr(currLine, "<=")) {
						if (left > right) goto endloop;
						else break;
					}
					if (strstr(currLine, ">=")) {
						if (left < right) goto endloop;
						else break;
					}
					if (strstr(currLine, "=")) {
						if (left != right) goto endloop;
						else break;
					}
					if (strstr(currLine, "<")) {
						if (left >= right) goto endloop;
						else break;
					}
					if (strstr(currLine, ">")) {
						if (left <= right) goto endloop;
						else break;
					}
				}
			}
		}
		if (pos = strstr(currLine, ":=")) {
			char varName = *(pos - 1);
			string onlyConstants = exchange_variables(string(pos + 2));
			Expression exp(onlyConstants);
			variables[varName] = exp.get_result();
		}
		if (pos = strstr(currLine, "go")) {
			string desireLebel = string(pos + 2);
			source.seekg(labels[stoi(desireLebel)]);
		}
		if (pos = strstr(currLine, "get")) 
		{
			int var;
			cin >> var;
			variables[*(pos + 4)] = var;
		}
		if (pos = strstr(currLine, "put")) 
		{
			char* strLiteral = pos + 4;
			if (*strLiteral == '$') {
				strLiteral++;
				while (*strLiteral != ')') {
					cout << *strLiteral;
					strLiteral++;
				}
			}
			else if (variables.count(*strLiteral))
				cout << variables[*strLiteral];
		}
		if (strstr(currLine, "finish"))	{
			system("pause");
			exit(0);
		}
	endloop:;
	}
}
