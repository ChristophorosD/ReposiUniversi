#pragma once
#ifndef BINTREE_FUNCS_H_
#define BINTREE_FUNCS_H_

#include <string>
#include <iostream>
#include <memory>

/*
Description: Searches the binary tree for a given president name
preconditions:
	(o) prezname--the keyname of the president
	(o) tref--the root of the binary tree
	(o) bool--if the president was found
	(o) tref--where the president was found
	(o) tref--the parent node of the president if found
postconditions:
	(o) bool--whether the presdident was found
	(o) tref--where the president was found
	(o) tref--the parent node of the president if found
*/


typedef std::shared_ptr<struct cell> tref;

struct cell
{
	std::string prez;
	tref left, right;
	cell()
	{
		prez = "foo foo Prezident";
	}
	cell(std::string prezName)
	{
		prez = prezName;
	}
};

typedef cell tnode;
/*
Description: Searches for a keyname
preconditions:
     (o) prezname--the keyname of the president
     (o) tref--the root of the binary tree (by reference to modify the actual tree)
	 (o) bool--whether the node was found or not
	 (o) tref the node was found
	 (o) tref parent node of the last node that the search algorithm lands on
	 (o) char--a character indicating if the node was the left or right child
postconditions: N/A
*/
void tsearch(std::string keyname, tref root, bool &found, tref &where, tref &parentNode, char &side);

/*
Description: inserts a president name in the binary tree
preconditions:
	(o) prezname--the keyname of the president
	(o) tref--the root of the binary tree (by reference to modify the actual tree)
postconditions: N/A
*/
void tinsert(std::string keyname, tref &root);

/*
Description: inserts a president name in the binary tree recursively
preconditions:
     (o) prezname--the keyname of the president
     (o) tref--the root of the binary tree (by reference to modify the actual tree)
postconditions: N/A
*/
void t_recInsert(std::string keyname, tref &root);
/*
Description: balances a tree structure based on data passed to it
preconditions:
	 (o) tref--the root of the binary tree (by reference to modify the actual tree)
	 (o) std::string--the raw data to be reogranized
	 (o) int--the left end of the array or section
	 (o) int--the right end of the array or section
postconditions: a balanced tree
Misc: works best if the dtat passed is in alphabetical/numerical order
*/
void tbalance(tref &root, std::string rawTreeData[], int leftEnd, int rightEnd);
/*
Description: builds an alphabetized tree structure based on an array of strings passed to it--controls how often tinsert should
be called
preconditions:
	(o) prezname array--the array of strings to use as a model to build the tree
	(o) int--the size of the array of strings
	(o) tref--the root of the binary tree (by reference to modify the actual tree)
postconditions: N/A
*/
void tbuilder(std::string list[], int size, tref &root);

/*
Description: outputs the tree
preconditions:
	(o) tref--the root of the binary tree
postconditions: N/A
*/

void toutput(tref root);

/*
Description: outputs the tree and shows its pointer structure
preconditions:
(o) tref--the root of the binary tree
postconditions: N/A
*/

void toutAnat(tref root);
/*
Description: uses the recurssive infix algorithm in order to traverse a tree and store its data in an array
preconditions:
     (o) tref--the root of the binary tree
	 (o) std::string travLog--the array to store data in
	 (o) int logSize--the size of the array to store data in
	 (o) int index--the index that will be shared on the stack for this function
		--allows for a global feel without using an actual global variable
postconditions: N/A
     (o)an array that records the traversal of the array
*/
void trav_lnr(tref root, std::string travLog[], int logSize, int &index);

#endif