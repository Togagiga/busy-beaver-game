// C language version of python code space holder
// two symbol n state turing machine permutations found
// filtering for non halting TMs
// finding TM which prints the most "ones"

#include <stdio.h>
#include <stdlib.h>

void make_single_machine(int *buf, int n)
{
	// return all permutations of single TM
	int testNum = 1;
	for(int i=0; i<4*n; i++)
	{
		buf[i] = testNum;
		testNum += 1;
	}
}


int main(int argc, char* argv[])
{
	int n = atoi(argv[1]);  //atoi stands for ascii to int
	printf("Running busy beaver with n=%i...\n", n);

	int gen_list[4*n]; // array holding permutation of single n state TM
	make_single_machine(gen_list, n); // passing in array
	
	for(int i=0; i<4*n; i++)
	{
		printf("Element in list: %i\n", gen_list[i]);
	}

	return 0;
}