/*
 Inverted Index ADT (partial) implementation, written by Ashesh Mahidadia Jan 2018.
 You may need to modify the following implementation and test it properly before using 
 in your program.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "InvertedIdx.h"
#include "DLListStr.h"
//#include "DLListStr.c"

#define data(tree)  ((tree)->data)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)

//typedef struct Node {
//   Tree left, right;
//   char  data[100];
//   DLListStr  list;	
//} Node;

// make a new node containing data
Tree newNode(Item it) {
   Tree new = malloc(sizeof(Node));
   assert(new != NULL);
   strcpy(new->data, it);  // replace,   data(new) = it;
   left(new) = right(new) = NULL;
   return new;
}

// create a new empty Tree
Tree newTree() {
	struct Node *L;
	L = malloc(sizeof(Node));
	L->left = NULL;
	L->list = NULL;
	L->right = NULL;
	int i;
	for (i = 0 ; i < 100 ; i++)
		L->data[i] = '\0';
	return L;
}

// free memory associated with Tree
void freeTree(Tree t) {
   if (t != NULL) {
      freeTree(left(t));
      freeTree(right(t));
      free(t);
   }
}

// display Tree sideways
void showTreeR(Tree t, int depth) {
   if (t != NULL) {
      showTreeR(right(t), depth+1);
      int i;
      for (i = 0; i < depth; i++)
	 putchar('\t');            // TAB character
      printf("%s\n", data(t));
      showTreeR(left(t), depth+1);
   }
}

void showTree(Tree t) {
   showTreeR(t, 0);
}

// check whether a key is in a Tree
bool TreeSearch(Tree t, Item it) {
   if (t == NULL)
      return false;

   else if (strcmp(it, data(t)) < 0)   //replace, else if (it < data(t))
      return TreeSearch(left(t), it);
   
   else if (strcmp(it, data(t)) > 0)  //replace, else if (it > data(t))
      return TreeSearch(right(t), it);

   else                                 // it == data(t)
      return true;
}

// insert a new item into a Tree
Tree TreeInsert(Tree t, Item it, char *val1) {
	
   if (t == NULL)
   {
      t = newNode(it);
      t->list = newDLListStr();
      //printf("tree insert %s \n", val1);
	  insertSetOrd(t->list,val1);
	}
   else if (strcmp(it, data(t)) < 0)   //replace, else if (it < data(t))
      left(t) = TreeInsert(left(t), it, val1);

   else if (strcmp(it, data(t)) > 0)  //replace, else if (it > data(t))
      right(t) = TreeInsert(right(t), it, val1);
      
	else if (strcmp(it, data(t)) == 0)
		insertSetOrd(t->list,val1);
		

   return t;
}

//int main() {
//    Tree newT = newTree();
//    TreeInsert(newT, "mars", "url11");
//    TreeInsert(newT, "has", "url11");
//    TreeInsert(newT, "long", "url11");
//    TreeInsert(newT, "been", "url11");
//    TreeInsert(newT, "the", "url11");
//    TreeInsert(newT, "subject", "url11");
//    TreeInsert(newT, "of", "url11");
//    TreeInsert(newT, "human", "url11");
//    TreeInsert(newT, "interest", "url11");
//    
//    showTree(newT);
//    getch();
//    return 0;
//}



