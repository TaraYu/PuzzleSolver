#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "puzzle2D.h"

//this file's main function just do error checking work then call hash function to solve word puzzle.




int main(int argc, char *argv[])
{
	//check the number of arguments;there are only two situations: 1- no optional argument(7arguments) 2- have optional arugment(9arguments)
    if (argc!=7 && argc!=9)
    {
        fprintf(stderr,"Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]\n");
        return 6;
    }
    int i;
    int number_p=0,number_l=0,number_w=0;
    char *puzzle_file;
    char *wordlist_file;
    int word_length;
	//check the argument's position
    for (i=0;i<7;i++)
    {
        if(strcmp(argv[i],"-p")==0)
        {
            number_p+=1;
            if (i!=1&&i!=3&&i!=5)
            {
                fprintf(stderr,"Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]\n");
                return 6;
            }
            puzzle_file = argv[i+1];
        }
        if(strcmp(argv[i],"-w")==0)
        {
            number_w+=1;
            if (i!=1&&i!=3&&i!=5)
            {
                fprintf(stderr,"Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]\n");
                return 6;
            }
            wordlist_file = argv[i+1];
        }
        if(strcmp(argv[i],"-l")==0)
        {
            number_l+=1;
            if (i!=1&&i!=3&&i!=5)
            {
                fprintf(stderr,"Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]\n");
                return 6;
            }
            if ((atoi(argv[i+1])>100))
            {
                fprintf(stderr,"Encountered error\n");
                return 7;
            }
            word_length = atoi(argv[i+1]);
        }

    }
    if (number_p!=1||number_w!=1||number_l!=1)
    {
        fprintf(stderr,"Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]\n");
        return 6;
    }
	//if there is no optional arguments, just print the result to output.txt
    if(argc==7)
    {
	    FILE*fp3 = fopen("output.txt","w");
	    FILE*fp1 = fopen(puzzle_file,"r");
	    FILE*fp2 = fopen(wordlist_file,"r");
	    //FILE*fp3 = fopen("output.txt","w");

	    if(fp1==NULL)
	    {
		fprintf(stderr,"Error: Puzzle file %s does not exist\n",puzzle_file);
		return 4;
	    }

	    if(fp2==NULL)
	    {
		fprintf(stderr,"Error: Wordlist file %s does not exist\n",wordlist_file);
		return 4;
	    }

	    char word[101];
	    int real_word_length;
	    int p;
	    int q=0;

	    //check puzzle file format
	    char puzzle[101];
	    int puzzle_length;
	    char puzzletable[101][101];
	    int n = 0;
	    while (fgets(puzzle,sizeof(puzzle),fp1)!=NULL)
	    {	
		//make sure there is no newline character
		if (puzzle[strlen(puzzle)-1] == '\n')
		{
		    puzzle[strlen(puzzle)-1] = '\0';
		}

		puzzle_length = strlen(puzzle);
		//check the ascii range 
		for(p=0;p<puzzle_length;p++)
		{
		    if(puzzle[p]<32||puzzle[p]>126)
		    {
		        fprintf(stderr,"Encountered error\n");
		        return 7;

		    }
			//put puzzle to a 2d-array
		    puzzletable[n][p] = puzzle[p];
		}
		n++;
	    }
	    //check word list format
	    while (fgets(word,sizeof(word),fp2)!=NULL)
	    {
		if (word[strlen(word)-1] == '\n')
		{
		    word[strlen(word)-1] = '\0';
		}
		if (strlen(word)!=0)
		{
			real_word_length = strlen(word);
		}
		else
			break;
		//printf("%d;%d\n",real_word_length,word_length);
		if(real_word_length!=word_length)
		{
		    fprintf(stderr,"Encountered error\n");
		    return 7;
		}
		
		for(p=0;p<word_length;p++)
		{
		    if(word[p]<32||word[p]>126)
		    {
		        fprintf(stderr,"Encountered error\n");
		        return 7;
		    }
		}
		q++;
		fprintf(fp3,"%s;",word);
		//call hash function to solve the wordpuzzle
		//use one word string as parameter. solve word one by one
		hash(puzzletable,word,word_length,fp3);
	    }
	    fclose(fp1);
	    fclose(fp2);
	    fclose(fp3);
    }
	//if user input optional argument we need to print result to the specified file
    if(argc==9)
    {
	//check optional argument's format
	if(strcmp(argv[7],"-o")!=0)
	{
	    fprintf(stderr,"Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]\n");
	    return 6;
	}
	else
	{
	    FILE*fp1 = fopen(puzzle_file,"r");
	    FILE*fp2 = fopen(wordlist_file,"r");
	    FILE*fp3 = fopen(argv[8],"w");

	    if(fp1==NULL)
	    {
		fprintf(stderr,"Error: Puzzle file %s does not exist\n",puzzle_file);
		return 4;
	    }

	    if(fp2==NULL)
	    {
		fprintf(stderr,"Error: Wordlist file %s does not exist\n",wordlist_file);
		return 4;
	    }

	    char word[101];
	    int real_word_length;
	    int p;
	    int q=0;

	    //check puzzle file format
	    char puzzle[101];
	    int puzzle_length;
	    char puzzletable[101][101];
	    int n = 0;
	    while (fgets(puzzle,sizeof(puzzle),fp1)!=NULL)
	    {
		if (puzzle[strlen(puzzle)-1] == '\n')
		{
		    puzzle[strlen(puzzle)-1] = '\0';
		}

		puzzle_length = strlen(puzzle);
		for(p=0;p<puzzle_length;p++)
		{
		    if(puzzle[p]<32||puzzle[p]>126)
		    {
		        fprintf(stderr,"Encountered error\n");
		        return 7;

		    }
		    puzzletable[n][p] = puzzle[p];
		}
		n++;
	    }
	    //check word list format
	    while (fgets(word,sizeof(word),fp2)!=NULL)
	    {
		if (word[strlen(word)-1] == '\n')
		{
		    word[strlen(word)-1] = '\0';
		}
		real_word_length = strlen(word);

		if (strlen(word)!=0)
		{
			real_word_length = strlen(word);
		}
		else
			break;

		if(real_word_length!=word_length)
		{
		    fprintf(stderr,"Encountered error\n");
		    return 7;
		}
		
		for(p=0;p<word_length;p++)
		{
		    if(word[p]<32||word[p]>126)
		    {
		        fprintf(stderr,"Encountered error\n");
		        return 7;
		    }
		}
		q++;
		fprintf(fp3,"%s;",word);
		hash(puzzletable,word,word_length,fp3);
	    }
	    fclose(fp1);
	    fclose(fp2);
	    fclose(fp3);
	    }
	}
    return 0;

}

