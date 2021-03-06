/* C language version of python code space holder
   two symbol n state turing machine permutations found
   filtering for non halting TMs
   finding TM which prints the most "ones" */

// TODO make_gen only working for n=1 (implement python's itertools)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

void make_single_machine(int n, char tm_lst[][4]);
void make_gen(int n, char tm_lst[][4], char *gen);
void print_system(int n, char *gen);
void print_gen(int n, char *gen, int *length);
char *filter_gen(int n, char *gen, int *length);
void run(int n, char *gen, int *length);


int main(int argc, char *argv[]) {
	if(argc !=2) {
		printf("Missing Command Line Argument!\n");
		return 1;
	}

	int n = atoi(argv[1]);  //atoi stands for ascii to int
	printf("---Running busy beaver with n=%i---\n\n", n);

	char tm_list[4*(n+1)][4]; // array holding all possible TMs
	make_single_machine(n, tm_list); // passing in array

	int gen_length = pow(4*(n+1), 2*n);
	char *gen = malloc(sizeof(char)*(3+1)*(n*2)*gen_length);  //holding all TM pairings
	make_gen(n, tm_list, gen);

	int filtered_length; // length of gen_filtered
	char *gen_filtered = filter_gen(n, gen, &filtered_length);  // all TM pairing with halting state
	free(gen);
	// print_gen(n, gen_filtered, &filtered_length);


	// ---> run filtered list of filtered systems <---
	run(n, gen_filtered, &filtered_length);
	free(gen_filtered);

	return 0;
}


// returns all possible turing machines
void make_single_machine(int n, char tm_lst[][4]) {
	char sign[] = "01";
	char direction[] = "RL";
	char state[6];

	if(n==1) {
		strcpy(state, "AH");
	}
	else if(n==2) {
		strcpy(state, "ABH");
	}
	else if(n==3) {
		strcpy(state, "ABCH");
	}
	else if(n==4) {
		strcpy(state, "ABCDH");
	}

	int counter = 0;
	for(int i=0; i<n+1; i++) {
		for(int j=0; j<2; j++) {
			for(int k=0; k<2; k++) {
				tm_lst[counter][0] = sign[k];
				tm_lst[counter][1] = direction[j];
				tm_lst[counter][2] = state[i];
				tm_lst[counter++][3] = '\0';   // null terminator:  8 bits of zeros
			}
		}
	}
}


// returns all possible permutations of turing machines returned from "make_single_machine"
void make_gen(int n, char tm_lst[][4], char *gen) {
	char temp[n*2][4*(n+1)][4];
	int c = 0;
	for(int i=0; i<n*2; i++) {
		for(int j=0; j<(4*(n+1)); j++) {
			memcpy(temp[i][j], tm_lst[j], strlen(tm_lst[j])+1);  // (destination, source, bytes)
			c++;
		}
	}

	// cartesian product of sets
	int counter = 0;
	for(int i=0; i<pow(4*(n+1), 2*n); i++) {
		int indices[2*n];
		int remainder = i;
		for(int j=0; j<2*n; j++) {	
			indices[j] = remainder % (4*(n+1));
			remainder = remainder/(4*(n+1));
		}
		for(int j=0; j<2*n; j++) {
			strcpy(gen, temp[j][indices[(2*n-1)-j]]);
			gen += 4;
		}
	}
}


void print_system(int n, char *gen) {
	char *system = malloc(sizeof(char)*(2*n)*5);
	for(int i=0; i<2*n; i++) {
			// put all actions into one variable...
			memcpy(system + i*5, gen + i*4, 3);  // memcpy instead of strcpy to not have '\0'
			if(i != (2*n-1)) {
				memset(system + i*5 + 3, ',', 1);
				memset(system + i*5 + 4, ' ', 1);
			}
	}
	printf("System: (%s)\n", system);
	free(system);
}


void print_gen(int n, char *gen, int *length) {
	for(int i=0; i<*length; i++) {
		print_system(n, gen);
		gen += 4*(2*n);  // move pointer by one system
		if(i == 30) {
			break;
		}
	}
}


char *filter_gen(int n, char *gen, int *length) {
	*length = 0;
	bool has_halting_state = false;
	char *gen_filtered = malloc(sizeof(char)*(3+1)*(n*2)*pow(4*(n+1),2*n));

	for(int i=0; i<pow(4*(n+1), 2*n); i++) {
		// need to check if TM has halting state...
		for(int j=0; j<(2*n); j++) {
			if(*(gen + j*4 + 2) == 'H') {
				has_halting_state = true;
			}
		}
		// if it does then copy to gen_filtered
		if(has_halting_state == true) {
			memcpy((gen_filtered + (*length)*(2*n)*4), gen, (2*n)*4);
			(*length)++;		
		}
		gen += (2*n)*4;  // one system of TMs
		has_halting_state = false; // reset
	}

	gen_filtered = (char *)realloc(gen_filtered, (*length)*4*(2*n));
	printf("Number of systems with halting state: %i\n", (*length));

	return gen_filtered;
}


void run(int n, char *gen, int *length) {
	int high_score = 0;
	int high_steps = 0;
	char *best_sys;

	// iterating through all systems in gen_filtered
	for(int sys=0; sys<(*length); sys++) {
		int steps = 1;
		int score = 0;
		bool halts = false;
		char cur_state[3];
		strcpy(cur_state, "A0");
		char possible_states[][3] = {"A0", "A1", "B0", "B1", "C0", "C1", "D0", "D1"};
		int tape_length = (sqrt(*length));
		char *tape = malloc(sizeof(char)*tape_length); // tape initialised to zero
		memset(tape, '0', sizeof(char)*tape_length);
		char *index = tape + tape_length/2;

		while(1) {
			// find which action to perform according to cur_state
			char *action;
			for(int i=0; i<4; i++) {
				if(strcmp(cur_state, possible_states[i]) == 0) {
					action = (gen + 4*i);
					break;
				}
			}
			// move head of tm right or left
			if(*(action + 1) == 'R') {
				memcpy(index, action, 1); // write new symbol
				index++;
			}
			else if(*(action + 1) == 'L') {
				memcpy(index, action, 1); // write new symbol
				index--;
			}

			// update cur_state
			memcpy(cur_state, (action+2), 1);
			memcpy(cur_state+1, index, 1);

			// CHEATING: Machine assumed to never halt
			if(steps >= tape_length/2) {
				break;
			}

			// checking for new state being halting state
			if(*(cur_state) == 'H') {
				halts = true;
				// count score if halts
				for(int i=0; i<tape_length; i++) {
					if(tape[i] == '1') {
						score++;
					}
				}
				if(score > high_score) {
					high_score = score;
					high_steps = steps;
					best_sys = gen;
				}
				break;
			}
			steps++;
		}

		char *system = malloc(sizeof(char)*(2*n)*5);
		for(int i=0; i<2*n; i++) {
			// put all actions into one variable...
			memcpy(system + i*5, gen + i*4, 3);
			if(i != (2*n-1)) {
				memset(system + i*5 + 3, ',', 1);
				memset(system + i*5 + 4, ' ', 1);
			}
		}
		printf("(%s) --> %s, %i, %i\n", system, halts?"true":"false", steps, score);
		free(system);
		gen += (2*n)*4;  // move pointer one system along
		free(tape);
	}
	printf("\n----> Highest Score: %i in %i steps\n", high_score, high_steps);
	print_system(n, best_sys);
}