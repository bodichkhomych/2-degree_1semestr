using namespace std;

#include <iostream>
#include <thread>

/*
*  Function Header information
*/
void mergeSort(int array[], int i, int j, int indexL, int indexR);
void merge(int array[], int i1, int j1, int i2, int j2);


/*
* Function Name: Main()
* Description: Standard C main function. Reads in from stdin and calls functions
*   to begin the merge sort process.
*/
int main() {
	int array[100000];
	int inputNo = 0;
	int input = 0;
	int outputNo = 0;

	do {
		cin >> input;
		array[inputNo++] = input;
	} while (input != -1);

	if (inputNo == 0) {
		cout << "No values entered. Please enter at least 2 values to be sorted." << endl;
		return 0;
	}
	else if (inputNo == 1) {
		cout << "Single value entered. Please enter at least 2 values to be sorted." << endl;
	}
	else {
		mergeSort(array, 0, inputNo, 0, 0);
	}

	cout << "The List Sorted:" << endl;
	while (outputNo < inputNo - 1) {
		cout << array[outputNo] << endl;
		outputNo++;
	}
	system("pause");
	return 0;
}

/*
* Function Name: mergeSort(array, i, j, indexL, indexR)
* Description:  Merge sort function that uses <thread> library to perform the sort.
* Parameters:
*   array - Reference to the array that the merge sort will be performed on.
*   i - The lower bound of the array to perform the merge sort on.
*   j - The upper bound of the array to perform the merge sort on.
*   indexL - The current thread depth on the left hand side of the merge sort.
*   indexR - The current thread depth on the right hand side of the merge sort.
*/
/*void S(array(int) procs_up, array(int) procs_down)
{
	int proc_count = array_size(procs_up) + array_size(procs_down);
	if (proc_count == 1) {
		return;
	}
	else if (proc_count == 2) {
		array_push(&comparators, ((pair_t){ procs_up[0], procs_down[0] }));
		return;
	}

	array(int) procs_up_odd = array_new(array_size(procs_up) / 2 + array_size(procs_up) % 2, int);
	array(int) procs_down_odd = array_new(array_size(procs_down) / 2 + array_size(procs_down) % 2, int);
	array(int) procs_up_even = array_new(array_size(procs_up) / 2, int);
	array(int) procs_down_even = array_new(array_size(procs_down) / 2, int);
	array(int) procs_result = array_new(array_size(procs_up) + array_size(procs_down), int);

	for (int i = 0; i < array_size(procs_up); i++) {
		if (i % 2) {
			array_push(&procs_up_even, procs_up[i]);
		}
		else {
			array_push(&procs_up_odd, procs_up[i]);
		}
	}
	for (int i = 0; i < array_size(procs_down); i++) {
		if (i % 2) {
			array_push(&procs_down_even, procs_down[i]);
		}
		else {
			array_push(&procs_down_odd, procs_down[i]);
		}
	}

	S(procs_up_odd, procs_down_odd);
	S(procs_up_even, procs_down_even);

	array_concatenate(&procs_result, procs_up, procs_down);

	for (int i = 1; i + 1 < array_size(procs_result); i += 2) {
		array_push(&comparators, ((pair_t){ procs_result[i], procs_result[i + 1] }));
	}

	array_delete(&procs_up_odd);
	array_delete(&procs_down_odd);
	array_delete(&procs_up_even);
	array_delete(&procs_down_even);
	array_delete(&procs_result);
}*/

/*void B(array(int) procs)
{
	if (array_size(procs) == 1) {
		return;
	}

	array(int) procs_up = array_new(array_size(procs) / 2, int);
	array(int) procs_down = array_new(array_size(procs) / 2 + array_size(procs) % 2, int);

	array_copy(procs_up, procs, 0, array_size(procs_up));
	array_copy(procs_down, procs, array_size(procs_up), array_size(procs_down));

	B(procs_up);
	B(procs_down);
	S(procs_up, procs_down);

	array_delete(&procs_up);
	array_delete(&procs_down);
}*/

void mergeSort(int array[], int i, int j, int indexL, int indexR)
{
	int m;

	if (i < j) {
		m = (i + j) / 2;

		cout << "Creating thread for left half of list index " << indexL << "-" << indexR << endl;
		thread left(mergeSort, array, i, m, indexL + 1, indexR);
		left.join();

		cout << "Creating thread for right half of list index " << indexL << "-" << indexR << endl;
		thread right(mergeSort, array, m + 1, j, indexL, indexR + 1);
		right.join();

		cout << "Merging for index " << indexL << "-" << indexR << endl;
		merge(array, i, m, m + 1, j);

		cout << "Exiting thread for index " << indexL << "-" << indexR << endl;
	}
}

/*
* Function Name: merge(array, i1, j1, i2, j2)
* Description: Merge function used by mergeSort to merge two sorted parts of the array.
* Parameters:
*   array - Reference to the array that the merge will be performed on.
*   i1 - Lower bound of the left half to merge.
*   j1 - Upper bound of the left half to merge.
*   i2 - Lower bound of the right half to merge.
*   j2 - Upper bound of the right half to merge.
*/
void merge(int array[], int i1, int j1, int i2, int j2) {
	int tempArray[100000];    //array used for merging
	int i, j, k;
	i = i1;    //beginning of the first list
	j = i2;    //beginning of the second list
	k = 0;

	while (i <= j1 && j <= j2) {
		if (array[i] < array[j]) {
			tempArray[k++] = array[i++];
		}
		else {
			tempArray[k++] = array[j++];
		}
	}

	while (i <= j1) {   //copy remaining elements of the first list
		tempArray[k++] = array[i++];
	}

	while (j <= j2) {    //copy remaining elements of the second list
		tempArray[k++] = array[j++];
	}

	//Transfer elements from temp[] back to a[]
	for (i = i1, j = 0; i <= j2; i++, j++) {
		array[i] = tempArray[j];
	}
	
}