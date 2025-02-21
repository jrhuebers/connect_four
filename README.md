# C Programming Project: `connect_four.c`
### Overview
Project worth 2 ECTS associated with a Computer Science course on digital systems. Assessed proficiency with low-level programming (particularly memory allocation) in C.

The task was to create a performant implementation of the game _Connect Four_ played on a (near-) infinite grid. Colored tokens, with colors ranging from 0 to 255, are dropped into the grid. If four tokens of the same color form a line (including diagonals), they disappear and all tokens above them fall to fill the created gaps.

**Input:** The program accepts structured input through standard command-line input. Each line of input describes the drop of a colored token, specified by its color (integer 0–255) and x-coordinate (column index). The token instantly falls to the ground or the highest token in the respective column.

**Program:** The core functionality includes checking for and eliminating lines of four matching tokens, with tokens above the removed line falling to fill the empty spaces.

**Output:** Upon receiving `EOF`, the program outputs the final state of the grid. The output consists of remaining tokens, each described by a pair of integers representing their color and x-coordinate.

### Project Files
- `connect_four.c`: C program implementing the game logic.
- directories `public_testcases`, `more_testcases`: Contain input and output files for testing the program. The files are formatted according to the input-output specifications outlined above.
- `test.sh`: A shell script that automates testing of the compiled program (`a.out`) against the input-output files in `public_testcases` and `more_testcases`.
- `test_memory.sh`: A shell script that automates memory leak testing of the compiled program (`a.out`) using Valgrind. It runs the program with the input-output files in the `public_testcases` and `more_testcases` directories to detect and report any memory leaks.
