#include "words.h"

bool isEditionStep(string first, string second)
{
	string result;
	sort(first.begin(), first.end());
	sort(second.begin(), second.end());
	set_intersection(first.begin(), first.end(), second.begin(), second.end(), inserter(result,result.begin()));
	int maxLen = max(first.length(), second.length());
	if (maxLen - result.length() != 1) return false;
	return true;
}

void word::addStep(word *newStep) {
	string first = val, second = newStep->val;
	
	int balance = first.compare(second);
	
	if (balance < 0) {
		steps.push_back(newStep);
	}
	else {
		newStep->steps.push_back(this);
	}
}

bool word::isStep(word *another) {
	string first = this->val, second = another->val;

	return isEditionStep(first, second);
}

word::word(string _val) {
	val = _val;
}

string &word::getVal() {
	return this->val;
}
word* word::getStep(int index) {
	return steps.at(index);
}
int word::getStepsLen() {return steps.size();}

vector<int> getPath(vector<int> &parents, int from, int to) {
	vector<int> res;
	while (parents.at(to) != -1) {
		res.insert(res.begin(), to);
		to = parents.at(to);
	}
	res.insert(res.begin(), to);
	return res;
};

//
// 'Vocabulary' class
//

vocabulary::vocabulary(string filename) {
	len = 0;

	ifstream in(filename);
	string current;
	
	while (!in.eof()) {
		getline(in, current);

		addWord(current);
	}
}
int vocabulary::getStrPos(const string &str) {
	for (int i = 0; i < len; i++) {
		if (!str.compare(contents.at(i)->getVal())) return i;
	}
}

// Adds word to vocabulary
void vocabulary::addWord(string nword) {
	word *newWord = new word(nword);
	for (int i = 0; i < len; i++) {
		if (newWord->isStep(contents.at(i))) {
			newWord->addStep(contents.at(i));
		}
	}
	contents.push_back(newWord);
	len++;
}
void getMaxWay(vocabulary &src){

	vector<vector<int>> matrix(src.len, vector<int>(src.len, 0));
	
	// Transform vocabulary into graph
	for (int i = 0; i < src.len; i++) {
		word *cur = src.contents.at(i);
		for (int j = 0; j < cur->getStepsLen(); j++) {
			word *step = cur->getStep(j);
			int num = src.getStrPos(step->getVal());
			matrix.at(i).at(num) = 1;
		}
	}

	// Used to store maximal way
	vector<int> maxWay;


	// Start Djikstra from every vertex 
	// and find the longest way

	int vNum = matrix.size();

	for (int i = 0; i < vNum; i++) {

		vector<bool> used(vNum, false);
		vector<int> marks(vNum, 0);
		marks.at(i) = 1;

		vector<int> parents(vNum, -1);

		for (int j = 0; j < vNum; j++) {
			int cur = -1;
			// Select unused vertex with maximal mark
			for (int k = 0; k < vNum; k++) {
				if (!used.at(k) && (cur == -1 || marks.at(k) > marks.at(cur)))
					cur = k;
			}

			// Mark current vertex as used
			used.at(cur) = true;

			// Refresh marks
			for (int to = 0; to < vNum; to++) {
				// Get edge
				int edge = matrix.at(cur).at(to);
				// If edge exists
				if (edge) {
					// If cur.mark + edge >= to.mark
					// make 'cur' parent for 'to'
					// and refresh mark
					if (edge + marks.at(cur) >= marks.at(to)) {
						marks.at(to) = edge + marks.at(cur);
						parents.at(to) = cur;
					}
				}
			}
		}


		// Select farthest vertex
		int cur = 0;
		for (int k = 0; k < vNum; k++) {
			if (marks.at(k) > marks.at(cur))
				cur = k;
		}

		// Vector 'Parents' stores our way,
		// variable 'cur' stores farthest vertex
		// use func to get way from 'i' to 'cur'
		vector<int> path = getPath(parents, i, cur);

		if (path.size() > maxWay.size()) maxWay = path;
	}
	
	// Print maximal ladder

	for (int i = 0; i < maxWay.size(); i++) {
		cout << src.contents.at(maxWay.at(i))->getVal() << "; ";
	}
	cout << endl;
}