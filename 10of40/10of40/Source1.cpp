#include "Graph.h"

Graph::Graph() {

}

Graph::~Graph() {

}

Graph::Graph(ifstream& input) {
	input >> numVertex >> numEdges;

	incList.resize(numVertex);
	edgeArray = new Edge[numEdges];

	int currentEdge;
	int currentVertex;

	// creating incidence list implementation of the array // impletension is ðåàëèçàöèÿ
	for (int i(0); i < numEdges * 2; i++) {
		input >> currentEdge >> currentVertex;
		incList[currentVertex].push_back(currentEdge);
		pushEdge(currentEdge, currentVertex);
	}


}

void Graph::pushEdge(int currentEdge, int currentVertex) {
	if (edgeArray[currentEdge].from == -1)
		edgeArray[currentEdge].from = currentVertex;
	else
		edgeArray[currentEdge].to = currentVertex;
}

int Graph::getVertex(int currentEdge, int currentVertex) {
	if (edgeArray[currentEdge].from == currentVertex)
		return edgeArray[currentEdge].to;
	else
		return edgeArray[currentEdge].from;
}

void Graph::deleteSameEdge(int currentEdge, int currentVertex) {
	int anotherVertex = getVertex(currentEdge, currentVertex);
	for (int i = 0; i < incList[anotherVertex].size(); i++) {
		if (incList[anotherVertex][i] == currentEdge)
			incList[anotherVertex].erase(incList[anotherVertex].begin() + i);
	}
}

//http://e-maxx.ru/algo/euler_path
//stack St;
//â St êëàä¸ì ëþáóþ âåðøèíó(ñòàðòîâàÿ âåðøèíà);
//ïîêà St íå ïóñòîé
//ïóñòü V - çíà÷åíèå íà âåðøèíå St;
//åñëè ñòåïåíü(V) = 0, òî
//äîáàâëÿåì V ê îòâåòó;
//ñíèìàåì V ñ âåðøèíû St;
//èíà÷å
//íàõîäèì ëþáîå ðåáðî, âûõîäÿùåå èç V;
//óäàëÿåì åãî èç ãðàôà;
//âòîðîé êîíåö ýòîãî ðåáðà êëàä¸ì â St;

void Graph::findEulerCycle() {

	st.push(0);

	while (!st.empty()) {
		int V = st.top();
		if (incList[V].empty()) {
			resArray.push_back(V);
			st.pop();
		}
		else {
			//take the last edge for vertex V
			int tmpEdge = incList[V][incList[V].size() - 1];
			//delete it
			incList[V].pop_back();
			//push another vertex (not V, but neighbor V)
			st.push(getVertex(tmpEdge, V));
			deleteSameEdge(tmpEdge, V);
		}
	}
}

void Graph::printResult() {
	if (resArray.empty())
		cout << "No Euler cycle in the graph";
	else
		for (int i = 0; i < resArray.size() - 1; i++) {
			cout << resArray[i] << " -> " << resArray[i + 1] << ";" << endl;
		}
}