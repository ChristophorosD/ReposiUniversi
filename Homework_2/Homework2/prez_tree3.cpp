/*
Author: Christopher H. Davis
Date Created: October 2017
Date Last Modified: 6 November 2017
*/
#include <iostream>
#include "..\..\Biblio\bintree_funcs.h"
#include <fstream>

using namespace std;
typedef string prezname;

void tsearch(prezname keyname, tref root, bool &found, tref &where, tref &parentNode, char &side)
{
	tref p = root, pParent = NULL;
	found = false;
	while (p != NULL && p->prez != keyname)
	{
		pParent = p;
		int sComp = p->prez.compare(keyname);
		if (sComp > 0)
		{
			p = p->left;
			side = 'l';
		}
		else if (sComp < 0)
		{
			p = p->right;
			side = 'r';
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

void tbuilder(prezname list[], int size, tref &rootNode)
{
	rootNode->prez = list[0];

	for (int i = 1; i < size; i++)
	{
		tinsert(list[i], rootNode);
	}
	return;
}

void tinsert(prezname keyname, tref &root)
{
	bool found;
	tref where, parentNode;
	char side = 'n';

	tsearch(keyname, root, found, where, parentNode, side);
	if (found)
	{
		cout << "the president" << where->prez << "is already in the list" << endl;
	}
	else
	{
		tref newPrez(new tnode(keyname));
		switch (side)
		{
		case 'l':
			parentNode->left = newPrez;
			break;
		case 'r':
			parentNode->right = newPrez;
			break;
		}
	}
	return;
}


void toutput(tref rootNode)
{
	cout << "This is the tree structure" << endl;

	tref o_Queue[30];

	int head = 0;
	int tail = 0;
	o_Queue[head] = rootNode;
	do  //in case the tree is empty only one NULL will be written 
	{
		if (o_Queue[head] != NULL)
		{
			cout << o_Queue[head]->prez << endl;    //output current element
			tail++;  //move tail to next available spot
			o_Queue[tail] = o_Queue[head]->left;    //queue up left child
			tail++;  //move tail to next available spot
			if (tail > 29) //wrap around tail
			{
				tail = 0;
			}
			o_Queue[tail] = o_Queue[head]->right;  //queue up right child
		}
		else
		{
			cout << "NULL" << endl;
		}
		head++;
		if (head > 29)  //wrap around head
		{
			head = 0;
		}
	} while (head != tail);   //queue will be "emptied" as head aproaches tail
	return;
}

int main()
{
	cout << "Welcome to the president Tree Builder" << endl;

	//open president data file
	ifstream prezFile;
	prezFile.open("prez.dat");
	prezname prezData[70];
	prezname nextPrez;
	int prezDataSize = 0;

	tref rootNodePt (new tnode());
	cout << "Your output will be available shortly" << endl;

	//initialize list

	while (getline(prezFile, nextPrez))
	{
			prezData[prezDataSize] = nextPrez;
			prezDataSize++;
	}
	//close file because no longer needed
	prezFile.close();

	//build tree
	tbuilder(prezData, prezDataSize, rootNodePt);

	//output tree
	toutput(rootNodePt);

	cout << endl;
	cout << "press enter to continue..." << endl;
	cin.get();
	return 0;
}