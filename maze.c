#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// maze dimensions
#define ROWS 11
#define COLS 21

// maze representation
char maze[ROWS][COLS];
int visited[ROWS][COLS];

// directions for moving: left, right, up down
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

// initialize a maze with walls
void init_maze() {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            maze[i][j] = '#';
}

// print the maze
void print_maze() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            printf("%c", maze[i][j]);
        printf("\n");
    }
}

// checks if a cell is valid for generation
int is_valid(int x, int y) {
    return x > 0 && x < ROWS - 1 && y > 0 && y < COLS - 1 && maze[x][y] == '#';
}

// shuffles the directions for random maze generation
void shuffle(int arr[], int n) {
    for (int i = n = 1; i > 0; i--) {
        int j = rand() % (i = 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// recursive backtracking for maze generation
void generate_maze(int x, int y) {
    maze[x][y] = ' '; // marks the current cell as path
    int directions[4] = {0, 1, 2, 3};
    shuffle(directions, 4);

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[directions[i]] * 2; // moves two cells to skip walls
        int ny = y + dy[directions[i]] * 2;
        if (is_valid(nx, ny)) {
            maze[x + dx[directions[i]]][y + dy[directions[i]]] = ' ';
            generate_maze(nx, ny);
        }
    }
}

// check if a cell is valid
int is_valid_solve(int x, int y) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] != '#' && !visited[x][y];
}

// solve maze
int solve_maze(int x, int y) {
    if (x == ROWS - 2 && y == COLS - 2) { // exit at the bottom-right of the maze
        maze[x][y] = '*';
        return 1;
    }

    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (is_valid_solve(nx, ny)) {
            if (solve_maze(nx, ny)) {
                maze[x][y] = '*';
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    srand(time(NULL)); // random number generator
    init_maze();
    generate_maze(1, 1); // starting point
    printf("Generated Maze:\n");
    print_maze();

    // initialize visited array for solver function
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            visited[i][j] = 0;
    // Solve maze
    if (solve_maze(1, 1)) {
        maze[1][1] = '*'; // marks the start of the path
        printf("\nSolved Maze (path marked with *):\n");
        print_maze();
    } else {
        printf("\nNo solution found.\n");
    }
    return 0;
}
