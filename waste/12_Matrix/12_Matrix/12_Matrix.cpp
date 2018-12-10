#include "12_Matrix.h"
#include <fstream>
#include <ostream>

using std::cout;
using std::endl;
using std::ifstream;

Matrix::Matrix() {
	ifstream fin;
	fin.open("matrix.txt");
	fin >> numRows >> numColumns;

	if (numRows == 0) {
		std::cerr << "Error: File is empty" << endl;
		head = nullptr;
		return;
	}

	int data;
	linkNode* linkTmp = new linkNode();
	dataNode* dataTmp = new dataNode();
	head = new linkNode();
	head = linkTmp;
	bool first = true;
	bool newRow = true;

	for (int itrY(0); itrY < numRows; itrY++) {
		newRow = true;
		for (int itrX(0); itrX < numColumns; itrX++) {
			fin >> data;
			if (data != 0) {
				if (!linkTmp->down && newRow) {
					linkNode* tmp = new linkNode();
					dataTmp = new dataNode();
					
					dataTmp->data = data;
					dataTmp->columnIndex = itrX;
					tmp->rowIndex = itrY;
					tmp->next = dataTmp;
					if (!first) {       // going to the next row
						tmp->up = linkTmp;
						linkTmp->down = tmp;
						linkTmp = tmp;
					}
					else {				// linking head
						first = false;
						linkTmp = tmp;
						head = linkTmp;
					}
					newRow = false;
				} 
				else if (!newRow) {
					dataNode* tmp = new dataNode();
					tmp->data = data;
					tmp->columnIndex = itrX;
					dataTmp->next = tmp;
					tmp->prev = dataTmp;
					dataTmp = tmp;
				}

			}
			else if (!linkTmp->down && !linkTmp->next && itrX == numColumns - 1 && itrY == numRows - 1) 
			{// create a node with zero value if input matrix is filled only with zeros
				linkNode* tmp = new linkNode(0);
				dataNode* tmpData = new dataNode(0, 0);
				tmp->next = tmpData;
				head = tmp;
			}

		}
	}
}

Matrix::~Matrix() {

}

void Matrix::printMatrix() {
	linkNode* currHead = head;
	dataNode* tmpData = nullptr;
	bool first = true;
	int nullLine = 0;
	bool onlyZerosLeft = false;
	int index;
	for (int i(0); i < numRows; i++) {
		if (!first) { // change head pointer if the program goes to the row with a non-zero value
			if (currHead->down)
				currHead = currHead->down;
			else
				onlyZerosLeft = true;
			first = true;
		}
		if (onlyZerosLeft)
			nullLine = numRows - i;
		else {
			nullLine = currHead->rowIndex - i; // count number of lines that contain null value
			tmpData = currHead->next;
		}
		cout << endl;
		for (int j(0); j < numColumns; j++){
			if (tmpData && !onlyZerosLeft)
				index = tmpData->columnIndex; // remember the index of a non-zero value
			if (nullLine != 0)
				cout << "0 ";
			else {
				if (j != index)
					cout << "0 ";
				else {
					cout << tmpData->data << " ";
					tmpData = tmpData->next;
					first = false;
				}
			}
		}
	}
	cout << endl;
}

void Matrix::insertInColumn(linkNode* currHead, dataNode* tmpData, int x, int data) {
	bool first = true;
	if (currHead->up)
		first = false;
	while (tmpData) {
		if (x < tmpData->columnIndex)
			if (tmpData->prev) { // inserting new Node between 2 exsisting data nodes case: 1 x 0 1
				dataNode* curr = new dataNode(data, x);
				curr->next = tmpData;
				tmpData->prev->next = curr;
				curr->prev = tmpData->prev;
				tmpData->prev = curr;
				return;
			}
			else if (!first){ 
				dataNode* curr = new dataNode(data, x);
				curr->next = tmpData;
				currHead->next = curr;
				tmpData->prev = curr;
				return;
			}
			else { // case: x 0 0 1
				dataNode* curr = new dataNode(data, x);
				head->next = curr;
				curr->next = tmpData;
				tmpData->prev = curr;
				currHead->next = curr;
				head = currHead;
				return;
			}
		else if (tmpData->columnIndex == x) {
			tmpData->data = data;
			tmpData->columnIndex = x;
			return;
		}
		else {
			if (!tmpData->next) { // case: 0 1 0 x
				dataNode* curr = new dataNode(data, x);
				curr->prev = tmpData;
				tmpData->next = curr;
				return;
			}
			else
				tmpData = tmpData->next;
		}
	}
}

void Matrix::changeValue(int x, int y, int data) {
	dataNode* tmpData;
	linkNode* currHead;
	currHead = head;
	if (x > numColumns || y > numRows) {
		cout << endl << "error, out of range" << endl;
		return;
	}
	while (currHead) {
		if (currHead->rowIndex == y) {
			tmpData = currHead->next;
			insertInColumn(currHead, tmpData, x, data);
			return;
		}
		else if (y < currHead->rowIndex) {
			linkNode* tmpLink = new linkNode(y);
			if (currHead->up) {
				tmpLink->down = currHead;
				tmpLink->up = currHead->up;
				currHead->up->down = tmpLink;
				currHead->down = tmpLink;
			}
			else {
				tmpLink->down = currHead;
				currHead->up = tmpLink;
				head = tmpLink;
			}
			dataNode* curr = new dataNode();
			tmpLink->next = curr;
			curr->data = data;
			curr->columnIndex = x;
			return;
		}
		else {
			if (!currHead->down) {
				linkNode* tmpLink = new linkNode(y);
				currHead->down = tmpLink;
				tmpLink->up = currHead;
				dataNode* curr = new dataNode();
				tmpLink->next = curr;
				curr->data = data;
				curr->columnIndex = x;
				return;
			}
			currHead = currHead->down;
		}
	}
}

int Matrix::getRow() {
	return numRows;
}

void Matrix::findMaxElement(int& maxElement) {
	linkNode* currHead = head;
	dataNode* tmpData = nullptr;
	int x = 0;
	int y = 0;
	
	while (currHead) {
		tmpData = currHead->next;
		while (tmpData) {
			if (tmpData->data > maxElement) {
				maxElement = tmpData->data;
				x = tmpData->columnIndex;
				y = currHead->rowIndex;
			}
			tmpData = tmpData->next;
		}
		currHead = currHead->down;
	}
	std::cout << "Max element: " << maxElement;
	deleteRowAndColumn(x, y);
}

void Matrix::deleteLine(linkNode* linkPointer) { // fully delete the row in matrix
		dataNode* tmpData = linkPointer->next;
		dataNode* tmp = nullptr;
		while (tmpData->next) {
			tmp = tmpData->next;
			if (tmpData->next->next)
				tmpData->next = tmpData->next->next;
			if (!tmp->next)
				tmpData->next = nullptr;
			tmp->prev = nullptr;
			tmp->next = nullptr;	
			delete tmp;
		}
		delete tmpData;
		delete linkPointer;
}

void Matrix::makeNewHead(linkNode*& currHead, int y) { // create new link for the head
	int index = 0;
	if (currHead->down) {
		linkNode* tmp = currHead;
		currHead = currHead->down;
		head = currHead;
		head->up = nullptr;
		if (tmp->next->next)
			deleteLine(tmp);
		else
			delete tmp;
	}
	else {
		if (numRows - 1 == 0) {
			cout << "Matrix is empty";
			deleteLine(currHead);
			head = nullptr;
			currHead = nullptr;
			return;
		}
		else if (y == numRows - 1) { // last line
			index = y - 1;
		}
		else
			index = y + 1;
		linkNode* tmpLink = new linkNode(index);
		dataNode* tmpData = new dataNode(0,0);
		tmpLink->next = tmpData;
		head = tmpLink;
		currHead = head;
	}
}

void Matrix::deleteRowAndColumn(int x, int y) {
	dataNode* tmpData = nullptr;
	linkNode* currHead = head;
	
	if ( x > numColumns || y > numRows) { // invalid input
		cout << endl << "error, out of range" << endl;
		return;
	}

	if (numColumns == 1 && numRows == 1) { // case if matrix is consist of only one element
		tmpData = currHead->next;
		delete tmpData;
		delete currHead;
		head = nullptr;
		cout << endl << "Matrix is empty";
		return;
	}

	
	while (currHead) {
		if (currHead->rowIndex == y) {
			if (currHead == head) {
				makeNewHead(currHead, y);
			}
			else {
				if (!currHead->down) {
					currHead->up->down = nullptr;
					deleteLine(currHead);
				}
				else {
					currHead->up->down = currHead->down;
					currHead->down->up = currHead->up;
					linkNode* tmp = currHead;
					currHead = currHead->down;
					deleteLine(tmp);
				}
			}
		}
		else { // if the line is not a target for deleting
			if(currHead->rowIndex > y) 
				currHead->rowIndex--;
			tmpData = currHead->next;
			while (tmpData) {
				if (tmpData->columnIndex == x) { // if the Node in line is a target
					if (!tmpData->next && !tmpData->prev) { // only one Node in line
						if (currHead == head)
							makeNewHead(currHead, y);
						else if (!currHead->down) {
							currHead->up->down = nullptr;
							currHead = nullptr;
						}
						else {
							currHead->up->down = currHead->down;
							currHead->down->up = currHead->up;
							currHead = currHead->down;
						}
						delete tmpData;
						tmpData = nullptr;
						continue;
					}
					else if (!tmpData->next) { // the last Node in line
						dataNode* tmp = tmpData;
						tmpData = tmpData->prev;
						tmpData->next = nullptr;
						tmp->next = nullptr;
						tmp->prev = nullptr;
						delete tmp;
					}
					else if (tmpData->prev && tmpData->next) { // 1 0 .. x .. 1
						dataNode* tmp = tmpData;
						tmpData->prev->next = tmpData->next;
						tmpData->next->prev = tmpData->prev;
						tmpData = tmpData->next;
						tmpData->columnIndex--;
						tmp->next = nullptr;
						tmp->prev = nullptr;
						delete tmp;
					}
					else { // 0 x 0 1 ..
						dataNode* tmp = tmpData;
						currHead->next = tmpData->next;
						tmpData = tmpData->next;
						tmpData->prev = nullptr;
						tmpData->columnIndex--;
						tmp->next = nullptr;
						tmp->prev = nullptr;
						delete tmp;
					}	
				}
				if (tmpData->columnIndex > x) // decrementing indexes of each node after target node
					tmpData->columnIndex--;
				tmpData = tmpData->next;
			}
			currHead = currHead->down;
		}
	}

	numRows--;
	numColumns--;
}
