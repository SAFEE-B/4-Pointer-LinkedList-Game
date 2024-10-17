#include <iostream>
#include <cstdlib>
#include <ctime>
#include <curses.h> // Ensure you have included the PDCurses header

using namespace std;

class Node {
public:
    char key;
    Node* up;
    Node* down;
    Node* left;
    Node* right;

    Node() : key('.'), up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}
};

class Board {
public:
    Node* head;
    int size;
    int px, py; // Player coordinates
    int kx, ky; // Key coordinates
    int dx, dy; // Another item coordinates
    int c1x, c1y; // Coin 1 coordinates
    int c2x, c2y; // Coin 2 coordinates
    Node* player;

    Board(int level) {
        // Set size based on level
        if (level == 1) {
            size = 10;
        } else if (level == 2) {
            size = 15;
        } else if (level == 3) {
            size = 20;
        } else {
            size = 10;
            printw("Invalid Number Given as Size...(Started with size 10x10)\n");
        }

        // Dynamically allocate the headArr
        Node** headArr = new Node*[size];
        for (int a = 0; a < size; a++) {
            headArr[a] = new Node[size]; // Create an array of Nodes for each row
            for (int b = 0; b < size; b++) {
                if (b == 0) {
                    headArr[a][b].key = '@'; // Set leftmost key to '@' (start point)
                }
            }
        }

        // Link nodes horizontally and vertically
        for (int a = 0; a < size; a++) {
            for (int b = 0; b < size - 1; b++) {
                headArr[a][b].right = &headArr[a][b + 1];
                headArr[a][b + 1].left = &headArr[a][b];
                if (a < size - 1) {
                    headArr[a][b].down = &headArr[a + 1][b];
                    headArr[a + 1][b].up = &headArr[a][b];
                }
            }
        }

        head = headArr[0];
    }

    ~Board() {
        // Cleanup memory
        for (int a = 0; a < size; a++) {
            delete[] head[a]; // Delete each row
        }
        delete[] head; // Delete the array of rows
    }

    void setParameters() {
        // Randomly set player and item positions
        px = rand() % (size - 2);
        py = rand() % (size - 2);
        
        do {
            kx = rand() % (size - 2);
            ky = rand() % (size - 2);
        } while (kx == px && ky == py);

        do {
            dx = rand() % (size - 2);
            dy = rand() % (size - 2);
        } while ((dx == px && dy == py) || (dx == kx && dy == ky));

        do {
            c1x = rand() % (size - 2);
            c1y = rand() % (size - 2);
        } while ((c1x == px && c1y == py) || (c1x == kx && c1y == ky) || (c1x == dx && c1y == dy));

        do {
            c2x = rand() % (size - 2);
            c2y = rand() % (size - 2);
        } while ((c2x == px && c2y == py) || (c2x == kx && c2y == ky) || (c2x == dx && c2y == dy) || (c2x == c1x && c2y == c1y));
    }

    void setPositions() {
        Node* currentRow = head;
        for (int a = 0; a < size; a++) {
            Node* currentPtr = currentRow;
            for (int b = 0; b < size; b++) {
                if (b == px && a == py) {
                    currentPtr->key = 'P'; // Set player position
                    player = currentPtr;
                } else if (b == kx && a == ky) {
                    currentPtr->key = 'K'; // Set key position
                } else if (b == dx && a == dy) {
                    currentPtr->key = 'D'; // Set another item position
                } else if ((b == c1x && a == c1y) || (b == c2x && a == c2y)) {
                    currentPtr->key = 'C'; // Set coin positions
                }
                currentPtr = currentPtr->right;
            }
            currentRow = currentRow->down;
        }
    }

    void MovePlayer() {
        char dir;
        printw("Give Input (w/a/s/d): ");
        refresh(); // Ensure prompt is shown
        dir = getch(); // Use getch to read input without pressing enter
        if (dir == 'w' && py > 0) {
            player->key = '.'; // Clear previous position
            player = player->up;
            player->key = 'P'; // Move up
            py--;
        } else if (dir == 's' && py < size - 1) {
            player->key = '.';
            player = player->down;
            player->key = 'P'; // Move down
            py++;
        } else if (dir == 'd' && px < size - 1) {
            player->key = '.';
            player = player->right;
            player->key = 'P'; // Move right
            px++;
        } else if (dir == 'a' && px > 0) {
            player->key = '.';
            player = player->left;
            player->key = 'P'; // Move left
            px--;
        }
    }

    void printBoard() {
        clear(); // Clear the screen
        Node* currentRow = head;

        // Print the board row by row
        for (int a = 0; a < size; a++) {
            Node* current = currentRow;
            for (int b = 0; b < size; b++) {
                mvaddch(a, b, current->key); // Use PDCurses to add characters
                current = current->right;
            }
            currentRow = currentRow->down;
        }
        refresh(); // Refresh the screen to show changes
    }
};

void PlayGame() {
    printw("What Hardness You wanna Play...\nPRESS 1 :EASY\nPRESS 2:MEDIUM\nPRESS 3:HARD\n");
    int hardness;
    scanw("%d", &hardness); // Use &hardness to read the input correctly
    Board b1(hardness);
    b1.setParameters();
    b1.setPositions();
    b1.printBoard();
    int count = 0;

    while (true) {
        b1.MovePlayer();
        b1.printBoard();
        count++;
        if (count % 10 == 0) {
            // Add coin randomization logic here
            // b1.randomizeCoin();
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    initscr(); // Start PDCurses mode
    noecho(); // Don't echo user input
    cbreak(); // Disable line buffering to read input immediately
    PlayGame();
    endwin(); // End PDCurses mode
    return 0;
}
