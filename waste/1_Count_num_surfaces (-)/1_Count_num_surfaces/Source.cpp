#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
using namespace std;
struct Rect {
	double xBegin;
	double yBegin;
	double xEnd;
	double yEnd;
};
int main()
{
	int n;
	ifstream input("Text.txt");
	input >> n;
	int count = 0;//number of section
	int res = 0;//total number of section
	vector<Rect> m;
	Rect  pt;
	for (int i(0); i < n; i++)
	{
		input >> pt.xBegin >> pt.yBegin >> pt.xEnd >> pt.yEnd;
		m.push_back(pt);
	}
	sort(m.begin(), m.end(), [](Rect a, Rect b)->bool//sort by x
	{
		return a.xBegin<b.xBegin;
	});
	for (int i(0); i<m.size(); i++){ //counting section sorted for beginning
		count = 0;
		for (int j(0); j < i; j++){
			if (m[j].xBegin <= m[i].xBegin&&m[j].xEnd >= m[i].xBegin) // case intersection of 2 rectangles 
			{
				if (m[j].yBegin <= m[i].yBegin&&m[j].yBegin >= m[i].yEnd) ++count; // if a new rectangle is lower than current
				if (m[j].yEnd <= m[i].yBegin&&m[j].yEnd >= m[i].yEnd) ++count; // upper than current
			}
		}
		if (count>0) // note that i and j are same elements
			res += count - 1;
	}
	for (int i(0); i<m.size(); i++){ // counting surfaces comparing rectangles from the end 
		count = 0;
		for (int j(0); j < n; j++){ // checking every rect
			if (m[j].xBegin <= m[i].xEnd&&m[j].xEnd >= m[i].xEnd)
			{
				if (m[j].yBegin <= m[i].yBegin&&m[j].yBegin >= m[i].yEnd) ++count; // lower case j is lower than i
				if (m[j].yEnd <= m[i].yBegin&&m[j].yEnd >= m[i].yEnd) ++count; // upper: j is higher than i
			}
		}
		if (count>0)
			res += count - 1;
	}
	cout << res + 1 << endl;
	system("pause");
	return 0;
}