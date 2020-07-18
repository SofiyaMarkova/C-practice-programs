/* your name | votre nom  */

#include <stdio.h>
#include <stdlib.h>
#include "pacman.h"

void initialize_game(char game_board[][N_COLS], int pacman_location[]) {

    for (int row = 0; row < N_ROWS; row++) {
        for (int col = 0; col < N_COLS; col++) {
            game_board[row][col] = EMPTY;
        }
    }

    for (int col = 2; col < 5; col++) {
        game_board[1][col] = DOTS;
    }

    for (int row = 2; row < 5; row++) {
        game_board[row][2] = WALL;
    }

    game_board[0][1] = GHOST;
    pacman_location[0] = INITIAL_ROW_LOC;
    pacman_location[1] = INITIAL_COL_LOC;
    game_board[INITIAL_ROW_LOC][INITIAL_COL_LOC] = PACMAN;
    display_gameplay("Ready to play", game_board);
}

//all is '' not "" because it is char not string (so was trying to work with & but that be wrong). anyways best to use the #define words anyways
//*loc is pacman_location (pointer got sent so can change pacman location in this function and changes everywhere)
void play(char game_board[][N_COLS], int move, int *loc, int turn_index) {

    char label_buffer[20];

    int position[2]; //array of size 2 to store the position for row and col pacman WANT to move

    sprintf(label_buffer, "\nTurn %d", turn_index);
    // display_gameplay(label_buffer, game_board);

    // yours | a vous


//set var where pacman want move
    switch (move) {
        case NORTH: //north = 1
            position[0] = loc[0] - 1;
            position[1] = loc[1];

            if (position[0] <
                0) { //if move so low that off the edge it makes the row number be the how much row to bring it back to the bot
                position[0] = N_ROWS;
            }
            break;
        case EAST: //east = 2
            position[0] = loc[0];
            position[1] = loc[1] + 1;

            if (position[1] > N_COLS) { //if move so far east that reach efge, then make take back to col 0
                position[1] = 0;
            }
            break;
        case SOUTH: //south = 3
            position[0] = loc[0] + 1;
            position[1] = loc[1];

            if (position[0] > N_ROWS) {
                position[0] = 0; //if move more than there rows, make it bring back to row 0
            }
            break;
        case WEST: //west = 4
            position[0] = loc[0];
            position[1] = loc[1] - 1;

            if (position[1] <
                0) { //if move so back cols that out of edge, move back to where col is last col (as much as there are cols column)
                position[1] = N_COLS;
            }
            break;
    }

    if (game_board[position[0]][position[1]] == WALL) { //if wall nothing should change
        printf("\ncan't move because wall");
    } else if (game_board[position[0]][position[1]] ==
               GHOST) { //if ghost just make pacman at right now location disappear
        game_board[loc[0]][loc[1]] = EMPTY;
    } else { //for anything else just move pacman on new place and make previous place clear

        game_board[loc[0]][loc[1]] = EMPTY; //make position where pacman was before an empty

        //set new position for pacman
        loc[0] = position[0];
        loc[1] = position[1];

        game_board[position[0]][position[1]] = PACMAN; //put pacman on the board now where he wants to be
    }

    display_gameplay(label_buffer, game_board); //put display here so can see after each round where pacman went

    if (game_is_over(game_board)) {
        exit(1); //exit program if game is over (no need to keep printing game is over with steps left)
    }


}

void display_gameplay(char *label, char game_board[][N_COLS]) {
    printf("\n");
    int k; //display -- border at top
    for (k = 0; k < N_COLS; k++) {
        printf("-");
    }
    printf("--\n");

    int i, j;//traverse 2D array to display all parts
    for (i = 0; i < N_ROWS; i++) {
        printf("|"); //starting | wall
        for (j = 0; j < N_COLS; j++) {
            printf("%c", game_board[i][j]);
        }
        printf("|\n"); //ending | wall and indent
    }

    //display -- border at bottom
    for (k = 0; k < N_COLS; k++) {
        printf("-");
    }
    printf("--");
}

bool game_is_over(char game_board[][N_COLS]) {
    // yours | a vous
//false: not over, keep playing
//true: over. end game

//technically can stop game before even call function, when pacman taken away == must be game over
//could technically do it more efficiently where already check if pacman killed and a counter for dots eaten elsewhere (so not have to call a check again here)
//here is O(n) since need to go through array. could have been O(1) with approach of doing the check in play already (instead of traverse array again in seperate function)

    int i, j, dotCounter = 0, sawPacman = 0;//sawPacman acts as a bool, dotCounter used to track if there are any dots left
    //traverse the char array game_board to check if there is pacman or dots
    for (i = 0; i < N_ROWS; i++) {

        for (j = 0; j < N_COLS; j++) {

            if (game_board[i][j] == PACMAN) {
                sawPacman = 1;
            }
            if (game_board[i][j] == DOTS) {
                dotCounter++;
            }
        }
    }

    if (dotCounter == 0 && sawPacman) { //pacman still there but 0 dots on board
        printf("\ngame over because all dots collected");
        return true;
    }

    if (sawPacman == 0) { //no pacman so he was eaten
        printf("\ngame over because pacman eaten by ghost");
        return true;
    }

    return false; //return false for game is over since game is not over if the above conditions were not met


}
