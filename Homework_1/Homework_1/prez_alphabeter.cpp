#include<iostream>
#include<string>
#include<fstream>
#include "binarray_funcs.h"
using namespace std;

typedef string prezname;

void userinterface(prezname prezList[], int &length);
void load_data(prezname prezList[], int &length);

void bin_search(prezname keyname, prezname prez[], int length, bool &found, int &where)
{
	int top = 0, bottom = length-1, mid;
	found = false;
	while (top <= bottom && !found)
	{
		mid = (top + bottom) / 2;
		int compStr = prez[mid].compare(keyname);
		if (compStr < 0)
		{
			top = mid + 1;
		}
		else if (compStr > 0)
		{
			bottom = mid - 1;
		}
		else
		{
			found = true;
			where = mid;
		}
	}
	//if you never find person, use where the top index is (because it is now biger than bottom) and prepare
	//a tail shift
	if (!found)
	{
		where = top;
	}
	return;
}

void bin_insert(prezname keyname, prezname prez[], int &length)
{
	//found and where will be initialized in bin_search
	bool found;
	int where;
	bin_search(keyname, prez, length, found, where);
	if (found)
	{
		cout << keyname << " is alredy in the list slot at " << where << endl;
	}
	else
	{
		//tail shift algorithm
		for (int i = length; i >= where; i--)
		{
			prez[i + 1] = prez[i];
		}
		prez[where] = keyname;
		length++;
	}
	return;
}

void bin_delete(prezname keyname, prezname prez[], int &length)
{
	//found and where will be initialized in bin_search
	bool found;
	int where;
	bin_search(keyname, prez, length, found, where);
	if (!found)
	{
		cout << keyname << " does not exist: cannot be deleted." << endl;
	}
	else
	{
		//tail shift algorithm
		for (int i = where; i <= length; i++)
		{
			prez[i] = prez[i+1];
		}
		length--;
	}
	return;
}


void userinterface(prezname prezList[], int &length)
{
	char userInput[2];
	prezname prezKey;
	bool closeProg = false;
	do
	{

		cout << "----Welcome to President List Modifier-----" << endl;
		cout << "Please choose how you would like to modify the array" << endl << endl;
		cout << "a. add a President" << endl;
		cout << "b. delete a president" << endl;
		cout << "c. search for a president" << endl;
		cout << "e. EXIT PROGRAM" << endl;

		cin.get(userInput, 2);
		cin.ignore();
		if (isdigit(userInput[0]))
		{
			cout << "This cannot be a number" << endl;
		}
		else
		{
			bool found;
			int where;
			cout << endl;
			switch (userInput[0])
			{
			case 'a':
				cout << "Please enter the president name you would like to add" << endl;
				cout << ":  ";
				getline(cin, prezKey);
				cout << prezKey;
				cout << endl;
				bin_insert(prezKey, prezList, length);
				break;
			case 'b':
				cout << "Please enter the president name you would like to delete" << endl;
				cout << ":  ";
				getline(cin, prezKey);
				bin_delete(prezKey, prezList, length);
				break;
			case 'c':
				cout << "Please enter the president name you would like to serach for" << endl;
				cout << ":  ";
				getline(cin, prezKey);
				bin_search(prezKey, prezList, length, found, where);
				if (found)
				{
					cout << endl;
					cout << "President " << prezKey << " was found at index: " << where << endl;
				}
				else
				{
					cout << prezKey << " is not in the list" << endl;
				}
				break;
			case 'e':
				cout << "---------------------------PRESIDENT EXIT LIST---------------------------" << endl;
				for (int i = 0; i < length; i++)
				{
					cout << "President " << i+1 << ")  " << prezList[i] << endl;
				}
					closeProg = true;
					break;
				default:
					cout << "Please enter valid input!" << endl;
					break;
			}
		}

	} while (!closeProg);
	cout << endl;
	cout << "press enter to continue..." << endl;
	cin.ignore();
		return;
}


void load_data(prezname prezList[], int &length)
{
	std::string prezFileName;
	prezname prezVal;
	ifstream prezFile;
	do
	{
		cout << "Please enter the name of the data file" << endl;
		cout << "->:";

		getline(cin, prezFileName);
		prezFile.open(prezFileName);
		if (!prezFile)
		{
			cout << "Please enter a valid file name" << endl;
		}
	} while (!prezFile);

	while (getline(prezFile, prezVal))
	{
		//have to check if there is an eof
		if (!prezFile.eof())
		{
			if (length == 0)
			{
				prezList[length] = prezVal;
				length++;
			}
			else
			{
				bin_insert(prezVal, prezList, length);
			}
		}
	}

	cout << "data inserted and alphabetized..." << endl;
	cout << "size: " << length << endl;
	prezFile.close();
	return;
}

int main()
{
	int prezNum = 0;
	prezname prezKey;
	prezname prez[70];
	for (int i = 0; i < 70; i++)
	{
		prez[i] = "";
	}

	load_data(prez, prezNum);
	userinterface(prez, prezNum);


	return 0;
}