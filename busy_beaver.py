# Busy Beaver problem is concerned with the question of how many ones a halting turing machine can print on an empty tape


import numpy as np
import itertools

# defining options for 2 symbol n state turing machines
beaver_dict = {1: [["0", "1"], ["R", "L"], ["A", "H"]], 2: [["0", "1"],["R", "L"], ["A", "B", "H"]], 3: [["0", "1"], ["R", "L"], ["A", "B", "C", "H"]],
				4: [["0", "1"], ["R", "L"], ["A", "B", "C", "D", "H"]], 5: [["0", "1"], ["R", "L"], ["A", "B", "C", "D", "E", "H"]]}


def make_single_machine(n):
	gen_lst = []
	for state in range(n+1):       # symbol, direction, next state
		for direction in range(2):
			for i in range(2):
				#item[machine] = item[machine][:param] + beaver_dict[n][param][i] + item[machine][param+1:]
				item = beaver_dict[n][0][i] + beaver_dict[n][1][direction] + beaver_dict[n][2][state]
				gen_lst.append(item)
	return gen_lst

def make_gen(n):
	tm_lst = make_single_machine(n)  # single machine for n states
	permutations_of = []
	gen_lst = []
	for i in range(n*2):
		permutations_of.append(tm_lst)

	# get all permutatins of lists in permutations_of (cross product)
	gen_lst = list(itertools.product(*permutations_of))

	return gen_lst


beaver_programs = [
					{ },
					{"A0": "1RH"},
					{"A0": "1RB", "A1": "1LB", "B0": "1LA", "B1": "1RH"},
					{"A0": "1RB", "A1": "1RH", "B0": "0RC", "B1": "1RB", "C0": "1LC", "C1": "1LA"},
					{"A0": "1RB", "A1": "1LB", "B0": "1LA", "B1": "0LC", "C0": "1RH", "C1": "1LD", "D0": "1RD", "D1": "0RA"}]


def run(tm, state, index):
	action = tm[state]

	if action[1] == "R":
		tape[index] = int(action[0])  # write new symbol
		index += 1
	elif action[1] == "L":
		tape[index] = int(action[0])  # write new symbol
		index -= 1
	return f"{action[2]}{int(tape[index])}", index



if __name__ == "__main__":
	n = 2						# number of states
	# steps = 1					# S(steps, symbols)  --> S(2,2)nn
	# state = "A0"
	# tape  = np.zeros(100)
	# index = 50
	# tm = beaver_programs[n]
	# for i in range(((n+1)*2*2)**(n*2)):    # number of possible machines...
	# 	state, index = run(tm, state, index)
	# 	print(index, state)
	# 	if state[0] == "H":        # check for halting state
	# 		break
	# 	steps += 1
	# print(f"Halting state reached -> Score: {len(np.argwhere(tape==1))} in {steps} steps")


	lst = make_gen(n)
	print(lst)
	print(len(lst))