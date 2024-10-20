This is a 2d Maze game, build Using pdCurses on Windows. The game is an assignment of DataStructures course and focuses on multiple way linked list.

The game uses Linked list based board and OOP based approach for game building

It has been built on specific requirements, that prescribe the game features

Some of the game features are:

**Game Board**

• The game grid is represented using a multidimensional linked list, where each node
represents a grid cell, and each cell is connected to its adjacent cells (up, down, left,
right).

• Player, key, door, coins, and bomb will be placed randomly each time the game
starts; the code should be generic.

• The player can see the maze’s boundaries, but the key and the exit door are invisible.

• The player’s current position is visible, and they can move within the boundaries
of the grid.

**Movement**

• The player can move in four directions: up, down, left, and right.

• The player can only sense the distance to the hidden key, which is calculated using
the City Block Distance formula. This sensing ability informs the player whether
they are getting “closer” or “further away” from the key after each move.
If the player moves closer to the key from their initial position, a prompt will display
“Getting Closer.” Conversely, if they move further away, the prompt will display
“Further away.”

• Once the player moves in one direction, they cannot immediately move back without
using an undo feature. The number of moves allowed is based on the City Block
Distance between the player, the key, and the door.

• The player has a limited number of moves to find the key and the exit. At the start
of the game, the total number of moves will be calculated, including the distance
from the player to the key and from the key to the door.

**Sense Power (Hint System)**

• The player has a power that allows them to sense the key’s proximity.

• After each move, the game will calculate the City Block Distance between the
player’s current node and the hidden key. The player will receive a hint indicating
whether they are getting “closer” or “further away” from the key.

• The same applies to the door; the player can only enter the door if they have
obtained the key.

**Levels of Difficulty**

• Easy Level: The player has a calculated number of moves (based on the City
Block Distance) plus 6 extra moves. They can use the undo feature 6 times, and
the grid size is 10x10.

• Medium Level: The player has the calculated number of moves plus 2 extra
moves, can use the undo feature 4 times, and the grid size is 15x15.

• Hard Level: The player has exactly the calculated number of moves, only 1 undo
move, and the grid size is 20x20.

**Undo Feature**

• The player has limited undo powers. Each time the player undoes a move, they
return to their previous position by popping their last move from the stack.

• The number of undo actions is limited and depends on the difficulty level.

**Inventory System**

• Coins will appear randomly on the grid. After a short time, they will disappear,
and new coins will appear in different locations.

• The player collects coins by moving onto their positions. Each coin collected grants
one additional undo move.

• Once the player reaches the exit door, the collected coins will be revealed in the order
they were picked up. The reveal will include the exact positions where the coins
were collected, showing the order and coordinates (e.g., “(2,3)”) of each collected
coin, starting with the first coin and ending with the last.

**Score**

• If the player finishes the game with unused moves, each remaining move will con-
tribute 1 point to the player’s score.

• Each coin collected will contribute 2 points to the player’s score and grant 1 addi-
tional undo movement.

• The total score, consisting of remaining moves and collected coins, will contribute
to the player’s bonus marking in the final evaluation.

**Game Over Conditions**

• If the player steps on a bomb, the game will immediately end, and the player will
lose.

• If the player uses up all their allowed moves without reaching the exit door, the
game will be over, and the player will lose.

• If the player successfully finds the hidden key and navigates to the exit door within
the allowed number of moves, the game will be over, and the player will win.

**How To run:**

1.Install pdCurses on you device(install using vcpkg on windows).

2.Correctly setup task.json file for vscode or visual Studio

3.Use ctrl+shift+b to build the game

4. run the game using ./main
   




