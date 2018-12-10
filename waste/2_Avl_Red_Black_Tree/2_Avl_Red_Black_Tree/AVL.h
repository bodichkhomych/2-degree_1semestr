#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

struct Node {
	Node* right;
	Node* left;
	int height;
	int key;
	Node(){
		right = nullptr; left = nullptr; height = 0; key = 0;
	}
	Node(int k) {
		right = nullptr; left = nullptr; height = 0; key = k;
	}
};

class AVL {
private:
	Node* root;

	int getHeigth(Node* node) {
		return node ? node->height : 0;
	}

	void fixHeight(Node* node) {
		int h1 = getHeigth(node->left);
		int h2 = getHeigth(node->right);
		node->height = ((h1 > h2) ? h1 : h2) + 1;
	}

	int balanceFactor(Node* node) {
		return getHeigth(node->right) - getHeigth(node->left);
	}

	Node* rotateRight(Node* node) {
		Node* current = node->left;
		node->left = current->right;
		current->right = node;
		fixHeight(node);
		fixHeight(current);
		return current;
	}

	Node* rotateLeft(Node* node) {
		Node* current = node->right;
		node->right = current->left;
		current->left = node;
		fixHeight(node);
		fixHeight(current);
		return current;
	}

	Node* findMin(Node* node) // find a Node with minimal key in a p tree 
	{
		return node->left ? findMin(node->left) : node;
	}

	Node* removeMin(Node* node);
	Node* balance(Node* node);
	

public: 
	AVL() {

	}
	Node* insert(Node* root, int k);
	Node* removeKey(Node* node, int k);
	void printTree(Node* node);

};