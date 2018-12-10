#include "RedBlack.h"

// --------------------------------------------

// Tree node constructor
rbTree::node::node(int _key, node *_parent, bool _isLeaf) :isLeaf(_isLeaf) {
	key = _key;
	parent = _parent;

	if (parent) {
		if (key < parent->key) parent->left = this;
		else parent->right = this;
	}

	if (isLeaf) {
		color = BLACK;
		left = right = NULL;
	}
	else {
		color = RED;
		left = new node(0, this, true), right = new node(0, this, true);
	}
}

// !!! Warning !!! Magic used, be cautious
void rbTree::node::print(int level) {
	if (this->isLeaf) return;

	// '-' fill for red nodes
	if (this->color == RED) {
		cout << setfill('-');
	}
	// '+' fill for black nodes
	else {
		cout << setfill('+');
	}

	// Set fixed width for output
	cout << setw(3) << this->key;

	// Print right subtree
	if (!this->right->isLeaf) {
		cout << "/--";
		this->right->print(level + 1);
	}
	else if (!this->left->isLeaf) {
		cout << "/--NIL";
	}


	// Print left subtree
	if (!this->left->isLeaf) {
		cout << endl;
		for (int i = 0; i < 2 * level + 1; i++) cout << "   ";

		cout << "\\--";
		this->left->print(level + 1);
	}
}

// --------------------------------------------

