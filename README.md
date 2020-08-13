# Busy Beaver Game

*Experiments with complexity theory, turing machines and the halting problem for fun*

### Problem Statement

How many ones can a halting turing machine print on a blank (all 0) tape?

- We are concerned with two symbol machines ∈{0, 1}
- Machines start in "A" state
- Only halting machines are scored
- Number of possible TMs with n states: (4(n+1))^(2n)

[Wikipedia - Busy beaver](https://en.wikipedia.org/wiki/Busy_beaver)

### Getting Started

- Simply run the code (after compiling in the case of C) with a command line argument `n` as an integer (i.e. n = 1,2,3,...)
- The final score, steps and best system will be printed to the terminal

### Current Capabilities

- Successful calculation of n = 1 and 2
- n = 3 runs fairly fast on C but does not produce the right answer as of yet