#pragma once
#ifndef BINARRAY_FUNCS_H
#define BINARRAY_FUNCS_H

/*
Author: Christopher Davis
Date Created:=: 23 Oct. MMXVII
Revisions
Date Modified

Purpose: this is to handle alphabetized or numerically ordered lists
*/

/*
Description--this function performs a binary search on an array and returns the index where it is found
preconditions
        (o) ordVal keyname--an arbitrary class value that can be ordered (e.g. a string or numeric value)
		(o) ordVal nameArray[]--the array to be searched
		(o) int length--the length of the array to be searched
		(o) bool found--a passed by reference boolean value to indicate if the keyname searched for is found
		(o) int where--the index where the keyname is found
postconditions:
        (o) bool found--a passed by reference boolean value to indicate if the keyname searched for is found
        (o) int where--the index where the keyname is found
*/
template <class ordVal> void bin_search(ordVal keyname, ordVal nameArray[], int length, bool &found, int &where);

/*
Description--this function inserts an element into the array
preconditions
        (o) ordVal keyname--an arbitrary class value that can be ordered (e.g. a string or numeric value)
		(o) ordVal nameArray[]--the array to be searched
		(o) int length--the length of the array to be searched
		(o) bool found--a passed by reference boolean value to indicate if the keyname searched for is found
		(o) int where--the index where the keyname is found
postconditions:
        (o) bool found--a passed by reference boolean value to indicate if the keyname searched for is found
        (o) int where--the index where the keyname is found
		(o) int length--the new length of the array
*/
template <class ordVal> void bin_insert(ordVal keyname, ordVal nameArray[], int &length);

/*
Description--this function inserts an element into the array
preconditions
        (o) ordVal keyname--an arbitrary class value that can be ordered (e.g. a string or numeric value)
        (o) ordVal nameArray[]--the array to be searched
        (o) int length--the length of the array to be searched
        (o) bool found--a passed by reference boolean value to indicate if the keyname searched for is found
        (o) int where--the index where the keyname is found
postconditions:
        (o) bool found--a passed by reference boolean value to indicate if the keyname searched for is found
        (o) int length--the new length of the array
*/
template <class ordVal> void bin_delete(ordVal keyname, ordVal nameArray[], int &length);



#endif
