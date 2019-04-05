#include <iostream>
#include "..\..\Biblio\bintree_funcs.h"
#include <fstream>


using namespace std;


void tsearch(prezname keyname, tref &root, bool &found, tref &where, tref &parentNode)
{
	tref p = root, pParent = NULL;
	while (p != NULL && p->prez != keyname)
	{
		pParent = p;
		int sComp = p->prez.compare(keyname);
		if (sComp > 0)
		{
			p = p->left;
		}
		else if (sComp < 0)
		{
			p = p->right;
		}
		else
		{
			found = true;
			break;
		}
	}
	where = p;
	parentNode = pParent;
	return;
}

void tinsert(prezname keyname, tref &root)
{
	bool found;
	tref where;
	tref parentNode;
	tref newPrez;

	tsearch(keyname, root, found, where, parentNode);
	if (found)
	{
		cout << "the president" << where->prez << "is already in the list" << endl;
	}
	else
	{
		int sComp = parentNode->prez.compare(keyname);
		if (sComp > 0)
		{
			parentNode->left = newPrez;
		}
		else
		{
			parentNode->right = newPrez;
		}
	}
	newPrez->prez = keyname;
	newPrez->left = NULL;
	newPrez->right = NULL;
	return;
}
void tbuilder(prezname list[], int size, tref &rootNode)
{
	rootNode->prez = list[0];
	rootNode->left = NULL;
	rootNode->right = NULL;

	for (int i = 1; i < size; i++)
	{
		tinsert(list[i], rootNode);
	}
	return;
}

void toutput(tref &rootNode)
{
	cout << "This is the tree structure" << endl;
	
	tref o_Queue[30];
	
	int head = 0;
	int tail = 1;

	o_Queue[head] = rootNode;
	while (o_Queue[head]->left != NULL || o_Queue[head]->right != NULL)
	{
		cout << o_Queue[head]->prez << endl;
		if (o_Queue[head]->left != NULL)
		{
			o_Queue[tail] = o_Queue[head]->left;
			head = tail;
			tail++;
		}
		else
		{
			cout << "NULL" << endl;
		}
		if (o_Queue[head]->left != NULL)
		{
			o_Queue[tail] = o_Queue[head]->right;
			tail++;
		}
		if (tail == 29)
		{
			tail = 0;
		}
	}
	return;
}
int main()
{
	cout << "Welcome to the president Tree Builder" << endl;
	ifstream prezFile;
	prezFile.open("prez.dat", ios::in);
	prezname prezData[70];
	prezname nextPrez;
	int prezDataSize = 0;

	tref rootNode = NULL;
	cout << "Your output will be available shortly" << endl;

	//initialize list

	while (getline(prezFile, nextPrez))
	{
		//if (!prezFile.eof())
		//{
			//getline(prezFile, nextPrez)
			prezData[prezDataSize] = nextPrez;
			//prezFile >> prezData[prezDataSize];
			prezDataSize++;
			cout << "President " << prezDataSize << " is: " << nextPrez << endl;
		//}
	}

	prezFile.close();
	//build tree
	tbuilder(prezData, prezDataSize, rootNode);

	//output
	toutput(rootNode);
	return 0;
}