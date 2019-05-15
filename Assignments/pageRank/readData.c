// written by Subham Anand

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#include "graph.c"
#include "graph.h"
#include "readData.h"
#include <ctype.h>
//#include "InvertedIdx.c"
#include "InvertedIdx.h"
#define MAXSTRING 1000


static int nov = 0;
char **listofurls;
char** GetCollection()
{
	//printf("get collection");
	FILE *collection;
	char val1[15] = "collection.txt";
	collection = fopen(val1,"r");
	
	char readingline[10];
	
	listofurls = malloc(sizeof *listofurls * MAXSTRING);
	int j= 0;
	
	while (fscanf(collection, "%s", readingline)==1) {
		
		listofurls[j] = malloc(10*sizeof(char));
	
		strcpy(listofurls[j],readingline);
		
		j++;
		nov++;
	    }
//	printf("get collection method\n %d", nov);
//	for (k = 0 ; k < nov ; k++)
//		printf("get collection method %s\n", listofurls[k]);
	//printf("%d nov", nov);
	fclose(collection);
	//printf("closing\n");
	return listofurls;
}

int num()
{
	return nov;
}


Tree GetInvertedList()
{
	Tree c = newTree();
	char **b = GetCollection();
	int m;
	
	for (m = 0 ; m < nov ; m++)
	{
		FILE *urls;
		
		char txt[10] = ".txt";
		char val[10] ;
		char val1[10];
		char readingline[100];
		char *urlcontent[100];
		int n = 0,i,check;
		
		strcpy(val, *(b+m));
		strcpy(val1, *(b+m));
		//printf("val1-->%s\n", *(b+m));
		strcat(val, txt);
		
		urls = fopen(val, "r");
		int flag = 0;
		while (fscanf(urls, "%s", readingline) == 1){
			urlcontent[n] = malloc(100 * sizeof(char));
			
			if (strcmp(readingline,"Section-2") == 0 && strcmp(readingline,"#start") != 0){
				flag = 1;
			}
			if (flag==1)
			{
				if (strcmp(readingline,"#end") == 0)
				{
					break;
				}
				if (strcmp(readingline,"Section-2") != 0 && strcmp(readingline,"#start") != 0){
				
					for(i=0;i<strlen(readingline);i++)
					{
						readingline[i] = tolower(readingline[i]);
						if(i == (strlen(readingline)-1))
						{
							//printf("---------------------Hello");
							check = (int)readingline[i]; 
							if(check < 97 || check > 122)
							{
							//	printf("---------%c",readingline[i]);
								readingline[i] = '\0';
								continue;
							}
						}
					}
						
						
						strcpy(urlcontent[n], readingline);
						//printf("read data %s \n", *(b+m));
						//printf("%s \t", readingline);
						TreeInsert(c, readingline, *(b+m));
						//printf("%s \t", readingline);
						n++;
					}
				
			}
		}
	}
return c;		
}




Graph GetGraph()
{	
	int m=0, q, r;
	char **b = listofurls;
//	for (i = 0 ; i < nov ; i++)
//	{
//		printf("graph method %s\n", *(b+i));	
//	}
	
	Graph a = newGraph(nov);
	//printf("beffore inserting\n");
	//showGraph(a);
	
	for (m = 0 ; m < nov ; m++)
	{
		FILE *urls;
		
		char txt[10] = ".txt";
		char val[10];
		char readingline[20];
		char *urlcontent[20];
		int n = 0;
		
		strcpy(val, *(b+m));
		//printf("val-->%s", val);
		strcat(val, txt);
		
		urls = fopen(val, "r");
		
		while (fscanf(urls, "%s", readingline) == 1){
			urlcontent[n] = malloc(20 * sizeof(char));
			
			if (strcmp(readingline,"#end") == 0){
				break;
			}
			
			if (strcmp(readingline,"Section-1") != 0 && strcmp(readingline,"#start") != 0){
				strcpy(urlcontent[n], readingline);
				n++;
			}
		}
		
		for (q = 0; q < n ; q++)
		{
			for (r = 0 ; r < nov ; r++)
			{
				if (strcmp(urlcontent[q], *(b+r)) == 0)
				{
					Edge e1;
					e1.v = m;
					e1.w = r;
					insertEdge(a, e1);
					break;
				}
			}
		}
		//printf("after inserting\n");
		//showGraph(a);
		
		fclose(urls);	
	}
	return a;
}



//int main()
//{
//	
//	//int i = 0;
//	//Graph c = GetGraph();
//	printf("main method-------\n");
//	//showGraph(c);
//	//printf("main method g->nv %d\n", c->nV);
//	
//	char** b = GetCollection();
//	//Tree t = GetInvertedList();
//	//showTree(t);
//	return 0 ;
//}

