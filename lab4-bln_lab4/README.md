# CSE 332 Lab Base
Repository for submitting lab work

Note: We will read this file as raw text rather than markdown.

Name: Benny Eisner, Lucas Vogel, Nicholas Magnani
Lab # 4 

Document your lab work here according to the lab specification
We all worked together in a group setting on this lab, collaborating on building, testing, and debugging the code together.
Errors:


Testing: 
When testing our program we tested both Gomoku and TicTacToe with the input "./lab_x Gomoku" and "./lab_x TicTacToe"
and in both instances the game flow worked as it should with both games being played correctly. We then tested empty string, invalid inputs,
and more than one parameter with these command lines:

- input: "./lab_x " output: "Usage: ./lab_x [TicTacToe|Gomoku]"
- input: "./lab_x hello" output: "Usage: ./lab_x [TicTacToe|Gomoku]"
- input:  "./lab_x hello world" output: "Usage: ./lab_x [TicTacToe|Gomoku]"

Then when entering the game correctly, we tried invalid moves and invalid inputs and our program worked as expected returning an error message and then asking again.
For example:

- input: "4,4" output: "Invalid move (out of bounds or too many numbers). Try again."
- input "0,   " output: Invalid move (out of bounds or too many numbers). Try again."

In all instances of invalid move input for both GoMoku and TicTacToe the game reported an error message and continued on playing. 
On all instances of testing when putting in the correct input the program worked as expected and in all draws and wins the program
returned the value corresponding to that outcome.

Extra Credit:

For the Extra credit portion we first gad to modify the constuctor for the Gomoku class to allow any board dimension greater than 3x3.
We then modified the constructor to customize the win condition by adding a new parameter for the number of required pieces connected to win.
We made it so the win condition defaults to the side lenght of the board. We then modified checking the argument parameters by seeing if 
they pass in a different board size and if no arguments are provided the game defaults to a 19x19 five in a row configuaration.

Testing Extra Credit:
We tested our extra credit first by running the program with no passed in parameters and it worked as it should by defaulting to a 19x19 board.
We then tested it by passing in the minimal board conditions of 3 by 3, other board sizes, and then invalid cases:

- input: "./lab_x Gomoku 3 3" output: a 3x3 board with a win condition of 3
- input: "./lab_x Gomoku 5 5" output: a 5x5 board with a win condition of 5
- input: "./lab_x Gomoku 10 5" output: a 10x10 board with a win condition of 5
- input: "./lab_x Gomoku 10 15" output: "Win length must be between 3 and board size /n Usage: ./lab_x [TicTacToe|Gomoku]"
- input: "./lab_x Gomoku     " output: Default board size of 19


