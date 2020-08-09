# Busy Beaver problem is concerned with the question of how many ones a halting turing machine can print on an empty tape

import numpy as np
import itertools
import sys

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

	# get all permutations (cross product)
	gen_lst = list(itertools.product(*permutations_of))

	return gen_lst


def filter_gen(gen_lst):
	# we can delete systems with no "H" state
	# we can also delete systems with identical machines
	filtered_lst = []
	for system in gen_lst:
		for tm in system:
			if tm[2] == "H":
				filtered_lst.append(system)
				break
	print(f">---- {len(filtered_lst)} possible TMs with halting state ----<")
	return filtered_lst


def run_gen(n, gen_lst):
	gen_lst = filter_gen(gen_lst)  # filtered for having halting state
	best_score, best_steps = 0, 0

	for system in gen_lst:   # number of TMs combinations with halting state
		steps = 1
		score = 0
		halts = False
		state = "A0"
		tape = np.zeros(len(gen_lst))
		index = int(len(tape)/2)
		keys = ["A0", "A1", "B0", "B1", "C0", "C1", "D0", "D1", "E0", "E1"]
		action_dict = {}
		for idx, tm in enumerate(system):
			action_dict[keys[idx]] = tm
		# print(action_dict)
		while True:
			action = action_dict[state]
			if action[1] == "R":
				tape[index] = int(action[0])  # write new symbol
				index += 1
			elif action[1] == "L":
				tape[index] = int(action[0])  # write new symbol
				index -= 1

			if steps >= int(len(tape)/2):
				# print("Machine assumed to never halt!")
				break
			state = f"{action[2]}{int(tape[index])}"
			# print(index, state)
			if state[0] == "H":
				halts = True
				score = len(np.argwhere(tape==1))
				# print(f"Halting state reached -> Score: {score} in {steps} steps")
				if score > best_score:
					best_score = score
					best_steps = steps
				break
			steps += 1
		print(f"{system} --> {halts}, {score}, {steps}")
	print(f"Best Score: {best_score} in {best_steps} steps")

	return gen_lst


######## pre-defined best TMs for n states ########
beaver_programs = [ { },
					{"A0": "1RH"},
					{"A0": "1RB", "A1": "1LB", "B0": "1LA", "B1": "1RH"},
					{"A0": "1RB", "A1": "1RH", "B0": "0RC", "B1": "1RB", "C0": "1LC", "C1": "1LA"},
					{"A0": "1RB", "A1": "1LB", "B0": "1LA", "B1": "0LC", "C0": "1RH", "C1": "1LD", "D0": "1RD", "D1": "0RA"}]

def run(tm, state, index, tape):
	action = tm[state]

	if action[1] == "R":
		tape[index] = int(action[0])  # write new symbol
		index += 1
	elif action[1] == "L":
		tape[index] = int(action[0])  # write new symbol
		index -= 1
	return f"{action[2]}{int(tape[index])}", index

def eval_tm(n, tm):
	steps = 1					# S(steps, symbols)  --> S(2,2)nn
	state = "A0"
	tape  = np.zeros(100)
	index = 50
	# tm = beaver_programs[n]
	for i in range(((n+1)*2*2)**(n*2)):    # number of possible machines...
		state, index = run(tm, state, index, tape)
		print(index, state)
		if state[0] == "H":        # check for halting state
			break
		steps += 1
	print(f"Halting state reached -> Score: {len(np.argwhere(tape==1))} in {steps} steps")
###################################################



if __name__ == "__main__":
	# eval_tm(n, beaver_programs[n])
	print(f"executing {sys.argv[0]}")
	n = int(sys.argv[1])
	lst = make_gen(n)
	lst = run_gen(n, lst)