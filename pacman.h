/* DO NOT MODIFY | NE MODIFIEZ PAS */

#ifndef PACMAN_H_
#define PACMAN_H_

#include <stdbool.h>

#define N_COLS 6
#define N_ROWS 6

#define INITIAL_ROW_LOC 4
#define INITIAL_COL_LOC 1

#define PACMAN 'G'
#define GHOST '@'
#define WALL '#'
#define DOTS '.'
#define EMPTY ' '

#define NORTH 	1
#define EAST	2
#define SOUTH	3
#define WEST	4

void initialize_game(char game_board[][N_COLS], int pacman_location[]);

void play(char game_board[][N_COLS], int move, int *loc, int turn_index);

void display_gameplay(char* label, char game_board[][N_COLS]);

bool game_is_over(char game_board[][N_COLS]);

#endif /* PACMAN_H_ */
