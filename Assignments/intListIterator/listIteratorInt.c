/*
listIteratorInt.c : list Iterator ADT implementation
Written by Subham Anand
Date: 3rd Jan 2018
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorInt.h"

// my global variables
int prev_counter = 0;
int check_counter = 0;
int last_returned_data = 0;

typedef struct Node {
	
	int data;
	struct Node *next;
	struct Node *prev;
	
} Node;

typedef struct IteratorIntRep {
	
	Node *head;
	Node *tail;
	Node *currentNode;
	
} IteratorIntRep;

IteratorInt IteratorIntNew() {
	
	IteratorInt i = malloc(sizeof(IteratorIntRep));
	i->currentNode = NULL;
	i->head = NULL;
	i->tail = NULL;

	return i;
}

void traverseForward(IteratorInt it)
{
	Node *n = malloc(sizeof(Node));
	n = it->head;
	while (n != NULL)
	{
		printf("%d\n", n->data);
		n = n->next;
	}
}

void reset(IteratorInt it) {

	// implement this function 
	it->currentNode = it->head;
	prev_counter = 1;

}

int add(IteratorInt it, int v) {

	//printf("HEllo world\n");
	Node *n = malloc(sizeof(Node));
	assert(n != NULL);
	
	// implement this function 
	// for empty list
	if (it->head == NULL)
	{
		n->data = v;
		n->next = NULL;
		n->prev = NULL;
		it->currentNode = n;
		it->head = n;
		it->tail = n;
		// 2nd jan change
		prev_counter = 0;
		//printf("Enter if %d\n", n->data);
		return 1;
	}
	
	// for adding element before head
	if (prev_counter == 1)
	{
		n->data = v;
		n->next = it->currentNode;
		it->currentNode->prev = n;
		n->prev = NULL;
		it->currentNode = n;
		it->head = n;
		// 1st jan change
		prev_counter = 0;
		//printf("Enter else %d\n", n->data);
		return 1;
	}
	
	// for end of list
	if (it->currentNode == it->tail)
	{
		n->data = v;
		n->next = NULL;
		it->currentNode->next = n;
		n->prev = it->currentNode;
		it->currentNode = n;
		it->tail = n;
		//printf("Enter else %d\n", n->data);
		return 1;
	}
	
	// for in between list
		n->data = v;
		n->next = it->currentNode->next;
		it->currentNode->next->prev = n;
		// change 1st jan
		it->currentNode->next = n;
		n->prev = it->currentNode;
		it->currentNode = n;
		//printf("Enter else %d\n", n->data);
		return 1;

	return 0;  // you need to change this...
}

int hasNext(IteratorInt it) {

	// implement this function 
	// for head
	if (it->head == NULL)
	{
		return 0;
	}
	if (prev_counter == 1)
	{
		return 1;
	}
	// for tail
	if (it->currentNode->next == NULL)
	{
		return 0;
	}
	
	

	return 1;  // you need to change this...
}

int hasPrevious(IteratorInt it) {

	// implement this function 
	// no element in list
	if (it->head == NULL)
	{
		return 0;
	}
	// for head
	if (prev_counter == 1)
	{
		return 0;
	}
//	if (it->currentNode->prev == NULL)
//	{
//		return 0;
//	}

	return 1;  // you need to change this...
}\

int *next(IteratorInt it) {
	// to avoid null values
	check_counter = 0;
	// implement this function 
	Node *n = malloc(sizeof(Node));
	int *dum = NULL;
	// empty list
	if (it->head == NULL)
	{
		return dum; // changing line return n->next
	}
	
	if (prev_counter == 1)
	{
		prev_counter = 0;
		check_counter = 1;
		last_returned_data = it->currentNode->data;
		dum = &(it->currentNode->data);
		return dum;
		//it->currentNode = it->head;
	}
	
	// next node is null
	if (it->currentNode->next == NULL)
	{
		return dum;
	}
	
	
	
	// base case
	n = it->currentNode;
	it->currentNode = it->currentNode->next;
	last_returned_data = n->next->data;
	dum = &(n->next->data);
	// change 1st jan
	check_counter = 1;
	return dum ;  // you need to change this...
}

int *previous(IteratorInt it) {
	check_counter = 0;
	// implement this function 
	//Node *n = malloc(sizeof(Node));
	int *dum = NULL;
	//empty list
	if (it->head == NULL)
	{
		return dum;
		
	}
	
	//previous node null
	
	if (it->currentNode->prev == NULL)
	{
		if (prev_counter == 0)
		{
			prev_counter = 1;
			check_counter = 1;
			last_returned_data = it->currentNode->data;
			dum = &(it->currentNode->data);
			return dum;
		}
		return dum;
	}
	
	//base case
	it->currentNode = it->currentNode->prev;
	check_counter = 1;
	last_returned_data = it->currentNode->next->data;
	dum = &(it->currentNode->next->data);
	return dum ;  // you need to change this...

}

int deleteElm(IteratorInt it) {

	// implement this function 
	Node *temp = malloc(sizeof(Node));
	// check counter for whether previous call is out of those four method
	if (check_counter == 1)
	{
		//printf("Enter delete\n");
		// current node
		if (it->currentNode->data == last_returned_data)
		{
			// if deleting head
			if (it->currentNode == it->head)
			{
				//If only one element is present in the list and it has to be deleted
  			if (it->head == it->tail)
  			{
  			  it->head = NULL;
			  it->currentNode = NULL;
			  it->tail = NULL;
			  // 2nd jan change
			  free(it->currentNode);
			  return 1;		
			}
				it->currentNode->next->prev = NULL;
				it->head = it->currentNode->next;
				it->currentNode->next = NULL;
				// 2nd jan change
				free(it->currentNode);
				it->currentNode = it->head;
				prev_counter = 1;
				check_counter = 0;
				return 1;
			}
			// if deleting tail
			if (it->currentNode == it->tail)
			{
				it->tail = it->currentNode->prev;
				it->currentNode->prev->next = NULL;
				it->currentNode->prev = NULL;
				// 2nd jan change
				free(it->currentNode);
				it->currentNode = it->tail;
				check_counter = 0;
				return 1;
				
			}
			// in between head and tail
			it->currentNode->next->prev = it->currentNode->prev;
			it->currentNode->prev->next = it->currentNode->next;
			// 3rd jan change 5 lines
			temp = it->currentNode;
			free(it->currentNode);
			it->currentNode = temp->prev;
			//it->currentNode = it->currentNode->prev;
			check_counter = 0;
			return 1;
			
		}
		// right delete
		if (it->currentNode->next->data == last_returned_data)
		{
			// if right node is tail
			if (it->currentNode->next == it->tail)
			{
				it->tail = it->currentNode;
				// 3rd jan change 3 lines
				//it->currentNode->next->prev = NULL;
				free(it->currentNode->next);
				it->currentNode->next = NULL;
				check_counter = 0;
				return 1;
			}
			// if right node is not tail
			it->currentNode->next->next->prev = it->currentNode;
			// 3rd jan change 3 lines
			it->currentNode->next = it->currentNode->next->next;
			check_counter = 0;
			return 1;
			
		}
		// left delete
		if (it->currentNode->prev->data == last_returned_data)
		{
			// if left node is head
			if (it->currentNode->prev == it->head)
			{
				it->head = it->currentNode;
				it->currentNode->prev->next = NULL;
				it->currentNode->prev = NULL;
				// 2nd jan change
				//free(it->currentNode->prev);
				check_counter = 0;
				return 1;
			}
			// if left node is not head
			it->currentNode->prev->prev->next = it->currentNode;
			it->currentNode->prev = it->currentNode->prev->prev;
			// 2nd jan change
			//free(it->currentNode->prev);
			check_counter = 0;
			return 1;
		}
		
		
		//printf("Last returned value %d\n", last_returned_data);
	}
	
	
	return 0;  // you need to change this...
}

int set(IteratorInt it, int v) {

	// implement this function 
	// to check succesfull call to those 4 methods
	if (check_counter == 1)
	{
		// if element is current node
		if (it->currentNode->data == last_returned_data)
		{
			it->currentNode->data = v;
			check_counter = 0;
			return 1;
		}
		// if element is on right
		if (it->currentNode->next->data == last_returned_data)
		{
			it->currentNode->next->data = v;
			check_counter = 0;
			return 1;
		}
		// if element is on left
		if (it->currentNode->prev->data == last_returned_data)
		{
			it->currentNode->prev->data = v;
			check_counter = 0;
			return 1;
		}
	}

	return 0;
}

int *findNext(IteratorInt it, int v) {
	check_counter = 0;
	// implement this function 
	Node *n = malloc(sizeof(Node));
	//Node *n1 = malloc(sizeof(Node));
	int *dum = NULL;
	n = it->currentNode;
	
	// for head cursor
	if (prev_counter == 0)
	{
		if (it->currentNode->next == NULL)
		{
			return dum;
		}
	}
	// change 1st jan
	if (prev_counter == 1)
	{
		if (it->currentNode->data == v)
		{
			last_returned_data = it->currentNode->data;
			dum = &(it->currentNode->data);
			prev_counter = 0;
			return dum;
		}
	}
	// for moving cursor ahead to check from that position
	if (it->currentNode->next != NULL)
	{
		// change 1st jan check_counter = 1;
		it->currentNode = it->currentNode->next;
	}
	
	// base case
	while (it->currentNode != NULL)
	{
		if (it->currentNode->data == v)
		{
			prev_counter = 0;
			check_counter = 1;
			//it->currentNode->next = it->currentNode->data;
			last_returned_data = it->currentNode->data;
			dum = &(it->currentNode->data);
			return dum;
		}
	it->currentNode = it->currentNode->next;
	}
	it->currentNode = n;
	// change 1st jan dum = &(n1->next->data);
	return dum;
}

int *findPrevious(IteratorInt it, int v) {
	check_counter = 0;
	// implement this function 
	Node *n = malloc(sizeof(Node));
	//Node *n1 = malloc(sizeof(Node));
	int *dum = NULL;
	n = it->currentNode;
	
	// for null cursor
	if (prev_counter == 1)
	{
		return dum;
	}
	
	// for head cursor or single element
	if (it->currentNode->prev == NULL)
	{
		if (it->currentNode->data == v)
		{
			prev_counter = 1;
			check_counter = 1;
			last_returned_data = it->currentNode->data;
			dum = &(it->currentNode->data);
			return dum;
		}
	}
	
	// base case
	while (it->currentNode != NULL)
	{
		if (it->currentNode->data == v)
		{
			// change 1st jan for 8 lines
			if (it->currentNode == it->head)
			{
				prev_counter = 1;
				check_counter = 1;
				last_returned_data = it->currentNode->data;
				dum = &(it->currentNode->data);
				return dum;
			}
			//prev_counter = 0;
			it->currentNode = it->currentNode->prev;
			check_counter = 1;
			last_returned_data = it->currentNode->next->data;
			dum = &(it->currentNode->next->data);
			return dum;
		}
		
	it->currentNode = it->currentNode->prev;
	}
	
	it->currentNode = n;
	return dum;
}

void freeIt(IteratorInt it) {

	// implement this function 
	// 2nd jan change start
	Node *n = malloc(sizeof(Node));
	if (it->head != NULL)
	{
		while(it->head != NULL)
		{
			n = it->head;
			free(it->head);
			it->head = n->next;
		}
		free(n);
	}
//	it->currentNode = NULL;
//	it->head = NULL;
//	it->tail = NULL;
	free(it);

}



int subsetList(IteratorInt L1, IteratorInt L2){

	/* 
	   Your solution here 

	*/ // 4 8 10 5---- 5 8
	Node *currNodeSmall= malloc(sizeof(Node));
	Node *currNodeLarge= malloc(sizeof(Node));
	currNodeSmall = L2->head;
	currNodeLarge = L1->head;
	int counter = 0;
	while (currNodeSmall != NULL)
	{
		while (currNodeLarge != NULL)
		{
			if (currNodeSmall->data == currNodeLarge->data)
			{
				counter += 1;
			}
			currNodeLarge = currNodeLarge->next;
		}
		
		if (counter != 1)
		{
			printf("not subset\n");
			return;
		}
		currNodeLarge = L1->head;
		counter = 0;
		currNodeSmall = currNodeSmall->next;
	}
	
	printf("subset\n");

	return 0;
}

IteratorInt getPeaks(IteratorInt L){

	IteratorInt peaksL = IteratorIntNew();

	// your solution here ... 
	Node *currNode= malloc(sizeof(Node));
	currNode = L->head;
	
	while (currNode->next != NULL)
	{
		int myval = currNode->data;
		if (currNode->next != NULL && currNode->prev != NULL)
		{
			if (currNode->next->data < currNode->data && currNode->prev->data < currNode->data)
			{
				// create a node with the value of myval and add that node to peaksL
				add(peaksL, myval);
			}
		}
		currNode = currNode->next;
	}

	return peaksL;

}

void showlist(IteratorInt it)
{
	Node *n = malloc(sizeof(Node));
	n = it->head;
	while (n != NULL)
	{
		printf("%d\n", n->data);
		n = n->next;
	}
}

int main(int argc, char *argv[])
{
	IteratorInt a = IteratorIntNew();
	add(a, 3);
	add(a, 16);
	add(a, 55);
	add(a, 40);
	add(a, 32);
	add(a, 20);
	add(a, 22);
	add(a, 70);
	add(a, 62);
	add(a, 50);
	add(a, 80);
	add(a, 11);
	IteratorInt b = IteratorIntNew();
	b = getPeaks(a);
	showlist(b);
//	add(b, 5);
//	add(b, 5);
//	subsetList(a, b);
	return 0;
}
	
//	printf("main method add method %d\n", add(a, 20));
//	printf("main method add method %d\n", add(a, 12));
//	printf("main method add method %d\n", add(a, 33));
//	printf("main method add method %d\n", add(a, 25));
//	printf("main method previous %d\n", *previous(a));
//	printf("main method previous %d\n", *previous(a));
//	printf("main method next %d\n", *next(a));
//	printf("main method delete %d\n", deleteElm(a));
//	printf("main method previous %d\n", *previous(a));
//	printf("main method delete %d\n", deleteElm(a));
//	printf("main method previous %d\n", *previous(a));
//	printf("main method delete %d\n", deleteElm(a));
//	printf("main method next %d\n", *next(a));
//	printf("main method delete %d\n", deleteElm(a));
//	printf("main method add method %d\n", add(a, 55));
//	printf("main method add method %d\n", add(a, 29));
//	printf("main method reset called-------------\n");
//	reset(a);
//	printf("main method next %d\n", *next(a));
//	printf("main method add method %d\n", add(a, 62));
//	printf("main method add method %d\n", add(a, 44));
//	printf("main method previous %d\n", *previous(a));
//	printf("main method next %d\n", *next(a));
//	printf("main method delete %d\n", deleteElm(a));
//	printf("main method previous %d\n", *previous(a));
//	printf("main method next %d\n", *next(a));
//	printf("main method delete %d\n", deleteElm(a));
//	printf("main method delete %d\n", deleteElm(a));
//	printf("main method next %d\n", *next(a));
//	printf("main method delete %d\n", deleteElm(a));
//	printf("main method previous %d\n", *previous(a));
//	printf("main method delete %d\n", deleteElm(a));
//	//printf("main method current node %d\n",a->currentNode->data);
//	//printf("main method current node %d\n",a->currentNode->data);
//	
//	//printf("prev counter %d\n", prev_counter);
//	//
//	//
//	//printf("main method add method %d\n", add(a, 25));
//	//printf("main method add method %d\n", add(a, 14));
//	//printf("main method add method %d\n", add(a, 32));
//	//printf("main method add method %d\n", add(a, 53));
//	
//	
//	//
//	//freeIt(a);
//	//add(a,50);
//	
//	//reset(a);
//	//printf("main method has previous %d\n", hasPrevious(a));
//	//printf("main method previous %d\n", *previous(a));
//	
//	//printf("main method check counter %d\n", check_counter);
//	
////	printf("main method set %d\n", set(a, 100));
//	
//	//printf("main method has next %d\n", hasNext(a));
//	
//	
//	
//	
////	
//	//add(a, 25);	
//	//printf("answer -->main method next %d\n", *next(a));
//	//printf("answer -->main method next %d\n", *next(a));
////	printf("answer -->main method next %d\n", *next(a));
//	
//	//printf("main method previous %d\n", *previous(a));
//	//set(a, 56);
//	//printf("main method has previous %d\n", hasPrevious(a));
//	//printf("main method has next %d\n", hasNext(a));
//	//printf("main method current node %d\n",a->currentNode->data);
//	//add(a,30);
//	//printf("main method previous %d\n", *previous(a));
//	//printf("main method previous %d\n", *previous(a));
//	//printf("main method find next %d\n", *findNext(a,10));
//	//add(a, 25);
//	//printf("main method previous %d\n", *previous(a));
//	//printf("main method next %d\n", *next(a));
//	
//	//printf("main method find previous %d\n", *findPrevious(a,5));
//	//printf("main method delete %d\n", deleteElm(a));
//	//printf("prev counter %d\n", prev_counter);
//	//printf("main method find previous %d\n", *findNext(a,14));
//	//printf("main method previous %d\n", *previous(a));
//	//printf("main method next %d\n", *next(a));
//	//printf("prev counter %d\n", prev_counter);
//	//printf("main method next %d\n", *next(a));
//	//printf("main method previous %d\n", *previous(a));
//	//printf("prev counter %d\n", prev_counter);
////	printf("main method previous %d\n", *previous(a));
//	//printf("main method %d\n",a->currentNode->data);
//	//add(a, 13);
////	printf("main method current node %d\n",a->currentNode->data);
////	printf("main method prev counter %d\n", prev_counter);
////	showlist(a);
////	printf("main method %d\n",a->tail->prev->data);
////	printf("main method %d\n", hasNext(a));
//return 100;
//}
//int main(int argc, char *argv[]) {
//
//	  /* The following code, inside the comments, may or may not be correct!
//
//	     It's provided in case you find it difficult to understand
//	     how to create a list iterator, and use it's functions.
//
//	     The code below only tests basic operations, however
//	     make sure that you do test all the required functions properly in
//	     your test file.
//
//	  */
//		/*
//		int val, result;
//		IteratorInt it1 = IteratorIntNew();
//
//		val = 25;
//		result = add(it1 , val);
//		printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//		// should print "Inserting 25: Success"
//			traverseForward(it1);
//			traverseBackward(it1);
//
//			printf("\n");
//		val = 12;
//		result = add(it1 , val);
//		printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//		// should print "Inserting 12: Success"
//			traverseForward(it1);
//			traverseBackward(it1);
//
//			printf("\n");
//		val = 6;
//		result = add(it1 , val);
//		printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//		// should print "Inserting 6: Success"
//			traverseForward(it1);
//			traverseBackward(it1);
//
//			printf("\n");
//		val = 82;
//		result = add(it1 , val);
//		printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//		// should print "Inserting 82: Success"
//			traverseForward(it1);
//			traverseBackward(it1);
//
//			printf("\n");
//		val = 11;
//		result = add(it1 , val);
//		printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//		// should print "Inserting 11: Success"
//			traverseForward(it1);
//			traverseBackward(it1);
//
//			printf("\n");
//		int *vp1 = previous(it1);
//		printf("\nPrevious value is: %d \n", *(vp1) );
//		// should print "Previous value is: 11"
//			traverseForward(it1);
//			traverseBackward(it1);
//
//			printf("\n");
//			result = deleteElm(it1);
//			printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//			traverseForward(it1);
//			traverseBackward(it1);
//
//			printf("\n");
//		int *vp2 = previous(it1);
//		printf("\nPrevious value is: %d \n", *vp2 );
//		// should print "Previous value is: 82"
//			traverseForward(it1);
//			traverseBackward(it1);
//
//			printf("\n");
//			result = deleteElm(it1);
//			printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//			traverseForward(it1);
//			traverseBackward(it1);
//
//			printf("\n");
//		 vp2 = previous(it1);
//		printf("\nPrevious value is: %d \n", *vp2 );
//		// should print "Previous value is: 82"
//			traverseForward(it1);
//			traverseBackward(it1);
//
//			printf("\n");
//			result = deleteElm(it1);
//			printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//			traverseForward(it1);
//			traverseBackward(it1);
//
//			printf("\n");
//		vp2 = previous(it1);
//		printf("\nPrevious value is: %d \n", *vp2 );
//		// should print "Previous value is: 82"
//			traverseForward(it1);
//			traverseBackward(it1);
//
//			printf("\n");
//			result = deleteElm(it1);
//			printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//			traverseForward(it1);
//			traverseBackward(it1);
//
//			printf("\n");
//			vp2 = previous(it1);
//		printf("\nPrevious value is: %d \n", *vp2 );
//		// should print "Previous value is: 82"
//			traverseForward(it1);
//			traverseBackward(it1);
//
//			printf("\n");
//			result = deleteElm(it1);
//			printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//			traverseForward(it1);
//			traverseBackward(it1);
//
//			val = 25;
//			result = add(it1 , val);
//			printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//			// should print "Inserting 25: Success"
//				traverseForward(it1);
//				traverseBackward(it1);
//
//				printf("\n");
//			val = 12;
//			result = add(it1 , val);
//			printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//			// should print "Inserting 12: Success"
//				traverseForward(it1);
//				traverseBackward(it1);
//
//				printf("\n");
//			val = 6;
//			result = add(it1 , val);
//			printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//			// should print "Inserting 6: Success"
//				traverseForward(it1);
//				traverseBackward(it1);
//
//
//				val = 2;
//	      void *result1 = findNext(it1 , val);
//	      printf("\nFinding %d: %s \n", val, (result1 !=NULL ? "Success" : "Failed") );
//	      traverseForward(it1);
//	      traverseBackward(it1);
//	      printf("\n");
//
//				val=90;
//				result=add(it1, val);
//				printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//				// should print "Inserting 6: Success"
//					traverseForward(it1);
//					traverseBackward(it1);
//					printf("\n");
//
//				val = 12;
//				result1 = findPrevious(it1 , val);
//				printf("\nFinding %d: %s \n", val, (result1 !=NULL ? "Success" : "Failed") );
//				traverseForward(it1);
//				traverseBackward(it1);
//				printf("\n");
//
//				val=100;
//				result=add(it1, val);
//				printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//				// should print "Inserting 6: Success"
//					traverseForward(it1);
//					traverseBackward(it1);
//					printf("\n");
//
//				reset(it1);
//				traverseForward(it1);
//				traverseBackward(it1);
//				printf("\n");
//
//				val = 6;
//	      result1 = findNext(it1 , val);
//	      printf("\nFinding %d: %s \n", val, (result1 !=NULL ? "Success" : "Failed") );
//	      traverseForward(it1);
//	      traverseBackward(it1);
//	      printf("\n");
//
//*/
//	  int val, result;
//	  IteratorInt it1 = IteratorIntNew();
//
//	  val = 25;
//	  result = add(it1 , val);
//	  printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//	  // should print "Inserting 25: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//	  val = 12;
//	  result = add(it1 , val);
//	  printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//	  // should print "Inserting 12: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//	  val = 6;
//	  result = add(it1 , val);
//	  printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//	  // should print "Inserting 6: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//	  val = 82;
//	  result = add(it1 , val);
//	  printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//	  // should print "Inserting 82: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//	  val = 11;
//	  result = add(it1 , val);
//	  printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//	  // should print "Inserting 11: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//	  int *vp1 = previous(it1);
//	  printf("\nPrevious value is: %d \n", *(vp1) );
//	  // should print "Previous value is: 11"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//	  int *vp2 = previous(it1);
//	  printf("\nPrevious value is: %d \n", *vp2 );
//	  // should print "Previous value is: 82"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//	  int *vp3 = next(it1);
//	  printf("\nNext value is: %d \n", *vp3 );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//      result = deleteElm(it1);
//      printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//	  // should print "Next value is: 82"
//      val = 99;
//      result = add(it1 , val);
//      printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//      result = deleteElm(it1);
//      printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//      int *vp4 = previous(it1);
//      printf("\nPrevious value is: %d \n", *vp4 );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//      int *vp5 = previous(it1);
//      printf("\nPrevious value is: %d \n", *vp5 );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//      int *vp6 = previous(it1);
//     printf("\nPrevious value is: %d \n", *vp6 );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//      result = deleteElm(it1);
//      printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      result = deleteElm(it1);
//      printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//	  	printf("\nNext value is: %d \n", *next(it1) );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      result = deleteElm(it1);
//      printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//      printf("\nNext value is: %d \n", *next(it1) );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      result = deleteElm(it1);
//      printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      printf("\n");
//
//      printf("\nNext value is: %d \n", *next(it1) );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      result = deleteElm(it1);
//      printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//
//      result = deleteElm(it1);
//      printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      printf("\n");
//
//
//      result = deleteElm(it1);
//      printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      printf("\n");
//
//      val = 2;
//	  result = add(it1 , val);
//	  printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//	  // should print "Inserting 25: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//	  val = 12;
//	  result = add(it1 , val);
//	  printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//	  // should print "Inserting 12: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//	  val = 6;
//	  result = add(it1 , val);
//	  printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//	  // should print "Inserting 6: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//	  val = 82;
//	  result = add(it1 , val);
//	  printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//	  // should print "Inserting 82: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//
//      printf("\n");
//      int *temp = previous(it1);
//      printf("\nPrevious value is: %d \n", *temp );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//      temp = next(it1);
//      printf("\nNext value is: %d \n", *temp );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//
//      printf("\n");
//      printf("\nPrevious value is: %d \n", *previous(it1) );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//      result = deleteElm(it1);
//      printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//
//      printf("\n");
//	  printf("\nPrevious value is: %d \n", *previous(it1) );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      result = deleteElm(it1);
//      printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//      printf("\nPrevious value is: %d \n", *previous(it1) );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      result = deleteElm(it1);
//      printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      printf("\n");
//
//
//
//
//
//
//
//      printf("\n");
//	  val = 12;
//	  result = add(it1 , val);
//	  printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//	  // should print "Inserting 12: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//	  val = 6;
//	  result = add(it1 , val);
//	  printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//	  // should print "Inserting 6: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//	  val = 82;
//	  result = add(it1 , val);
//	  printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//	  // should print "Inserting 82: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//	  val = 11;
//	  result = add(it1 , val);
//	  printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//	  // should print "Inserting 11: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//      printf("\n");
//      printf("\nReseting Iterator Object:\n");
//      reset(it1);
//      traverseForward(it1);
//      //traverseBackward(it1);
//      printf("\n");
//
//      val = 100;
//      result = add(it1 , val);
//      printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//      // should print "Inserting 25: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//      printf("\nNext value is: %d \n", *next(it1) );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      result = deleteElm(it1);
//      printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      printf("\n");
//
//      val = 25;
//      result = add(it1 , val);
//      printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//      // should print "Inserting 25: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//      printf("\nNext value is: %d \n", *next(it1) );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      printf("\n");
//
//      val = 1;
//      result = set(it1 , val);
//      printf("\nSetting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      printf("\n");
//      printf("\nNext value is: %d \n", *next(it1) );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      val = 2;
//      result = set(it1 , val);
//      printf("\nSetting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//
//
//
//
//
//
//
//
//      printf("\nResetting Cursor:\n");
//      reset(it1);
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      val = 2;
//      void *result1 = findNext(it1 , val);
//      printf("\nFinding %d: %s \n", val, (result1 !=NULL ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      printf("\n");
//
//
//
//      result = deleteElm(it1);
//      printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      printf("\n");
//
//      val = 3;
//      result = add(it1 , val);
//      printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//      // should print "Inserting 25: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//
//      val = 11;
//      void *result3 = findNext(it1 , val);
//      printf("\nFinding %d: %s \n", val, (result3 !=NULL ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      printf("\n");
//
//      val = 1;
//      void *result4 = findPrevious(it1 , val);
//      printf("\nFinding %d: %s \n", val, (result4 !=NULL ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      printf("\n");
//
//
//      result = deleteElm(it1);
//      printf("\nDeletion: %s \n", ( result==1 ? "Success" : "Failed") );
//      traverseForward(it1);
//      //traverseBackward(it1);
//      printf("\n");
//
//      val = 99;
//      result = add(it1 , val);
//      printf("\nInserting %d: %s \n", val, (result==1 ? "Success" : "Failed") );
//      // should print "Inserting 25: Success"
//      traverseForward(it1);
//      //traverseBackward(it1);
//      printf("\n");
//		printf("the current nide is %d\n",it1->currentNode->next->data);
//
//
//  return EXIT_SUCCESS;
//
//}
//
//

