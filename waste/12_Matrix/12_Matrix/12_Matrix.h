#include <iostream>
#pragma once
class dataNode {
	friend class Matrix;
private:
	int columnIndex;
	int data;
	dataNode* next;
	dataNode* prev;
public:
	dataNode(){
		columnIndex = 0;
		data = 0;
		next = nullptr;
		prev = nullptr;
	}
	dataNode(int data, int x) {
		this->data = data;
		columnIndex = x;
		next = nullptr;
		prev = nullptr;
	}
};

class linkNode {
	friend class Matrix;

private:
	int rowIndex;
	linkNode* down;
	linkNode* up;
	dataNode* next;
public:
	linkNode() {
		rowIndex = 0;
		down = nullptr;
		next = nullptr;
		up = nullptr;
	}
	linkNode(int y) {
		rowIndex = y;
		down = nullptr;
		next = nullptr;
		up = nullptr;
	}
};



class Matrix
{
private:
	linkNode* head;
	int numRows;
	int numColumns;
	void insertInColumn(linkNode* currHead, dataNode* tmpData, int x, int data);
	void deleteLine(linkNode* linkPointer);
	void makeNewHead(linkNode*& currHead, int y);
public:
	Matrix();
	~Matrix();

	int getRow();
	void changeValue(int x, int y, int data);
	void deleteRowAndColumn(int columnIndex, int rowIndex);
	void findMaxElement(int& maxElement);
	void deleteMatrix();
	void printMatrix();

};

/* in changeValue should be applyed the removal of Nodes if the data is 0
*/
