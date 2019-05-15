#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#include "readData.c"
#include "searchPagerank.h"
#include "readData.h"
#define MAXSTRING 1000

void search(int argc, char *argv[])
{
	//char** b = GetCollection();
	//Tree t = GetInvertedList();
	int i, freq[100];
	int j = 0;
	char **listofurls;
	listofurls = malloc(sizeof *listofurls * MAXSTRING);
	
	for (i = 1 ; i < argc ; i++)
	{
		FILE *inverted;
		char val1[20] = "invertedIndex.txt";
		inverted = fopen(val1,"r");

	    char delim[2] = " ";
	    //char delim1[2] = "\n";
	    char *token;
	    char line[MAXSTRING] ;
		
		
  	    //int lnCount = 0;
	    while(fgets(line, MAXSTRING, inverted) != NULL)  {
			
			
			int leng = strlen(line);
			if(line[leng-1]=='\n')
			{
				line[leng-1] = '\0';
			}
			
	      /* first token */
	        token = strtok(line, delim);
			
	        //int count = 0;
	      /* iterate over the rest of the tokens */
	        if (strcmp(argv[i], token) == 0)
	        {
	    		
	      		while( token != NULL ) {
	         		//printf( "      token %d) %s\n", ++count, token );
	    			listofurls[j] = malloc(10*sizeof(char));
	    			
	    			if (strcmp(token, argv[i]) != 0 && strcmp(token,"\n") != 0)
	    			{
	    				//printf("my token %s", token);
	    				strcpy(listofurls[j],token);
	    				freq[j]=-1;
	    				j++;
	         			
					}
	    			token = strtok(NULL, delim);
	    			
	      		}
		  	}
	      
	
	  	}
	  	
		fclose(inverted);
	}
//	int z;
//	for (z = 0 ; z < j ; z++)
//	  	printf("%d\t list of urls \t%s\n", z,listofurls[z]);
	  	
//***************************************************************
	//int arr[MAXSTRING];
    int size=j, count,maxcount=0;

    for(i=0; i<size; i++)
    {
        count = 1;
        for(j=i+1; j<size; j++)
        {
            /* If duplicate element is found */
            if(strcmp(listofurls[i],listofurls[j])==0)
            {
                count++;

                /* Make sure not to count frequency of same element again */
                freq[j] = 0;
            }
        }

        /* If frequency of current element is not counted */
        if(freq[i] != 0)
        {
            freq[i] = count;
            if (count>maxcount)
            {
            	maxcount = count;
			}
        }
    }

    
    //Print frequency of each element
     
    // ******************************************************************
    FILE *pagerank;
    	//char readingline[MAXSTRING];
    	char line[MAXSTRING] ;
		char val1[20] = "pagerankList.txt";
		pagerank = fopen(val1,"r");
		char **myname;
		myname = malloc(sizeof *listofurls * MAXSTRING);
		float rank[MAXSTRING];
		int r = 0;
		char delim[2] = ",";
	    char *token;
		
		while(fgets(line, MAXSTRING, pagerank) != NULL)
		{
			token = strtok(line, delim);
			myname[r] = malloc(10*sizeof(char));
			
			strcpy(myname[r], token);
			
			token = strtok(NULL, delim);
			token = strtok(NULL, delim);
						
			rank[r] = atof(token);
			//printf("hello--->%s----> %f\n", myname[r], rank[r]);
			
			r++;
		}
    // ******************************************************************

    int k = 0, s, n;
    
    int counter = 0;
    
    //printf("\nFrequency of all elements of array : \n");
    
    while (maxcount>0)
    {
    	char **myarr;
    	myarr = malloc(sizeof *listofurls * MAXSTRING);
    	k = 0;
    	for(i=0; i<size; i++)
    	{
        	if(freq[i] != 0)
        	{
        		if(freq[i] == maxcount)
				{
					//printf("%s occurs %d times\n", listofurls[i], freq[i]);
					myarr[k] = malloc(10*sizeof(char));
					//strcat(listofurls[i], ",");
					strcpy(myarr[k], listofurls[i]);
					//printf("%d    %s\n", maxcount, myarr[k]);
					k++;
				}
        	}
    	}
    	int count = 0;
    	double highestrank = 0.0;
    	int val = 0;
//    	for (s = 0 ; s < 10 ; s++)
//    		printf("my arr in while %s\n",myarr[s]);
    	while (count < k && counter < 30)
    	{
			for (s = 0 ; s < k ; s++)
			{
				for (n = 0 ; n < r ; n++)
				{
					//printf("%s %s \n",myarr[s],myname[n]);
					if (strcmp(myarr[s], myname[n]) == 0)
					{
						//printf("if condition");
						if (rank[n] > highestrank)
						{
							
							highestrank = rank[n];
							val = n;
							
						}
					}
				}
				//printf("my name of val %s\n", myname[val]);
			}
			if (highestrank > 0)
			{
				//myname[strlen(myname[val])-1]='\0';
				//printf("highest rank of val %s\n", myname[strlen(myname[val])-1]);
				//myname[strlen(myname[val])-1] = '\0';
				printf("%s\n", myname[val]);
				counter++;
			}
				
			highestrank = 0;
			rank[val] = -1;
			count++;
			
		}
		
		
    	maxcount--;
	}
//********************************************************************	
	
	//printf("%d", argc);
	//showTree(t);
}

int main(int argc, char *argv[])
{
	search(argc, argv);
	return 0;
}
