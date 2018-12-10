#include "RedBlack.h"
#include "AVL.h"

void TestRBTree() {
	cout << "--------- TESTING R-B TREE ---------" << endl;

	rbTree myTree;
	srand(time(NULL));

	cout << "------------------------------------" << endl;

	int values[] = { 4, 5, 3, 8, 0, 6, 15, 2, 1 };
	for (int i(0); i < sizeof(values) / sizeof(int); i++) {
		myTree.push(values[i]);
	}

	myTree.print();
	cout << "------------------------------------" << endl;

	cout << "Removing: " << endl;

	myTree.pop(5);
	myTree.print();
	cout << "------------------------------------" << endl;

	myTree.pop(4);
	myTree.print();
	cout << "------------------------------------" << endl;
	cout << endl << endl;
}

int main(){
	AVL avlTree;
	Node* root = nullptr;
	int values[] = { 4, 5, 3, 8, 0, 6, 15, 2, 1 };
	for (int i(0); i < sizeof(values) / sizeof(int); i++) {
		root = avlTree.insert(root, values[i]);	
	}
	avlTree.printTree(root);
	cout << endl << "-------------" << endl;

	avlTree.removeKey(root, 0);
	avlTree.printTree(root);
	cout << endl << "------------" << endl;
	avlTree.removeKey(root, 2);
	avlTree.printTree(root);
	cout << endl;

	TestRBTree();
	cin.get();
}