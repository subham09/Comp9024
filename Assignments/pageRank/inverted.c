#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "inverted.h"
//#include "readData.c"
#include "readData.h"
#include "InvertedIdx.h"
#include "DLListStr.h"

FILE *fp;

void printInorder(Tree t)
{
	//int i;
     if (t == NULL)
          return;
 	
     /* first recur on left child */
     printInorder(t->left);
 
     /* then print the data of node */
     if (t->list != NULL)
     {
     	fprintf(fp, "%s ",t->data);
     	t->list->curr = t->list->first;
     	while (t->list->curr != NULL)
     	{
     		fprintf(fp, "%s ", t->list->curr->value);
     		t->list->curr = t->list->curr->next;
		}
		fprintf(fp , "\n");
	 }
 
     /* now recur on right child */
     printInorder(t->right);
}


void InvertedList()
{
	//char** b = GetCollection();
	Tree t = GetInvertedList();


    if((fp = fopen("invertedIndex.txt", "w")) != NULL)
    {
    	printInorder(t);
    	fclose(fp);
	}
	
	//showTree(t);
}


int main()
{
	InvertedList();
	return 0;
}
