# Busy Beaver problem is concerned with the question of how many ones a Turing machine can produce
# while eventually halting

# We will look at 2-symbol machines {0,1}
# number of possible TM: (symbols*directions*(states+1))^(states*symbols)
# states: n=3
# for 3 state: no of TMs = (2*2*(n+1))**(n*2)
# transition func has parameters: current state, current symbol, symbol to write, direction of shift, next state)
# start with all-0 tape
# iterate until halting state is entered
# BEGINS IN STATE A
# only if machine finally halts will the machine get a score which is the number of ones on the tape
# busy beaver func: Σ  -> called a busy beaver if max score is attained


beaver_dict = {2: [[0,1],["R", "L"], ["A", "B", "H"]], 3: [[0,1], ["R", "L"], ["A", "B", "C", "H"]]}

def run():
	pass

def ()



if __name__ == "__main__":
	# n = 2
	# for i in range(((n+1)*2*2)**(n*2)):
	# 	print(i)

	print(beaver_dict[2])

	#print(f"total: {12**4}")