#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "puzzle2D.h"

//this file's function will solve the word puzzle and return the position and direction.


int *toprightbackwardstobottomleft(char puzzletable[][101], int word_length, unsigned long long int hashvalue);
int *bottomlefttotopright(char puzzletable[][101], int word_length, unsigned long long int hashvalue);
int *bottomrightbackwardstotopleft(char puzzletable[][101], int word_length, unsigned long long int hashvalue);
int *toplefttobottomright(char puzzletable[][101], int word_length, unsigned long long int hashvalue);
int *verticalup(char puzzletable[][101], int word_length, unsigned long long int hashvalue);
int *verticaldown(char puzzletable[][101], int word_length, unsigned long long int hashvalue);
int *horizontalleft(char puzzletable[][101], int word_length, unsigned long long int hashvalue);
int *horizontalright(char puzzletable[][101], int word_length, unsigned long long int hashvalue);
int RobinKarp(char string[], int word_length, unsigned long long int hashvalue);


//pass word one by one, each time call hash function in wordsearch2d.c, just try to solve one word in the entire puzzle. puzzle2d.c is search the word in different 8 directions one by one by comparing the hash value(using robin karp algorithm).

//if the word is found in puzzle, function will return a pointer points to an array contains position and direction; if not, return zero.

int hash(char puzzletable[][101], char word[], int word_length,FILE *fp3)
{
   double prime=101;
   int i;
   unsigned long long int hashvalue=0;
   int *ptr;

	//calculate word's hash value
   for(i=0;i<word_length;i++)
   {
       hashvalue += word[i]*(pow(prime, (double)(word_length-i-1)));
   }

	//search and compare hash value in 8 different directions
   ptr = horizontalright(puzzletable, word_length, hashvalue);
   if (ptr == NULL)
   {
       ptr = horizontalleft(puzzletable, word_length, hashvalue);
       if(ptr == NULL)
       {
           ptr = verticaldown(puzzletable, word_length, hashvalue);
           if (ptr==NULL)
           {
                ptr = verticalup(puzzletable, word_length, hashvalue);
                if (ptr==NULL)
                {
                    ptr = toplefttobottomright(puzzletable, word_length, hashvalue);
                    if (ptr==NULL)
                    {
                        ptr = bottomrightbackwardstotopleft(puzzletable, word_length, hashvalue);
                        if(ptr==NULL)
                        {
                            ptr=bottomlefttotopright(puzzletable, word_length, hashvalue);
                            if(ptr==NULL)
                            {
				ptr = toprightbackwardstobottomleft(puzzletable, word_length, hashvalue);
				if (ptr == NULL)
				    fprintf(fp3,"(0,0);0\n");
				else
				    fprintf(fp3,"(%d,%d);%d\n",ptr[0],ptr[1],ptr[2]);
			    }
                            else
                                fprintf(fp3,"(%d,%d);%d\n",ptr[0],ptr[1],ptr[2]);
                        }
                        else
                            fprintf(fp3,"(%d,%d);%d\n",ptr[0],ptr[1],ptr[2]);
                    }
                    else
                        fprintf(fp3,"(%d,%d);%d\n",ptr[0],ptr[1],ptr[2]);
                }
                else
                    fprintf(fp3,"(%d,%d);%d\n",ptr[0],ptr[1],ptr[2]);
           }
           else
               fprintf(fp3,"(%d,%d);%d\n",ptr[0],ptr[1],ptr[2]);
       }
       else
           fprintf(fp3,"(%d,%d);%d\n",ptr[0],ptr[1],ptr[2]);
   }
   else
       fprintf(fp3,"(%d,%d);%d\n",ptr[0],ptr[1],ptr[2]);
   return 0 ;
}


int * horizontalright(char puzzletable[][101], int word_length, unsigned long long int hashvalue)
{
   int col = -1;
   int i;
   for (i=0;i<strlen(puzzletable[0]);i++)
   {
	//call robinkarp function to calculate this line of puzzle 's hash value and compare with the word value 
	//puzzletable passes robinkarp function line by line
       col = RobinKarp(puzzletable[i],word_length,hashvalue);
	//if in this direction can find word:
       if (col != -1)
       {
           int position[3] = {i,col,1};
           int *pospointer = position;
           return pospointer;
       }
   }
	//if cannot find word in this direction, return null and the word pass into next direction
   return NULL;
}


int * horizontalleft(char puzzletable[][101], int word_length, unsigned long long int hashvalue)
{
   int col = -1;
   int i;
   int w=0,k=strlen(puzzletable[0])-1;

   for (i=0;i<strlen(puzzletable[0]);i++)
   {
	//reverse horizontalright string
       char reverse[strlen(puzzletable[0])+1];
       for(w=0, k=strlen(puzzletable[0])-1; w<=strlen(puzzletable[0])-1 && k>= 0; w++,k--)
       {
           reverse[w] = puzzletable[i][k];
       }
       reverse[strlen(puzzletable[0])] = '\0';
       col = RobinKarp(reverse,word_length,hashvalue);
       if (col != -1)
       {
           int position[3] = {i,strlen(puzzletable[0])-col-1,2};
           int *pospointer = position;
           return pospointer;
       }
   }
   return NULL;
}


int * verticaldown(char puzzletable[][101], int word_length, unsigned long long int hashvalue)
{
   int row = -1;
   int i;
   int j;
   int puzzlesize=0;
   puzzlesize = strlen(puzzletable[0]);
   char vertical[puzzlesize+1];
   for(j=0;j<puzzlesize;j++)
   {
       for (i=0;i<puzzlesize;i++)
       {
           vertical[i] = puzzletable[i][j];
       }
       vertical[puzzlesize] = '\0';
       row = RobinKarp(vertical,word_length,hashvalue);
       if (row != -1)
           {
               int position[3] = {row,j,3};
               int *pospointer = position;
               return pospointer;
           }
   }
   return NULL;
}

int * verticalup(char puzzletable[][101], int word_length, unsigned long long int hashvalue)
{
   int row = -1;
   int i;
   int j;
   int puzzlesize=0;
   int w=0,k=strlen(puzzletable[0])-1;
   puzzlesize = strlen(puzzletable[0]);
   char vertical[puzzlesize+1];
   for(j=0;j<puzzlesize;j++)
   {
       for (i=0;i<puzzlesize;i++)
       {
           vertical[i] = puzzletable[i][j];
       }
       vertical[puzzlesize] = '\0';

       char reverse[puzzlesize+1];
       for(w=0, k=strlen(puzzletable[0])-1; w<=strlen(puzzletable[0])-1 && k>= 0; w++,k--)
       {
           reverse[w] = vertical[k];
       }
       reverse[strlen(puzzletable[0])] = '\0';
       row = RobinKarp(reverse,word_length,hashvalue);
       if (row != -1)
           {
               int position[3] = {puzzlesize-row-1,j,4};
               int *pospointer = position;
               return pospointer;
           }
   }
   return NULL;
}


	//diagonal directions
int * toplefttobottomright(char puzzletable[][101], int word_length, unsigned long long int hashvalue)
{
    int index = -1;
    int i,k,j;
    int puzzlesize = strlen(puzzletable[0]);
	//the string above the longest diagoanl
    for(i=0;i<puzzlesize;i++)
    {
        char string[word_length+1];
        for (k=0;k<puzzlesize-i;k++)
        {
            string[k] = puzzletable[k][k+i];
        }
        string[puzzlesize-i] = '\0';
        if (strlen(string)>=word_length)
        {
            index = RobinKarp(string,word_length,hashvalue);
            if (index != -1)
            {
                int position[3] = {index,i+index,5};
                int *pospointer = position;
                return pospointer;
            }
        }
    }
	//the string below the longest diagoanl
    for (j=0;j<puzzlesize;j++)
    {
        char string[word_length+1];
        for(k=0;k<puzzlesize-j;k++)
        {
            string[k] =  puzzletable[k+j][k];
        }
        string[puzzlesize-j]='\0';
        if (strlen(string)>=word_length)
        {
            //printf("%s\n",string);
            index = RobinKarp(string,word_length,hashvalue);
            if (index != -1)
            {
                int position[3] = {j+index,index,5};
                int *pospointer = position;
                return pospointer;
            }
        }
    }
    return NULL;
}


int * bottomrightbackwardstotopleft(char puzzletable[][101], int word_length, unsigned long long int hashvalue)
{
    int index = -1;
    int w,i,k,j,l;
    int puzzlesize = strlen(puzzletable[0]);
    for(i=0;i<puzzlesize;i++)
    {
        char string[word_length+1];
        for (k=0;k<puzzlesize-i;k++)
        {
            string[k] = puzzletable[k][k+i];
        }
        string[puzzlesize-i] = '\0';

	//reverse toplefttobottomright string
        char reverse[word_length+1];
        for(w=0, l=puzzlesize-i-1; w<=puzzlesize-i-1 && l>= 0; w++,l--)
        {
            reverse[w] = string[l];
        }
        reverse[puzzlesize-i] = '\0';
        if (strlen(reverse)>=word_length)
        {
            index = RobinKarp(reverse,word_length,hashvalue);
            if (index != -1)
            {
                int position[3] = {puzzlesize-index-1-i,puzzlesize-1-index,6};
                int *pospointer = position;
                return pospointer;
            }
        }
    }
    for (j=0;j<puzzlesize;j++)
    {
        char string[word_length+1];
        for(k=0;k<puzzlesize-j;k++)
        {
            string[k] =  puzzletable[k+j][k];
        }
        string[puzzlesize-j]='\0';

        char reverse[word_length+1];
        for(w=0, l=puzzlesize-j-1; w<=puzzlesize-j-1 && l>= 0; w++,l--)
        {
            reverse[w] = string[l];
        }
        reverse[puzzlesize-j] = '\0';
        if (strlen(reverse)>=word_length)
        {
            index = RobinKarp(string,word_length,hashvalue);
            if (index != -1)
            {
                int position[3] = {puzzlesize-index-1,puzzlesize-index-j-1,6};
                int *pospointer = position;
                return pospointer;
            }
        }
    }
    return NULL;
}

int * bottomlefttotopright(char puzzletable[][101], int word_length, unsigned long long int hashvalue)
{
    int index = -1;
    int i,k,j;
    int puzzlesize = strlen(puzzletable[0]);
    for(i=0;i<puzzlesize;i++)
    {
        char string[word_length+1];
        int l=0;
        for (k=puzzlesize-i-1;k>=0;k--)
        {
            string[l] = puzzletable[k][l];
            l++;
        }
        string[puzzlesize-i] = '\0';
        if (strlen(string)>=word_length)
        {
            index = RobinKarp(string,word_length,hashvalue);
            if (index != -1)
            {
                int position[3] = {puzzlesize-index-i-1,index,7};
                int *pospointer = position;
                return pospointer;
            }
        }
    }
    for (j=0;j<puzzlesize;j++)
    {
        char string[word_length+1];
        int l=0;
        for(k=puzzlesize-j-1;k>=0;k--)
        {
            string[l] =  puzzletable[puzzlesize-1-l][puzzlesize-k-1];
            l++;
        }
        string[puzzlesize-j]='\0';
        if (strlen(string)>=word_length)
        {
            index = RobinKarp(string,word_length,hashvalue);
            if (index != -1)
            {
                int position[3] = {puzzlesize-index-1,index+j,7};
                int *pospointer = position;
                return pospointer;
            }
        }
    }
    return NULL;
}




int * toprightbackwardstobottomleft(char puzzletable[][101], int word_length, unsigned long long int hashvalue)
{
    int index = -1;
    int i,k,j,w,p;
    int puzzlesize = strlen(puzzletable[0]);
    for(i=0;i<puzzlesize;i++)
    {
        char string[word_length+1];
        int l=0;
        for (k=puzzlesize-i-1;k>=0;k--)
        {
            string[l] = puzzletable[k][l];
            l++;
        }
        string[puzzlesize-i] = '\0';
        char reverse[word_length+1];
        for(w=0, p=puzzlesize-i-1; w<=puzzlesize-i-1 && p>= 0; w++,p--)
        {
            reverse[w] = string[p];
        }
        reverse[puzzlesize-i] = '\0';



        if (strlen(reverse)>=word_length)
        {
            index = RobinKarp(reverse,word_length,hashvalue);
            if (index != -1)
            {
                int position[3] = {index,puzzlesize-index-i-1,8};
                int *pospointer = position;
                return pospointer;
            }
        }
    }
    for (j=0;j<puzzlesize;j++)
    {
        char string[word_length+1];
        int l=0;
        for(k=puzzlesize-j-1;k>=0;k--)
        {
            string[l] =  puzzletable[puzzlesize-1-l][puzzlesize-k-1];
            l++;
        }
        string[puzzlesize-j]='\0';

        char reverse[word_length+1];
        for(w=0, p=puzzlesize-j-1; w<=puzzlesize-p-1 && p>= 0; w++,p--)
        {
            reverse[w] = string[p];
        }
        reverse[puzzlesize-j] = '\0';

        if (strlen(reverse)>=word_length)
        {
            index = RobinKarp(reverse,word_length,hashvalue);
            if (index != -1)
            {
                int position[3] = {index+j,puzzlesize-index-1,8};
                int *pospointer = position;
                return pospointer;
            }
        }
    }
    return NULL;
}


//this function 's work is calculate the hash value of puzzle by robin karp algorithm and compare it with word's hashvalue, then can get the result whether the word is matched.

int RobinKarp(char string[], int word_length, unsigned long long int hashvalue)
{
   double prime=101;
   int i;
   const int lenstr = strlen(string);
   unsigned long long int value=0;
	//calculate hash value of first wordlength string
   for(i=0;i<word_length;i++)
   {
       value += string[i]*(pow(prime, (double)(word_length-i-1)));
   }
	//if match the word
   if (hashvalue == value)
       return 0;
   else
   {
	//if not, move forward a character and calculate again
       int i;
       for(i=1;i<=(lenstr-word_length);i++)
       {
           value -= string[i-1]*(pow(prime,(double)(word_length-1)));
           value = value*prime;
           value += string[i+word_length-1];
           if (value == hashvalue)
               return i;
       }
   }
	//if still not find, the word is not in this line
   return -1;
}
