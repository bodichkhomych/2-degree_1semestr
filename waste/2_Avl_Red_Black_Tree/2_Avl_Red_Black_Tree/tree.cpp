#include "AVL.h"

using namespace std;

Node* AVL::balance(Node* node) // balancing the p Node
{
	fixHeight(node);
	if (balanceFactor(node) == 1)
	{
		if (balanceFactor(node->right) < 0)
			node->right = rotateRight(node->right);
		return rotateLeft(node);
	}
	if (balanceFactor(node) == -2)
	{
		if (balanceFactor(node->left) > 0)
			node->left = rotateLeft(node->left);
		return rotateRight(node);
	}
	return node; // balancing is not required
}

Node* AVL::insert(Node* root, int k) // insert k key in a tree with root
{
	if (!root) 
		root = new Node(k);
	else if (k < root->key)
		root->left = insert(root->left, k);
	else
		root->right = insert(root->right, k);
	return balance(root);
}

Node* AVL::removeMin(Node* node) // deleting a Node with minimal key from a node tree
{
	if (node->left == 0)
		return node->right;
	node->left = removeMin(node->left);
	return balance(node);
}

Node* AVL::removeKey(Node* node, int k) // deleting k key from node tree
{
	if (!node) return 0;
	if (k < node->key)
		node->left = removeKey(node->left, k);
	else if (k > node->key)
		node->right = removeKey(node->right, k);
	else //  k == node->key 
	{
		Node* q = node->left;
		Node* r = node->right;
		delete node;
		if (!r) return q;
		Node* min = findMin(r);
		min->right = removeMin(r);
		min->left = q;
		return balance(min);
	}
	return balance(node);
}

void AVL::printTree(Node* root) {
	queue<pair<Node*, int>> q;
	if (root)
		q.push(pair<Node*, int>(root, 1));
	int currDepth = 1;
	while (!q.empty()) {
		pair<Node*, int> curr = q.front();
		q.pop();
		if (curr.second != currDepth) {
			cout << endl;
			currDepth = curr.second;
		}
		cout << curr.first->key << " ";
		if (curr.first->left)
			q.push(pair<Node*, int>(curr.first->left, curr.second + 1));
		if (curr.first->right)
			q.push(pair<Node*, int>(curr.first->right, curr.second + 1));
	}
}