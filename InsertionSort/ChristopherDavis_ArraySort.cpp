/*
 * ArraySort.cpp
 *
 *  Created on: Nov 10, 2016
 *      Author: christopherdavis
 */
#include <iostream>
using namespace std;
/*
 * Description: this function sets the size of an array
 * pre_condition an integer (called by reference) that defines the absolute highest length that an array
 * post_condition: an integer that will serve as the length value for an array
 */
int set_arraySize (const int &);

/*
 * Description: populates an array with user input
 * pre_condition
 * 			(o) an array (called by reference) that will be filled with user input
 * 			(o) an integer for the size of the array
 * post_condition: the array populated with user input
 */
void fillArray(int *, int &);

/*
 * Description: sorts an array in ascending order using the insertion sort algorithm
 * pre_condition
 * 			(o) an array (called by reference) that holds raw data to be sorted
 * 			(o) an empty array (called by reference) that will hold the sorted data
 * 			(o) an integer (called by reference) for the size of both arrays
 * post_condition: the sorted array
 */
void insertion_sort(int *, int *, int &);

/*
 * Description: inserts an element at an index in an array and moves up subsequent values
 * pre_condition
 * 			(o) an array (called by reference) that will be manipulate
 * 			(o) an integer (called by reference) for the size of the array to be manipulated
 * 			(o) an integer (called by reference) that will be the index where a value is to be inserted
 * 			(o) an integer (called by reference) for the value that will be inserted in to the element at
 * 			a given index
 * 			(o) an integer (called by reference) for the index where the user input array is currently being processed
 * post_condition: n/a
 */
void displaceInsert(int *, int & , int &, int &, int &);

/*
 * Description: Displays a sorted array
 * pre_condition:
 * 			(o) an array (called by reference) whose elements will be displayed
 * 			(o) an integer (called by reference) for the size of the array

 * post_condition: n/a
 */
void displaySort ( int *, int &);

int main()
{

	const int ABSOLUTE_MAX = 10000;
	int array_size;

	//initialize array size
	array_size = set_arraySize(ABSOLUTE_MAX);
	int sort_array[array_size];

	//initialize array values for the array that wil hold the sorted values
	for (int i = 0; i < array_size; i++)
	{
		sort_array[i] = 0;
	}

	//create user input array
	int userInput_array[array_size];

	//get user input for sort
	fillArray(userInput_array, array_size);

	//sort the user data in increasing order
	insertion_sort(userInput_array, sort_array, array_size);

	//display the sorted array
	displaySort(sort_array, array_size);
return 0;
}


int set_arraySize(const int &MaxSize)
{
	//define array size
	int array_size(0);
	do
	{
	cout << "Please enter the size of the array you would like to create (nothing greater than 10,000) \n";
	cin >> array_size;

	//check if array is not bigger than max
	if (array_size > MaxSize)
	{
		cout << "you're not a good listener are you...LESS than 10,000. Thank you. \n";
	}
	}while (array_size > MaxSize);
	return array_size;
}

void fillArray(int *inputHolder, int &size)
{
	cout << "Now, please enter the list of data that you want to have sorted in ascending order.  Integers only. \n";
	for (int i = 0; i < size; i++)
	{
		cin >> inputHolder[i];
	}
	return;
}

void insertion_sort (int *userData, int *sortedArray, int &size)
{
	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k < size; k++)
		{
			/*replace an empty 0 with the given user data value
			  if k >= i, that means that the given sorted array value
			  cannot be a 0 that comes from the user array
			*/
			if (0 == sortedArray[k] && k >= i)
			{
				sortedArray[k] = userData[i];
				break;
			}
			else if (userData[i] <= sortedArray[k])
			{
				displaceInsert(sortedArray, size, k, userData[i], i);
				break;
			}
		}
	}
	return;

}

void displaceInsert(int *arrayRaw, int &size, int &index, int &val, int &uArrayMarker)
{
	int endArray = size-1;
	while (endArray >= index)
	{
		if (arrayRaw[endArray] != 0 || endArray < uArrayMarker)
		{
			arrayRaw[endArray+1] = arrayRaw[endArray];
			arrayRaw[endArray] = 0;
		}
		endArray--;
	}
	arrayRaw[index] = val;
	return;
}

void displaySort(int *sortedArray, int &size)
{
	cout << "The sorted array is as follows \n";
	for (int i = 0; i < size; i++)
	{
		cout << sortedArray[i] << "  ";
	}
	return;

}
