/* C language version of python code space holder
   two symbol n state turing machine permutations found
   filtering for non halting TMs
   finding TM which prints the most "ones" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void make_single_machine(int n, char tm_lst[][3])
{
	// return all permutations of single TM
	char sign[2] = {'0', '1'};
	char direction[2] = {'R', 'L'};
	char state[3] = {'A', 'B', 'H'};

	int counter = 0;
	for(int i=0; i<n+1; i++)
	{
		for(int j=0; j<2; j++)
		{
			for(int k=0; k<2; k++)
			{
				tm_lst[counter][0] = sign[k];
				tm_lst[counter][1] = direction[j];
				tm_lst[counter++][2] = state[i];
			}
		}
	}
}

void make_gen(int n, char tm_lst[][3])
{
	// permutate list of 
	printf("works: %.3s\n", tm_lst[4*(n+1)-1]);
}


int main(int argc, char* argv[])
{
	int n = atoi(argv[1]);  //atoi stands for ascii to int
	printf("Running busy beaver with n=%i...\n", n);

	char tm_list[4*(n+1)][3]; // array holding permutation of single n state TM
	make_single_machine(n, tm_list); // passing in array
	
	for(int i=0; i<4*(n+1); i++)
	{
		printf("TM: %.3s\n", *(tm_list + i));
	}

	make_gen(n, tm_list);
}