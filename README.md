Ohjelmointi 2: Rakenteet / Programming 2: Structures

Tampereen yliopisto / Tampere University

Syksy/Autumn 2021

# Minesweeper GUI project

Note: **only commits after "copy Square and GameBoard classes from template" are my original work**. The course provided a basic framework for the project, consisting of the basic game logic (counting mines, opening squares etc.). Everything else, including the GUI created with Qt, was created by me.

Instructions (copied from instructions.txt):

When you run the program, the main game window will appear. Enter a seed (any integer number),
pick a board size using the spinbox on the right and press 'New Game' to begin. Squares will appear:
this is the game board. Click on any square to open it. If the square shows a number,
this number represents the amount of mines that the 8 squares around it contain 
(an empty square has 0 mines surrounding it). Right-click a square to mark it with a flag
if you think a mine is there. Right-click it again to mark it with a question mark if you're not sure,
or right-click one more time to clear the mark. If you left-click on a square with a mine, you lose.
Mark all mines on the board with flags and you win. Click the 'Check' button to check if the flags
you've placed are actually on squares with mines in them. The dialog box at the bottom will give you
info about what is happening and will inform you if your seed value is improper. There is also a timer
on the right that will tell you how long it takes you to clear the board.
