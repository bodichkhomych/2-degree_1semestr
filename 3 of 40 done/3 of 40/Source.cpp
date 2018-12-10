#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

int main(int argc, const char * argv[]) {

	//f-front b-back k-to_us o-from_us

	cout << "Enter the fold order:" << endl;

	string input;
	getline(cin, input);
	vector<int> answer;
	char prevstep = input[0];

	while (input.length() > 1) {
		if (prevstep == input[0]) {
			if (answer.empty() == false) {
				answer.push_back(answer.back()*(1));
			}
			else {
				answer.push_back(1);
			}
		}
		else {
			answer.push_back(answer.back()*(-1));
		}

		prevstep = input[0];
		char previous = NULL;

		if (input.length() % 2 == 0) {
			cout << "There are no such fold order";
			return 0;
		}
		for (int i = 0; i < input.length(); i++) {
			if (input[i] == previous) {
				cout << "There are no such fold order";
				return 0;
			}
			previous = input[i];
			input.erase(i, 1);
		}
	}

	if (input[0] == prevstep) {
		answer.push_back(answer.back()*(-1));
	}
	else {
		answer.push_back(answer.back()*(1));
	}

	if (input[0] == 'o') {
		for (long i = answer.size() - 1; i >= 0; i--) {
			//            cout << "ans " << answer.back() << " - ansi " << answer[i] << endl;
			if (answer[i] == answer.back()) {
				cout << "f";
			}
			else {
				cout << "b";
			}
		}
	}
	else {
		for (long i = answer.size() - 1; i >= 0; i--) {
			if (answer[i] == answer.back()) {
				cout << "b";
			}
			else {
				cout << "f";
			}
		}
	}

	return 0;
	system("pause");
}
