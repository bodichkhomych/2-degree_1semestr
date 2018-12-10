//#pragma once
//
//template<typename T>
//class RBTree {
//private:
//	enum Color(Red, Black);
//	struct Node {
//		T key;
//		Color color;
//		Node* left;
//		Node* right;
//		Node* parent;
//
//		Node() :left(nullptr), right(nullptr), parent(nullptr), color(Black){};
//		Node(Color _color, T _key) :color(_color), key(_key), left(nullptr), right(nullptr), parent(nullptr){};
//		Node(Color _color, T _key, Node* _left, Node* _right, Node* _parent) 
//			:color(_color), key(_key), left(_left), right(_right), parent(_parent){};
//	} 
//
//
//	
//
//};


#include <iostream>
#include <iomanip>
using namespace std;

class rbTree {
	enum nodeColor { BLACK, RED };

	class node {
		friend class rbTree;
		int key;
		bool isLeaf;
		nodeColor color;
		node *left, *right, *parent;
	public:
		node(int _key = 0, node *parent = NULL, bool _isLeaf = false);

		// Print subtree
		void print(int level = 0);
	};

	node *root;

	// Color functions
	void paintBlack(node *tar) {
		tar->color = BLACK;
	}
	void paintRed(node *tar) {
		tar->color = RED;
	}
	int getColor(node *tar) {
		return(tar ? tar->color : 0);
	}

	// Returns brother
	node *getBro(node *tar) {
		node *parent = tar->parent;
		if (parent) {
			if (tar == parent->left) return parent->right;
			else return parent->left;
		}
		return NULL;
	}


	// Right and left rotations
	void rotRight(node *tar) {
		// Save parent
		node *parent = tar->parent;
		bool wasRoot = !(bool)parent;

		bool wasLeftChild = false;
		if (parent && tar == parent->left) wasLeftChild = true;

		// Left son will be new root;
		node *newRoot = tar->left;		// Get pointer to new root
		newRoot->parent = parent;		// its parent was 'tar', switch to 'tar->parent'

		tar->left = newRoot->right;		// Attach right subtree of new root to 'tar'
		tar->left->parent = tar;

		newRoot->right = tar;	// Attach 'tar' as right subtree to new root
		tar->parent = newRoot;	// Switch its parent to 'newRoot'

		// Modify global parent data
		if (wasRoot) root = newRoot;
		else {
			if (wasLeftChild) parent->left = newRoot;
			else parent->right = newRoot;
		}
	}
	void rotLeft(node *tar) {
		node *parent = tar->parent;
		bool wasRoot = !(bool)parent;

		bool wasLeftChild = false;
		if (parent && tar == parent->left) wasLeftChild = true;

		// Right son will be new root;
		node *newRoot = tar->right;		// Get pointer to new root
		newRoot->parent = parent;	// its parent was 'tar', switch to 'tar->parent'

		tar->right = newRoot->left;		// Attach left subtree of new root to 'tar'
		tar->right->parent = tar;

		newRoot->left = tar;	// Attach 'tar' as left subtree to new root
		tar->parent = newRoot;	// Switch its parent to 'newRoot'

		// Modify global parent data
		if (wasRoot) root = newRoot;
		else {
			if (wasLeftChild) parent->left = newRoot;
			else parent->right = newRoot;
		}
	}

	// Maintain Red-Black tree balance after inserting node 'tar' 
	void insert(int key) {

		node *parent = NULL;
		node *cur = root;

		// Find place for node
		while (cur->isLeaf == false) {
			if (key < cur->key) {
				parent = cur;
				cur = cur->left;
			}
			else if (key > cur->key) {
				parent = cur;
				cur = cur->right;
			}
			else return;
		}

		cur = new node(key, parent);
		insertCase0(cur);
	}

	// Node is new root
	void insertCase0(node *tar) {
		if (tar->parent)
			insertCase1(tar);
		else root = tar;
		paintBlack(root);
	}

	// Parent is black - no violation
	void insertCase1(node *tar) {
		if (tar->parent->color != BLACK) insertCase2(tar);
	}

	// Parent is red, uncle is red
	void insertCase2(node *tar) {
		node *grandpa = tar->parent->parent;

		if (grandpa) {
			node *parent = tar->parent;
			node *uncle = getBro(parent);

			if (uncle->color == RED) {
				paintBlack(parent);
				paintBlack(uncle);
				paintRed(grandpa);

				insertCase0(grandpa);
			}
			else insertCase3(tar);
		}
	}

	// Red parent, black uncle, parent is lSon (rSon), tar is rSon (lSon);
	void insertCase3(node *tar) {

		node *parent = tar->parent;
		node *uncle = getBro(parent);
		node *grandpa = parent->parent;

		if (parent == grandpa->left && tar == parent->right) {
			rotLeft(parent); tar = parent;
		}
		else if (parent == grandpa->right && tar == parent->left) {
			rotRight(parent); tar = parent;
		}
		insertCase4(tar);

	}

	// Red parent, black uncle, parent is lSon (rSon), tar is lSon (rSon);
	void insertCase4(node *tar) {
		node *parent = tar->parent;
		node *uncle = getBro(parent);
		node *grandpa = parent->parent;

		paintBlack(parent);
		paintRed(grandpa);

		if (parent == grandpa->left && tar == parent->left) {
			rotRight(grandpa);
		}
		else {
			rotLeft(grandpa);
		}
	}


	// Internal methods searching 
	// for element to delete
	node *findValidDel(node *tar) {
		// If node has two not-leaf children:
		if (tar->left->isLeaf == false && tar->right->isLeaf == false) {
			node *ans = tar->right;
			while (ans->left->isLeaf == false) {
				ans = ans->left;
			}
			return ans;
		}
		else return tar;
	}

	// Replaces node src in tree with tar
	void replaceNode(node *src, node *tar) {
		node *parent = src->parent;
		if (parent) {
			if (src == parent->left) parent->left = tar;
			else parent->right = tar;
		}
		else root = tar;
		tar->parent = parent;
	}

	// Delete node 'tar'
	void deleteNode(node *tar) {

		node *child = (tar->right->isLeaf ? tar->left : tar->right);
		replaceNode(tar, child);

		if (tar->color == BLACK) {
			// Deleting black node with red child
			if (child->color == RED) {
				paintBlack(child);
			}
			// Deleting black node with black child
			else deleteCase1(child);
		}

	}

	// 1) Child is new root
	void deleteCase1(node *tar) {
		if (tar->parent != NULL) deleteCase2(tar);
	}

	// 2) Brother is red
	void deleteCase2(node *tar) {

		node *bro = getBro(tar);

		if (bro->color == RED) {

			paintRed(tar->parent);
			paintBlack(bro);

			if (tar == tar->parent->left)
				rotLeft(tar->parent);
			else
				rotRight(tar->parent);
		}
		deleteCase3(tar);
	}

	// 3) Brother is black, its children are black
	void deleteCase3(node *tar) {
		node *bro = getBro(tar);

		node *lchild = bro->left;
		node *rchild = bro->right;

		if ((tar->parent->color == BLACK) &&
			(bro->color == BLACK) &&
			(lchild->color == BLACK) &&
			(rchild->color == BLACK)) {
			paintRed(bro);
			deleteCase1(tar->parent);
		}
		else {
			deleteCase4(tar);
		}
	}

	// 4) Bro and its children are black, but parent is red
	void deleteCase4(node *tar) {
		node *bro = getBro(tar);

		node *lchild = bro->left;
		node *rchild = bro->right;

		if ((tar->parent->color == RED) &&
			(bro->color == BLACK) &&
			(lchild->color == BLACK) &&
			(rchild->color == BLACK)) {
			paintRed(bro);
			paintBlack(tar->parent);
		}
		else deleteCase5(tar);

	}

	// 5) Bro is black, one son is black, second is red
	void deleteCase5(node *tar) {
		node *bro = getBro(tar);

		node *lchild = bro->left;
		node *rchild = bro->right;

		if (bro->color == BLACK) {

			if ((tar == tar->parent->left) &&
				(rchild->color == BLACK) &&
				(lchild->color == RED)) {
				paintRed(bro);
				paintBlack(lchild);
				rotRight(bro);
			}
			else if ((tar == tar->parent->right) &&
				(lchild->color == BLACK) &&
				(rchild->color == RED)) {
				paintRed(bro);
				paintBlack(rchild);
				rotLeft(bro);
			}
		}
		deleteCase6(tar);
	}

	// 6) Bro is black, one son is black, second is red
	void deleteCase6(node *tar) {
		node *bro = getBro(tar);
		node *lchild = bro->left;
		node *rchild = bro->right;

		bro->color = tar->parent->color;
		paintBlack(tar->parent);

		if (tar == tar->parent->left) {
			paintBlack(rchild);
			rotLeft(tar->parent);
		}
		else {
			paintBlack(lchild);
			rotRight(tar->parent);
		}
	}



public:
	rbTree() {
		root = new node(0, NULL, true);
	};
	node *getRoot() {
		return this->root;
	}

	void push(int key) {
		insert(key);
	}
	void pop(int key) {
		node *cur = root;

		// Find node with key
		while (!cur->isLeaf && cur->key != key) {
			if (key < cur->key) cur = cur->left;
			else cur = cur->right;
		}

		// If key not found
		if (cur->isLeaf) {
			//cout << "Not found!" << endl;
			return;
		}

		// If it was the only node, put root
		if (cur == root && cur->left->isLeaf && cur->right->isLeaf) {
			delete cur;
			root = NULL;
			return;
		}

		node *toDel = findValidDel(cur);
		swap(toDel->key, cur->key);
		deleteNode(toDel);
	}

	void print() {
		if (root) root->print();
		else cout << "<empty tree>" << endl;
		cout << endl;
	}
};