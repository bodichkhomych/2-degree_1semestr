#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
	int n;
cin >> n;
vector<double> x(n);
vector<double> y(n);
for (int i = 0; i < n; i++) {
	cin >> x[i] >> y[i];
}
const double INF = 1e10;
vector <double> dist2(n, INF);
dist2[0] = 0;
vector<bool> connected(n, false);
double maxEdge2 = 0;
while (true) {
	double minDist2 = INF;
	int cur = -1;
	for (int i = 0; i < n; i++) {
		if (!connected[i] && dist2[i] < minDist2) {
			minDist2  = dist2[i];
			cur = i;
		}
	}
	if (cur == -1) { 
		break;
	}
	maxEdge2 = max(maxEdge2, dist2[cur]);
		connected[cur] = true;
	for (int i = 0; i < n; i++) {
		if (!connected[i]) {
			double dx = x[i] - x[cur];
			double dy = y[i] - y[cur];
			double d2 = dx * dx + dy * dy;
			if (d2 < dist2[i]) {
				dist2[i] = d2;
			}
		}
	}
}
 printf("%.2f", sqrt(maxEdge2));
 system("pause");
 return 0;
}