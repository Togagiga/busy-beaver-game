/* C language version of python code space holder
   two symbol n state turing machine permutations found
   filtering for non halting TMs
   finding TM which prints the most "ones" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void make_single_machine(int n, char tm_lst[][4]);
void make_gen(int n, char tm_lst[][4], char *gen);
void print_gen(int n, char *gen);
void run();


int main(int argc, char *argv[])
{
	if(argc !=2)
	{
		printf("Missing Command Line Argument!\n");
		return 1;
	}

	int n = atoi(argv[1]);  //atoi stands for ascii to int
	printf("Running busy beaver with n=%i...\n", n);

	char tm_list[4*(n+1)][4]; // array holding all possible TMs
	make_single_machine(n, tm_list); // passing in array
	
	// for(int i=0; i<4*(n+1); i++)
	// {
	// 	printf("TM: %s\n", *(tm_list+i));
	// }

	char *gen = malloc(sizeof(char)*(3+1)*(n*2)*pow((4*(n+1)),2*n));  //holding all TM pairings
	printf("Allocating memory for %.1f bytes\n", (3+1)*(n*2)*pow((4*(n+1)),2*n));
	make_gen(n, tm_list, gen);
	print_gen(n, gen);

	return 0;
}


// returns all possible turing machines
void make_single_machine(int n, char tm_lst[][4])
{
	char sign[] = "01";
	char direction[] = "RL";
	char state[5];

	if(n==1)
	{
		strcpy(state, "AH");
	}
	else if(n==2)
	{
		strcpy(state, "ABH");
	}
	else if(n==3)
	{
		strcpy(state, "ABCH");
	}

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
				tm_lst[counter++][3] = '\0';   // null terminator:  8 bits of zeros
			}
		}
	}
}


// returns all possible permutations of turing machines returned from "make_single_machine"
void make_gen(int n, char tm_lst[][4], char *gen)
{
	printf("make gen...\n");
	char temp[n*2][4*(n+1)][4];
	int c = 0;
	for(int i=0; i<n*2; i++)
	{
		for(int j=0; j<(4*(n+1)); j++)
		{
			memcpy(temp[i][j], tm_lst[j], strlen(tm_lst[j])+1);  // (destination, source, bytes)
			// printf("%s\n", temp[i][j]);
			c++;
		}
	}

	// hard code for n=1 for now...
	char *ptr1 = gen;
	for(int i=0; i<(4*(n+1)); i++)
	{
		for(int j=0; j<(4*(n+1)); j++)
		{
			strcpy(ptr1, temp[0][i]);
			ptr1 += 4;
			strcpy(ptr1, temp[0][j]);
			ptr1 +=4;
		}
	}
}


void print_gen(int n, char *gen)
{
	for(int i=0; i<pow(4*(n+1), 2*n); i++)
	{
		printf("%s, %s\n", gen, (gen+4));
		gen += 8;
	}
}


void run()
{
	printf("running...\n");
}