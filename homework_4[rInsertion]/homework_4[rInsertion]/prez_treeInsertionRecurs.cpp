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

void tbuilder(prezname list[], int size, tref &rootNode)
{

	for (int i = 1; i < size; i++)
	{
		t_recInsert(list[i], rootNode);
	}
	return;
}

void  t_recInsert(prezname keyname, tref &root)
{
	if (root != NULL)
	{
		int strCmp = root->prez.compare(keyname);
		if (strCmp == 0) //stop recursion if the keyname already exists
		{
			cout << "President " << keyname << " is already in the list. at <<" << root << ">> CANNOT INSERT" << endl;
			return;
		}
		else if (strCmp > 0)
		{
			t_recInsert(keyname, root->left);
		}
		else
		{
			t_recInsert(keyname, root->right);
		}
	}
	else
	{ 
		tref newPrez(new tnode(keyname));
		root = newPrez;
		return;
	}
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
	prezFile.open("..\\..\\Biblio\\prez.dat");
	prezname prezData[70];
	prezname nextPrez;
	int prezDataSize = 0;

	cout << "Your output will be available shortly" << endl;

	//initialize list

	while (getline(prezFile, nextPrez))
	{
		prezData[prezDataSize] = nextPrez;
		prezDataSize++;
	}

	tref rootNodePt(new tnode(prezData[0]));
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