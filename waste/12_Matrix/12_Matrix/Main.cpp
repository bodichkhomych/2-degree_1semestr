#include <conio.h>
#include "12_Matrix.h"

int main() {
	Matrix newMatrix;
	newMatrix.printMatrix();
	//newMatrix.changeValue(1, 3, 3);
	//newMatrix.changeValue(1, 2, 0);
	//newMatrix.printMatrix();

	
		int max = -1000000;
		newMatrix.findMaxElement(max);
		newMatrix.printMatrix();

	

	/*newMatrix.deleteRowAndColumn(4,4);
	newMatrix.printMatrix();
	newMatrix.deleteRowAndColumn(3,3);
	newMatrix.printMatrix();
	newMatrix.deleteRowAndColumn(0,0);
	newMatrix.printMatrix();
	newMatrix.deleteRowAndColumn(0,1);
	newMatrix.printMatrix();
	newMatrix.deleteRowAndColumn(0, 0);*/
	_getch();

}