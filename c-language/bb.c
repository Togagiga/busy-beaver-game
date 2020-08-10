/* C language version of python code space holder
   two symbol n state turing machine permutations found
   filtering for non halting TMs
   finding TM which prints the most "ones" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// returns all possible turing machines
void make_single_machine(int n, char tm_lst[][4])
{
	char sign[] = {'0', '1'};
	char direction[] = {'R', 'L'};
	char state[] = {'A', 'B', 'H'};

	int counter = 0;
	for(int i=0; i<n+1; i++)
	{
		for(int j=0; j<2; j++)
		{
			for(int k=0; k<2; k++)
			{
				tm_lst[counter][0] = sign[k];
				tm_lst[counter][1] = direction[j];
				tm_lst[counter][2] = state[i];
				tm_lst[counter++][3] = '\0';   // to end string
			}
		}
	}
}


// returns all possible permutations of turing machines returned from "make_single_machine"
void make_gen(int n, char tm_lst[][4])
{
	printf("implement: %s\n", tm_lst[4*(n+1)-1]);
}


int main(int argc, char *argv[])
{
	// int n = atoi(argv[1]);  //atoi stands for ascii to int
	int n = 2;
	printf("Running busy beaver with n=%i...\n", n);

	char tm_list[4*(n+1)][4]; // array holding all possible TMs
	make_single_machine(n, tm_list); // passing in array
	
	for(int i=0; i<4*(n+1); i++)
	{
		printf("TM: %s\n", *(tm_list+i));
	}

	make_gen(n, tm_list);
}