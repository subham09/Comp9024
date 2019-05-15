/*
 Implementation of doubly-linked list ADT for string values.
 Written by Ashesh Mahidadia Jan 2018, based on code writted by John Shepherd 2015.
 You may need to modify the following implementation and test it properly before using 
 in your program.
*/


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "DLListStr.h"

// data structures representing DLListStr

//typedef struct DLListNode {
//	char   *value;  // value of this list item (string)
//	struct DLListNode *prev;
//	               // pointer previous node in list
//	struct DLListNode *next;
//	               // pointer to next node in list
//} DLListNode;
//
//typedef struct DLListRep {
//	int  nitems;      // count of items in list
//	DLListNode *first; // first node in list
//	DLListNode *curr;  // current node in list
//	DLListNode *last;  // last node in list
//} DLListRep;

// create a new DLListNode (private function)
// comment today
//static DLListNode *newDLListNode(char *val)
//{
//	DLListNode *new;
//	new = malloc(sizeof(DLListNode));
//	assert(new != NULL);
//
//        strcpy(new->value, val);  // for int, new->value = it;
//	
//	new->prev = new->next = NULL;
//	return new;
//}

// create a new empty DLListStr
DLListStr newDLListStr()
{
	struct DLListRep *L;

	L = malloc(sizeof (struct DLListRep));
	assert (L != NULL);
	L->nitems = 0;
	L->first = NULL;
	L->last = NULL;
	L->curr = NULL;
	return L;
}


/* 
   pre-reqisite: L is ordered (increasing) with no duplicates
   post-condition: val is inserted in L, L is ordered (increasing) with no duplicates
*/
void insertSetOrd(DLListStr L, char *val){

	/* 
	   implement this function to
	   insert val in L  (in order), no duplicates (set)

	*/
	//printf("hello insert\n");
	//printf("val\t%s\n", val);
	
	
	DLListNode *n = malloc(sizeof(DLListNode));
	DLListNode *current = malloc(sizeof(DLListNode));
	DLListNode *check = malloc(sizeof(DLListNode));
	check = L->first;
	assert(n != NULL);
	
	// implement this function 
	// for empty list
	
	while (check != NULL)
	{
		if (strcmp(check->value, val)==0)
			return;
		check = check->next;
	}
	
	if (L->first == NULL)
	{
		//printf("first\n");
		n->value = val;
		n->next = NULL;
		n->prev = NULL;
		L->curr = n;
		L->first = n;
		L->last = n;
		//printf("insert list %s \n", n->value);
		//showDLListStr(L);
		return;
	}
	
	
	
	
	else if (strcmp(L->first->value, val) > 0)
	{
		n->value = val;
		n->next = L->first;
        n->next->prev = n;
       	L->first = n;
       	//showDLListStr(L);
       	return;
	}
	
	else {
        current = L->first;
 
        // locate the node after which the new node
        // is to be inserted
        while (current->next != NULL && 
               strcmp(current->next->value, val) < 0 )
            current = current->next;
 
        /* Make the appropriate links */
        n->value = val;
        n->next = current->next;
 
        // if the new node is not inserted
        // at the end of the list
        if (current->next != NULL)
            n->next->prev = n;

        current->next = n;
        n->prev = current;
    }
	
	
	
	
	
	
//	// for end of list
//	if (L->curr == L->last)
//	{
//		//printf("second\n");
//		n->value = val;
//		n->next = NULL;
//		L->curr->next = n;
//		n->prev = L->curr;
//		L->curr = n;
//		L->last = n;
//		//printf("insert list %s \n", n->value);
//		showDLListStr(L);
//		return;
//	}
//	// for in between list
//		//printf("third\n");
//		n->value = val;
//		n->next = L->curr->next;
//		L->curr->next->prev = n;
//		n->prev = L->curr;
//		L->curr = n;
//		//printf("insert list %s \n", n->value);
//		showDLListStr(L);
		//showDLListStr(L);
		return;
}



// display items from a DLListStr, comma separated
void showDLListStr(DLListStr L)
{
	assert(L != NULL);
	DLListNode *curr;
	int count = 0;
	for (curr = L->first; curr != NULL; curr = curr->next){
		count++;
		if(count > 1) {
			fprintf(stdout,", ");
		}
		fprintf(stdout,"%s",curr->value);
	}
	fprintf(stdout,"\n");
}


// free up all space associated with list
void freeDLListStr(DLListStr L)
{
	assert(L != NULL);
	DLListNode *curr, *prev;
	curr = L->first;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(L);
}

//int main()
//{
//	DLListStr d = newDLListStr();
//	char *val = "url52";
//	insertSetOrd(d, val);
//	char *val1 = "url22";
//	insertSetOrd(d, val1);
//	char *val2 = "url44";
//	insertSetOrd(d, val2);
//	char *val3 = "url65";
//	insertSetOrd(d, val3);
//	showDLListStr(d);
//	return 0;
//}


