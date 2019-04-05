#include <iostream>
#include <string>
#include <fstream>
#include "../../Biblio/arrayManips.h"
using namespace std;

typedef std::string prezname;

void heap_sift(int nodeInt, prezname prezList[], int length)
{
	int maxKid;
	while (2 * nodeInt <= length)
	{
		if ((2 * nodeInt) == length)
		{
			maxKid = 2 * nodeInt;
		}
		else
		{
			int strCmp1 = prezList[2 * nodeInt].compare(prezList[(2 * nodeInt) + 1]);
			if (strCmp1 > 0)
			{
				maxKid = 2 * nodeInt;
			}
			else
			{
				maxKid = (2 * nodeInt) + 1;
			}
		}
		int cmpP_F = prezList[nodeInt].compare(prezList[maxKid]);
		if (cmpP_F < 0)
		{
			prezname temp = prezList[nodeInt];
			prezList[nodeInt] = prezList[maxKid];
			prezList[maxKid] = temp;
			nodeInt = maxKid;
		}
		else
		{
			break;
		}
	}
	return;
}

void heapify_stg1(prezname prezList[], int prezListSize)
{
	int uPar = prezListSize / 2;
	for (int i = uPar; i > 1; i--)
	{
		heap_sift(i, prezList, prezListSize);
	}
	return;
}

void heapify_stg2(prezname prezList[], int prezListSize)
{
	int size = prezListSize;
	for (int i = 1; i < prezListSize-1; i++)
	{
		heap_sift(1, prezList, size);
		prezname temp = prezList[1];
		prezList[1] = prezList[size];
		prezList[size] = temp;
		size--;
	}
	return;
}
void outputPrezes(prezname prezList[], int length)
{
	cout << "Ordered Prez Data" << endl;
	cout << "----------------------------------------------------------------" << endl;
	for (int i = 1; i <= length; i++)
	{
		cout << "President" << i << ")" << prezList[i] << endl;
	}
	cout << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << "END OF PREZEZ" << endl;
	return;
}



int main()
{
	cout << "This code heapifies the president list" << endl;
	prezname prezList[70];
	int prezListSize = 0;

	//initialize dummy values for array
	for (int i = 1; i < 70; i++)
	{
		prezList[i] = "foofoo_Prez";
	}

	//open president data file
	ifstream prezFile;
	prezFile.open("..\\..\\Biblio\\prez.dat");
	prezname nextPrez;

	cout << "Your output will be available shortly" << endl;

	//fill array with good data
	while (getline(prezFile, nextPrez))
	{
		prezList[prezListSize+1] = nextPrez;
		prezListSize++;
	}

	prezFile.close();

	cout << "Heapifying your presidents" << endl;
	heapify_stg1(prezList, prezListSize);
	heapify_stg2(prezList, prezListSize);
	outputPrezes(prezList, prezListSize);

	cout << endl;
	cout << "press enter to continue..." << endl;
	cin.get();

	return 0;
}