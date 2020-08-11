/* C language version of python code space holder
   two symbol n state turing machine permutations found
   filtering for non halting TMs
   finding TM which prints the most "ones" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

void make_single_machine(int n, char tm_lst[][4]);
void make_gen(int n, char tm_lst[][4], char *gen);
void print_gen(int n, char *gen);
char *filter_gen(int n, char *gen);
void run(int n, char *gen);


int main(int argc, char *argv[])
{
	if(argc !=2)
	{
		printf("Missing Command Line Argument!\n");
		return 1;
	}

	int n = atoi(argv[1]);  //atoi stands for ascii to int
	printf("---Running busy beaver with n=%i---\n", n);

	char tm_list[4*(n+1)][4]; // array holding all possible TMs
	make_single_machine(n, tm_list); // passing in array

	char *gen = malloc(sizeof(char)*(3+1)*(n*2)*pow((4*(n+1)),2*n));  //holding all TM pairings
	printf("Allocating memory for %.1f bytes\n", (3+1)*(n*2)*pow((4*(n+1)),2*n));
	make_gen(n, tm_list, gen);
	// print_gen(n, gen);
	char *gen_filtered = filter_gen(n, gen);
	free(gen);
	run(n, gen_filtered);

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
	for(int i=0; i<(4*(n+1)); i++)
	{
		for(int j=0; j<(4*(n+1)); j++)
		{
			strcpy(gen, temp[0][i]);
			gen += 4;
			strcpy(gen, temp[0][j]);
			gen +=4;
		}
	}
}


void print_gen(int n, char *gen)
{
	for(int i=0; i<pow(4*(n+1), 2*n); i++)
	{
		printf("%s, %s\n", gen, (gen+4));
		gen += (2*n)*4;
	}
}

char *filter_gen(int n, char *gen)
{
	printf("filter gen...\n");

	int length = 0;
	bool has_halting_state = false;
	char *gen_filtered = malloc(sizeof(char)*(3+1)*(n*2)*pow((4*(n+1)),2*n));

	for(int i=0; i<pow(4*(n+1), 2*n); i++)
	{
		// need to check if TM has halting state...
		for(int j=0; j<(2*n); j++)
		{
			if(*(gen + j*4 + 2) == 'H')
			{
				has_halting_state = true;
			}
		}
		// if it does then copy to gen_filtered
		if(has_halting_state == true)
		{
			memcpy((gen_filtered + length*(2*n)*4), gen, (2*n)*4);
			length++;		
		}
		gen += (2*n)*4;  // one system of TMs
		has_halting_state = false; // reset
	}

	gen_filtered = (char *)realloc(gen_filtered, length*4*(2*n));
	printf("---Number of systems with halting state: %i---\n", length);
	for(int i=0; i<length; i++)
	{
		printf("%s, %s\n", (gen_filtered+i*4*(2*n)), (gen_filtered+i*4*(2*n)+4));
	}
	return gen_filtered;
}


void run(int n, char *gen)
{
	printf("running...\n");

	int steps = 0;
	int score = 0;
	char *cur_tm;
	char cur_state[] = "A1";
	char possible_states[][3] = {"A0", "A1", "H0", "H1"};
	char *tape = malloc(sizeof(char)*((n+1)*10)); // tape initialised to zero
	memset(tape, '0', sizeof(char)*((n+1)*10));
	char *index = tape + ((n+1)*10)/2;
	printf("%c\n", *index);

	while(1)
	{
		printf("System: %s, %s\n", gen, (gen+4));
		printf("Current State: %s\n", possible_states[0]);

		if(cur_state == "A0")
		{
			memcpy(cur_tm, gen, sizeof(char)*4);
			printf("Current TM: %s\n", cur_tm);
			// over-write index, cur_state
		}
		else if(cur_state == "A1")
		{
			memcpy(cur_tm, gen+4, sizeof(char)*4);
			printf("Current TM: %s\n", cur_tm);
			// over-write index, cur_state
		}

		printf("finished!\n");

		steps++;
		break;
	}
}